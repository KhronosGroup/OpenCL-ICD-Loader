/*
 * Copyright (c) 2016-2026 The Khronos Group Inc.
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

#include <initguid.h>

#include "icd.h"
#include "icd_windows.h"
#include "icd_windows_hkr.h"
#include "icd_windows_dxgk.h"
#include "icd_windows_apppackage.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winreg.h>

#include <dxgi.h>
typedef HRESULT (WINAPI *PFN_CREATE_DXGI_FACTORY)(REFIID, void **);

static INIT_ONCE initialized = INIT_ONCE_STATIC_INIT;

typedef struct WinAdapter
{
    char * szName;
    LUID luid;
} WinAdapter;

const LUID ZeroLuid = { 0, 0 };

struct WinAdapterList
{
    WinAdapter* pWinAdapterBegin;
    WinAdapter* pWinAdapterEnd;
    WinAdapter* pWinAdapterCapacity;
};

BOOL adapterAdd(WinAdapterList *list, const char* szName, LUID luid)
{
    BOOL result = TRUE;
    if (list->pWinAdapterEnd == list->pWinAdapterCapacity)
    {
        size_t oldCapacity = list->pWinAdapterCapacity - list->pWinAdapterBegin;
        size_t newCapacity = oldCapacity;
        if (0 == newCapacity)
        {
            newCapacity = 1;
        }
        else if(newCapacity < UINT_MAX/2)
        {
            newCapacity *= 2;
        }

        WinAdapter* pNewBegin = malloc(newCapacity * sizeof(WinAdapter));
        if (!pNewBegin)
            result = FALSE;
        else
        {
            if (list->pWinAdapterBegin)
            {
                memcpy(pNewBegin, list->pWinAdapterBegin, oldCapacity * sizeof(WinAdapter));
                free(list->pWinAdapterBegin);
            }
            list->pWinAdapterCapacity = pNewBegin + newCapacity;
            list->pWinAdapterEnd = pNewBegin + oldCapacity;
            list->pWinAdapterBegin = pNewBegin;
        }
    }
    if (list->pWinAdapterEnd != list->pWinAdapterCapacity)
    {
        size_t nameLen = (strlen(szName) + 1)*sizeof(szName[0]);
        list->pWinAdapterEnd->szName = malloc(nameLen);
        if (!list->pWinAdapterEnd->szName)
            result = FALSE;
        else
        {
            memcpy(list->pWinAdapterEnd->szName, szName, nameLen);
            list->pWinAdapterEnd->luid = luid;
            list->pWinAdapterEnd++;
        }
    }
    return result;
}

void adapterFree(WinAdapter *pWinAdapter)
{
    free(pWinAdapter->szName);
    pWinAdapter->szName = NULL;
}

#if defined(CL_ENABLE_LAYERS)
typedef struct WinLayer
{
    char * szName;
    DWORD priority;
} WinLayer;

typedef struct WinLayerList
{
    WinLayer* pWinLayerBegin;
    WinLayer* pWinLayerEnd;
    WinLayer* pWinLayerCapacity;
} WinLayerList;

static int __cdecl compareLayer(const void *a, const void *b)
{
    return ((const WinLayer *)a)->priority < ((const WinLayer *)b)->priority ? -1 :
           ((const WinLayer *)a)->priority > ((const WinLayer *)b)->priority ? 1 : 0;
}

static BOOL layerAdd(WinLayerList* list, const char* szName, DWORD priority)
{
    BOOL result = TRUE;
    if (list->pWinLayerEnd == list->pWinLayerCapacity)
    {
        size_t oldCapacity = list->pWinLayerCapacity - list->pWinLayerBegin;
        size_t newCapacity = oldCapacity;
        if (0 == newCapacity)
        {
            newCapacity = 1;
        }
        else if(newCapacity < UINT_MAX/2)
        {
            newCapacity *= 2;
        }

        WinLayer* pNewBegin = malloc(newCapacity * sizeof(WinLayer));
        if (!pNewBegin)
        {
            KHR_ICD_TRACE("Failed allocate space for Layers array\n");
            result = FALSE;
        }
        else
        {
            if (list->pWinLayerBegin)
            {
                memcpy(pNewBegin, list->pWinLayerBegin, oldCapacity * sizeof(WinLayer));
                free(list->pWinLayerBegin);
            }
            list->pWinLayerCapacity = pNewBegin + newCapacity;
            list->pWinLayerEnd = pNewBegin + oldCapacity;
            list->pWinLayerBegin = pNewBegin;
        }
    }
    if (list->pWinLayerEnd != list->pWinLayerCapacity)
    {
        size_t nameLen = (strlen(szName) + 1)*sizeof(szName[0]);
        list->pWinLayerEnd->szName = malloc(nameLen);
        if (!list->pWinLayerEnd->szName)
        {
            KHR_ICD_TRACE("Failed allocate space for Layer file path\n");
            result = FALSE;
        }
        else
        {
            memcpy(list->pWinLayerEnd->szName, szName, nameLen);
            list->pWinLayerEnd->priority = priority;
            list->pWinLayerEnd++;
        }
    }
    return result;
}

void layerFree(WinLayer *pWinLayer)
{
    free(pWinLayer->szName);
    pWinLayer->szName = NULL;
}
#endif // defined(CL_ENABLE_LAYERS)

/*
 *
 * Vendor enumeration functions
 *
 */

// go through the list of vendors in the registry and call khrIcdVendorAdd
// for each vendor encountered
BOOL CALLBACK khrIcdOsVendorsEnumerate(PINIT_ONCE InitOnce, PVOID Parameter, PVOID *lpContext)
{
    (void)InitOnce;
    (void)Parameter;
    (void)lpContext;

    LONG result;
    BOOL status = FALSE, currentStatus = FALSE;
    const char* platformsName = "SOFTWARE\\Khronos\\OpenCL\\Vendors";
    HKEY platformsKey = NULL;
    DWORD dwIndex;
    WinAdapterList adapterList = {NULL, NULL, NULL};

    khrIcdInitializeEnvOptions();
    khrIcdVendorsEnumerateEnv();

    currentStatus = khrIcdOsVendorsEnumerateDXGK(&adapterList);
    status |= currentStatus;
    if (!currentStatus)
    {
        KHR_ICD_TRACE("Failed to load via DXGK interface on RS4, continuing\n");
    }

    currentStatus = khrIcdOsVendorsEnumerateHKR(&adapterList);
    status |= currentStatus;
    if (!currentStatus)
    {
        KHR_ICD_TRACE("Failed to enumerate HKR entries, continuing\n");
    }

    currentStatus = khrIcdOsVendorsEnumerateAppPackage(&adapterList);
    status |= currentStatus;
    if (!currentStatus)
    {
        KHR_ICD_TRACE("Failed to enumerate App package entry, continuing\n");
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
    }
    else
    {
        // for each value
        for (dwIndex = 0;; ++dwIndex)
        {
            char cszLibraryName[1024] = {0};
            DWORD dwLibraryNameSize = sizeof(cszLibraryName);
            DWORD dwLibraryNameType = 0;
            DWORD dwValue = 0;
            DWORD dwValueSize = sizeof(dwValue);

            // read the value name
            KHR_ICD_TRACE("Reading value %"PRIuDW"...\n", dwIndex);
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
                KHR_ICD_TRACE("Failed to read value %"PRIuDW", done reading key.\n", dwIndex);
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
            status |= adapterAdd(&adapterList, cszLibraryName, ZeroLuid);
        }
    }

    // Add adapters according to DXGI's preference order
    HMODULE hDXGI = LoadLibraryA("dxgi.dll");
    if (hDXGI)
    {
        IDXGIFactory* pFactory = NULL;
        PFN_CREATE_DXGI_FACTORY pCreateDXGIFactory = (PFN_CREATE_DXGI_FACTORY)(void*)GetProcAddress(hDXGI, "CreateDXGIFactory");
        if (pCreateDXGIFactory)
        {
            HRESULT hr = pCreateDXGIFactory(&IID_IDXGIFactory, (void **)&pFactory);
            if (SUCCEEDED(hr))
            {
                UINT i = 0;
                IDXGIAdapter* pAdapter = NULL;
                while (SUCCEEDED(pFactory->lpVtbl->EnumAdapters(pFactory, i++, &pAdapter)))
                {
                    DXGI_ADAPTER_DESC AdapterDesc;
                    if (SUCCEEDED(pAdapter->lpVtbl->GetDesc(pAdapter, &AdapterDesc)))
                    {
                        for (WinAdapter* iterAdapter = adapterList.pWinAdapterBegin; iterAdapter != adapterList.pWinAdapterEnd; ++iterAdapter)
                        {
                            if (iterAdapter->luid.LowPart == AdapterDesc.AdapterLuid.LowPart
                                && iterAdapter->luid.HighPart == AdapterDesc.AdapterLuid.HighPart)
                            {
                                khrIcdVendorAdd(iterAdapter->szName);
                                break;
                            }
                        }
                    }

                    pAdapter->lpVtbl->Release(pAdapter);
                }
                pFactory->lpVtbl->Release(pFactory);
            }
        }
        FreeLibrary(hDXGI);
    }

    // Go through the list again, putting any remaining adapters at the end of the list in an undefined order
    for (WinAdapter* iterAdapter = adapterList.pWinAdapterBegin; iterAdapter != adapterList.pWinAdapterEnd; ++iterAdapter)
    {
        khrIcdVendorAdd(iterAdapter->szName);
        adapterFree(iterAdapter);
    }

    free(adapterList.pWinAdapterBegin);

    result = RegCloseKey(platformsKey);
    if (ERROR_SUCCESS != result)
    {
        KHR_ICD_TRACE("Failed to close platforms key %s, ignoring\n", platformsName);
    }

#if defined(CL_ENABLE_LAYERS)
    const char* layersName = "SOFTWARE\\Khronos\\OpenCL\\Layers";
    HKEY layersKey = NULL;
    WinLayerList layerList = {NULL, NULL, NULL};

    KHR_ICD_TRACE("Opening key HKLM\\%s...\n", layersName);
    result = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        layersName,
        0,
        KEY_READ,
        &layersKey);
    if (ERROR_SUCCESS != result)
    {
        KHR_ICD_TRACE("Failed to open layers key %s, continuing\n", layersName);
    }
    else
    {
        // for each value
        for (dwIndex = 0;; ++dwIndex)
        {
            char cszLibraryName[1024] = {0};
            DWORD dwLibraryNameSize = sizeof(cszLibraryName);
            DWORD dwLibraryNameType = 0;
            DWORD dwValue = 0;
            DWORD dwValueSize = sizeof(dwValue);

            // read the value name
            KHR_ICD_TRACE("Reading value %"PRIuDW"...\n", dwIndex);
            result = RegEnumValueA(
                  layersKey,
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
                KHR_ICD_TRACE("Failed to read value %"PRIuDW", done reading key.\n", dwIndex);
                break;
            }
            KHR_ICD_TRACE("Value %s found...\n", cszLibraryName);

            // Require that the value be a DWORD
            if (REG_DWORD != dwLibraryNameType)
            {
                KHR_ICD_TRACE("Value not a DWORD, skipping\n");
                continue;
            }
            // add the library
            status |= layerAdd(&layerList, cszLibraryName, dwValue);
        }
        qsort(layerList.pWinLayerBegin, layerList.pWinLayerEnd - layerList.pWinLayerBegin, sizeof(WinLayer), compareLayer);
        for (WinLayer* iterLayer = layerList.pWinLayerBegin; iterLayer != layerList.pWinLayerEnd; ++iterLayer)
        {
            khrIcdLayerAdd(iterLayer->szName);
            layerFree(iterLayer);
        }
    }

    free(layerList.pWinLayerBegin);

    result = RegCloseKey(layersKey);

    khrIcdLayersEnumerateEnv();
#endif // defined(CL_ENABLE_LAYERS)
    return status;
}

// go through the list of vendors only once
void khrIcdOsVendorsEnumerateOnce()
{
    InitOnceExecuteOnce(&initialized, khrIcdOsVendorsEnumerate, NULL, NULL);
}

#if !defined(CL_LAYER_INFO) && defined(CL_SHARED_BUILD)
BOOL APIENTRY DllMain(HINSTANCE hinst, DWORD reason, LPVOID reserved) {
    (void)hinst;
    (void)reserved;
    if (reason == DLL_PROCESS_DETACH) {
        khrIcdDeinitialize(reserved == NULL ? 1 : 0);
    }
    return TRUE;
}
#endif
