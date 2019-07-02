/*
 * Copyright (c) 2016-2019 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * OpenCL is a trademark of Apple Inc. used under license by Khronos.
 */

#include "icd.h"
#include <windows.h>
#include "icd_windows_hkr.h"
#include "icd_windows_dxgk.h"
#include <stdio.h>
#include <winreg.h>

#include <initguid.h>
#include <dxgi.h>
typedef HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID, void **);

static INIT_ONCE initialized = INIT_ONCE_STATIC_INIT;

typedef struct WinAdapter
{
    char * szName;
    LUID luid;
} WinAdapter;

LUID ZeroLuid = { 0, 0 };

static WinAdapter* pWinAdapterBegin = NULL;
static WinAdapter* pWinAdapterEnd = NULL;
static WinAdapter* pWinAdapterCapacity = NULL;

void AdapterAdd(const char* szName, LUID luid)
{
    if (pWinAdapterEnd == pWinAdapterCapacity)
    {
        size_t OldCapacity = pWinAdapterCapacity - pWinAdapterBegin;
        size_t NewCapacity = OldCapacity;
        if (0 == NewCapacity)
        {
            NewCapacity = 1;
        }
        NewCapacity *= 2;

        WinAdapter* pNewBegin = malloc(NewCapacity * sizeof(*pWinAdapterBegin));
        if (pNewBegin)
        {
            if (pWinAdapterBegin)
            {
                memcpy(pNewBegin, pWinAdapterBegin, OldCapacity * sizeof(*pWinAdapterBegin));
                free(pWinAdapterBegin);
            }
            pWinAdapterCapacity = pNewBegin + NewCapacity;
            pWinAdapterEnd = pNewBegin + OldCapacity;
            pWinAdapterBegin = pNewBegin;
        }
    }
    if (pWinAdapterEnd != pWinAdapterCapacity)
    {
        size_t nameLen = strlen(szName) + 1;
        if (pWinAdapterEnd->szName = malloc(nameLen))
        {
            memcpy(pWinAdapterEnd->szName, szName, nameLen * sizeof(*szName));
            pWinAdapterEnd->luid = luid;
            ++pWinAdapterEnd;
        }
    }
}

/*
 * 
 * Vendor enumeration functions
 *
 */

// go through the list of vendors in the registry and call khrIcdVendorAdd 
// for each vendor encountered
BOOL CALLBACK khrIcdOsVendorsEnumerate(PINIT_ONCE InitOnce, PVOID Parameter, PVOID *lpContext)
{
    LONG result;
    const char* platformsName = "SOFTWARE\\Khronos\\OpenCL\\Vendors";
    HKEY platformsKey = NULL;
    DWORD dwIndex;

    if (!khrIcdOsVendorsEnumerateDXGK())
    {
        KHR_ICD_TRACE("Failed to load via DXGK interface on RS4, continuing\n");
        if (!khrIcdOsVendorsEnumerateHKR())
        {
            KHR_ICD_TRACE("Failed to enumerate HKR entries, continuing\n");
        }
    }

    KHR_ICD_TRACE("Opening key HKLM\\%s...\n", platformsName);
    result = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        platformsName,
        0,
        KEY_READ,
        &platformsKey);
    if (ERROR_SUCCESS != result)
    {
        KHR_ICD_TRACE("Failed to open platforms key %s, continuing\n", platformsName);
        return TRUE;
    }

    // for each value
    for (dwIndex = 0;; ++dwIndex)
    {
        char cszLibraryName[1024] = {0};
        DWORD dwLibraryNameSize = sizeof(cszLibraryName);
        DWORD dwLibraryNameType = 0;     
        DWORD dwValue = 0;
        DWORD dwValueSize = sizeof(dwValue);

        // read the value name
        KHR_ICD_TRACE("Reading value %d...\n", dwIndex);
        result = RegEnumValueA(
              platformsKey,
              dwIndex,
              cszLibraryName,
              &dwLibraryNameSize,
              NULL,
              &dwLibraryNameType,
              (LPBYTE)&dwValue,
              &dwValueSize);
        // if RegEnumKeyEx fails, we are done with the enumeration
        if (ERROR_SUCCESS != result) 
        {
            KHR_ICD_TRACE("Failed to read value %d, done reading key.\n", dwIndex);
            break;
        }
        KHR_ICD_TRACE("Value %s found...\n", cszLibraryName);
        
        // Require that the value be a DWORD and equal zero
        if (REG_DWORD != dwLibraryNameType)  
        {
            KHR_ICD_TRACE("Value not a DWORD, skipping\n");
            continue;
        }
        if (dwValue)
        {
            KHR_ICD_TRACE("Value not zero, skipping\n");
            continue;
        }

        // add the library
        AdapterAdd(cszLibraryName, ZeroLuid);
    }

    // Add adapters according to DXGI's preference order
    HMODULE hDXGI = LoadLibrary("dxgi.dll");
    if (hDXGI)
    {
        IDXGIFactory* pFactory = NULL;
        PFN_CREATE_DXGI_FACTORY pCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY)GetProcAddress(hDXGI, "CreateDXGIFactory");
        HRESULT hr = pCreateDXGIFactory(&IID_IDXGIFactory, &pFactory);
        if (SUCCEEDED(hr))
        {
            UINT i = 0;
            IDXGIAdapter* pAdapter = NULL;
            while (SUCCEEDED(pFactory->lpVtbl->EnumAdapters(pFactory, i++, &pAdapter)))
            {
                DXGI_ADAPTER_DESC AdapterDesc;
                pAdapter->lpVtbl->GetDesc(pAdapter, &AdapterDesc);

                for (WinAdapter* iterAdapter = pWinAdapterBegin; iterAdapter != pWinAdapterEnd; ++iterAdapter)
                {
                    if (iterAdapter->luid.LowPart == AdapterDesc.AdapterLuid.LowPart
                        && iterAdapter->luid.HighPart == AdapterDesc.AdapterLuid.HighPart)
                    {
                        khrIcdVendorAdd(iterAdapter->szName);
                        break;
                    }
                }

                pAdapter->lpVtbl->Release(pAdapter);
            }
            pFactory->lpVtbl->Release(pFactory);
        }
        FreeLibrary(hDXGI);
    }

    // Go through the list again, putting any remaining adapters at the end of the list in an undefined order
    for (WinAdapter* iterAdapter = pWinAdapterBegin; iterAdapter != pWinAdapterEnd; ++iterAdapter)
    {
        khrIcdVendorAdd(iterAdapter->szName);
    }

    result = RegCloseKey(platformsKey);
    if (ERROR_SUCCESS != result)
    {
        KHR_ICD_TRACE("Failed to close platforms key %s, ignoring\n", platformsName);
    }
	
    return TRUE;
}

// go through the list of vendors only once
void khrIcdOsVendorsEnumerateOnce()
{
    InitOnceExecuteOnce(&initialized, khrIcdOsVendorsEnumerate, NULL, NULL);
}
 
/*
 * 
 * Dynamic library loading functions
 *
 */

// dynamically load a library.  returns NULL on failure
void *khrIcdOsLibraryLoad(const char *libraryName)
{
    return (void *)LoadLibraryA(libraryName);
}

// get a function pointer from a loaded library.  returns NULL on failure.
void *khrIcdOsLibraryGetFunctionAddress(void *library, const char *functionName)
{
    if (!library || !functionName)
    {
        return NULL;
    }
    return GetProcAddress( (HMODULE)library, functionName);
}

// unload a library.
void khrIcdOsLibraryUnload(void *library)
{
    FreeLibrary( (HMODULE)library);
}

// implement device type platform behavior
void khrIcdDeviceTypeGetPlatform(cl_device_type device_type, cl_platform_id *outPlatform)
{
    // CL_DEVICE_TYPE_GPU => Should likely check Direct3D user-mode driver caps
    // CL_DEVICE_TYPE_CPU => Should likely check D3DKMT_ADAPTERTYPE::SoftwareDevice
}
