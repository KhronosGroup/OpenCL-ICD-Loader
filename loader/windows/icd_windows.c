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
#include "icd_windows_hkr.h"
#include "icd_windows_dxgk.h"
#include <stdio.h>
#include <windows.h>
#include <winreg.h>

static INIT_ONCE initialized = INIT_ONCE_STATIC_INIT;

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
        khrIcdVendorAdd(cszLibraryName);
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

