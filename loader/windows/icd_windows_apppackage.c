/*
 * Copyright (c) 2017-2019 The Khronos Group Inc.
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

#include <icd.h>
#include "icd_windows_apppackage.h"

#ifdef OPENCL_ICD_LOADER_DISABLE_OPENCLON12

bool khrIcdOsVendorsEnumerateAppPackage(void)
{
    KHR_ICD_TRACE("OpenCLOn12 is disabled\n");
    return false;
}

#else

#include <AppModel.h>

bool khrIcdOsVendorsEnumerateAppPackage(void)
{
    UINT32 numPackages = 0, bufferLength = 0;
    PCWSTR familyName = L"Microsoft.D3DMappingLayers_8wekyb3d8bbwe";
    if (ERROR_INSUFFICIENT_BUFFER != GetPackagesByPackageFamily(familyName,
                                                                &numPackages, NULL,
                                                                &bufferLength, NULL) ||
        numPackages == 0 || bufferLength == 0)
    {
        KHR_ICD_TRACE("Failed to find mapping layers packages by family name\n");
        return false;
    }

    bool ret = false;
    WCHAR *buffer = malloc(sizeof(WCHAR) * bufferLength);
    PWSTR *packages = malloc(sizeof(PWSTR) * numPackages);
    if (!buffer || !packages)
    {
        KHR_ICD_TRACE("Failed to allocate memory for package names\n");
        goto cleanup;
    }

    if (ERROR_SUCCESS != GetPackagesByPackageFamily(familyName,
                                                    &numPackages, packages,
                                                    &bufferLength, buffer))
    {
        KHR_ICD_TRACE("Failed to get mapping layers package full names\n");
        goto cleanup;
    }

    UINT32 pathLength = 0;
    WCHAR path[MAX_PATH];
    if (ERROR_INSUFFICIENT_BUFFER != GetPackagePathByFullName(packages[0], &pathLength, NULL) ||
        pathLength > MAX_PATH ||
        ERROR_SUCCESS != GetPackagePathByFullName(packages[0], &pathLength, path))
    {
        KHR_ICD_TRACE("Failed to get mapping layers package path length\n");
        goto cleanup;
    }

#if defined(_M_AMD64)
#define PLATFORM_PATH L"x64"
#elif defined(_M_ARM)
#define PLATFORM_PATH L"arm"
#elif defined(_M_ARM64)
#define PLATFORM_PATH L"arm64"
#elif defined(_M_IX86)
#define PLATFORM_PATH L"x86"
#endif

    wchar_t dllPath[MAX_PATH];
    wcscpy_s(dllPath, MAX_PATH, path);
    wcscat_s(dllPath, MAX_PATH, L"\\" PLATFORM_PATH L"\\OpenCLOn12.dll");

    char narrowDllPath[MAX_PATH];
    WideCharToMultiByte(CP_UTF8, 0, dllPath, -1, narrowDllPath, MAX_PATH, NULL, NULL);

    ret = adapterAdd(narrowDllPath, ZeroLuid);

cleanup:
    free(buffer);
    free(packages);
    return ret;
}

#endif
