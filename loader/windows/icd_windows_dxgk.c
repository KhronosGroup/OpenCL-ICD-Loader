/*
 * Copyright (c) 2017-2026 The Khronos Group Inc.
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
#include "icd_windows_dxgk.h"

#include <windows.h>
#include "adapter.h"

#ifndef NTSTATUS
typedef LONG NTSTATUS;
#define STATUS_SUCCESS  ((NTSTATUS)0x00000000L)
#define STATUS_BUFFER_TOO_SMALL ((NTSTATUS)0xC0000023)
#define NT_SUCCESS(status) (((NTSTATUS)(status)) >= 0)
#endif

// Calls D3DKMTEnumAdapters3 if available, D3DKMTEnumAdapters2 otherwise.
static NTSTATUS callEnumAdapters(
    PFN_LoaderEnumAdapters3 pEnumAdapters3,
    PFN_LoaderEnumAdapters2 pEnumAdapters2,
    ULONG* adapterCount,
    LoaderAdapterInfo* adapters)
{
    NTSTATUS status;
    if (pEnumAdapters3)
    {
        LoaderEnumAdapters3 EnumAdapters = {0};
        // Compute-only (MCDM) adapters are left out of the default enumeration.
        EnumAdapters.filter.include_compute_only = 1;
        EnumAdapters.adapter_count = *adapterCount;
        EnumAdapters.adapters = adapters;
        status = pEnumAdapters3(&EnumAdapters);
        *adapterCount = EnumAdapters.adapter_count;
    }
    else
    {
        LoaderEnumAdapters2 EnumAdapters = {0};
        EnumAdapters.adapter_count = *adapterCount;
        EnumAdapters.adapters = adapters;
        status = pEnumAdapters2(&EnumAdapters);
        *adapterCount = EnumAdapters.adapter_count;
    }
    return status;
}

static bool enumerateAdapters(
    PFN_LoaderEnumAdapters3 pEnumAdapters3,
    PFN_LoaderEnumAdapters2 pEnumAdapters2,
    ULONG* adapterCount,
    LoaderAdapterInfo** adapters)
{
    const char* functionName = pEnumAdapters3 ? "D3DKMTEnumAdapters3" : "D3DKMTEnumAdapters2";
    NTSTATUS status = STATUS_SUCCESS;

    *adapterCount = 0;
    *adapters = NULL;
    while (1)
    {
        ULONG count = 0;
        status = callEnumAdapters(pEnumAdapters3, pEnumAdapters2, &count, NULL);
        if (status == STATUS_BUFFER_TOO_SMALL)
        {
            // Number of Adapters increased between calls, retry;
            continue;
        }
        else if (!NT_SUCCESS(status))
        {
            KHR_ICD_TRACE("%s status != SUCCESS\n", functionName);
            return false;
        }
        LoaderAdapterInfo* buffer = malloc(sizeof(*buffer)*count);
        if (buffer == NULL)
        {
            KHR_ICD_TRACE("Allocation failure for adapters buffer\n");
            return false;
        }
        status = callEnumAdapters(pEnumAdapters3, pEnumAdapters2, &count, buffer);
        if (status == STATUS_BUFFER_TOO_SMALL)
        {
            // Number of Adapters increased between calls, retry;
            free(buffer);
            continue;
        }
        else if (!NT_SUCCESS(status))
        {
            KHR_ICD_TRACE("%s status != SUCCESS\n", functionName);
            free(buffer);
            return false;
        }
        *adapterCount = count;
        *adapters = buffer;
        return true;
    }
}

bool khrIcdOsVendorsEnumerateDXGK(void)
{
    bool ret = false;
    int result = 0;

    // Get handle to GDI Runtime
    HMODULE h = LoadLibraryA("gdi32.dll");
    if (h == NULL)
        return ret;

    if(GetProcAddress(h, "D3DKMTSubmitPresentBltToHwQueue")) // OS Version check
    {
        ULONG adapterCount = 0;
        LoaderAdapterInfo* adapters = NULL;
        NTSTATUS status = STATUS_SUCCESS;

        PFN_LoaderCloseAdapter pCloseAdapter = (PFN_LoaderCloseAdapter)(void*)GetProcAddress(h, "D3DKMTCloseAdapter");
        PFN_LoaderEnumAdapters2 pEnumAdapters2 = (PFN_LoaderEnumAdapters2)(void*)GetProcAddress(h, "D3DKMTEnumAdapters2");
        if (!pEnumAdapters2)
        {
            KHR_ICD_TRACE("GetProcAddress failed for D3DKMTEnumAdapters2\n");
            goto out;
        }
        PFN_LoaderQueryAdapterInfo pQueryAdapterInfo = (PFN_LoaderQueryAdapterInfo)(void*)GetProcAddress(h, "D3DKMTQueryAdapterInfo");
        if (!pQueryAdapterInfo)
        {
            KHR_ICD_TRACE("GetProcAddress failed for D3DKMTQueryAdapterInfo\n");
            goto out;
        }
        // D3DKMTEnumAdapters3 (Windows 10 2004) can explicitly request compute-only (MCDM) adapters.
        PFN_LoaderEnumAdapters3 pEnumAdapters3 = (PFN_LoaderEnumAdapters3)(void*)GetProcAddress(h, "D3DKMTEnumAdapters3");
        if (!pEnumAdapters3)
        {
            KHR_ICD_TRACE("GetProcAddress failed for D3DKMTEnumAdapters3, falling back to D3DKMTEnumAdapters2\n");
        }
        if (!(pEnumAdapters3 && enumerateAdapters(pEnumAdapters3, NULL, &adapterCount, &adapters)) &&
            !enumerateAdapters(NULL, pEnumAdapters2, &adapterCount, &adapters))
        {
            goto out;
        }
        const char* cszOpenCLRegKeyName = getOpenCLRegKeyName();
        const int szOpenCLRegKeyName = (int)(strlen(cszOpenCLRegKeyName) + 1)*sizeof(cszOpenCLRegKeyName[0]);
        for (UINT AdapterIndex = 0; AdapterIndex < adapterCount; AdapterIndex++)
        {
            LoaderQueryRegistryInfo queryArgs = {0};
            LoaderQueryRegistryInfo* pQueryArgs = &queryArgs;
            LoaderQueryRegistryInfo* pQueryBuffer = NULL;
            queryArgs.query_type = LOADER_QUERY_REGISTRY_ADAPTER_KEY;
            queryArgs.query_flags.translate_path = TRUE;
            queryArgs.value_type = REG_SZ;
            result = MultiByteToWideChar(
                CP_UTF8,
                0,
                cszOpenCLRegKeyName,
                szOpenCLRegKeyName,
                queryArgs.value_name,
                ARRAYSIZE(queryArgs.value_name));
            if (!result)
            {
                KHR_ICD_TRACE("MultiByteToWideChar status != SUCCESS\n");
                continue;
            }
            LoaderQueryAdapterInfo queryAdapterInfo = {0};
            queryAdapterInfo.handle = adapters[AdapterIndex].handle;
            queryAdapterInfo.type = LOADER_QUERY_TYPE_REGISTRY;
            queryAdapterInfo.private_data = &queryArgs;
            queryAdapterInfo.private_data_size = sizeof(queryArgs);
            status = pQueryAdapterInfo(&queryAdapterInfo);
            if (!NT_SUCCESS(status))
            {
                // Try a different value type.  Some vendors write the key as a multi-string type.
                queryArgs.value_type = REG_MULTI_SZ;
                status = pQueryAdapterInfo(&queryAdapterInfo);
                if (NT_SUCCESS(status))
                {
                    KHR_ICD_TRACE("Accepting multi-string registry key type\n");
                }
                else
                {
                    // Continue trying to get as much info on each adapter as possible.
                    // It's too late to return FALSE and claim WDDM2_4 enumeration is not available here.
                    continue;
                }
            }
            if (NT_SUCCESS(status) && pQueryArgs->status == LOADER_QUERY_REGISTRY_STATUS_BUFFER_OVERFLOW)
            {
                ULONG queryBufferSize = sizeof(LoaderQueryRegistryInfo) + queryArgs.output_value_size;
                pQueryBuffer = malloc(queryBufferSize);
                if (pQueryBuffer == NULL)
                    continue;
                memcpy(pQueryBuffer, &queryArgs, sizeof(LoaderQueryRegistryInfo));
                queryAdapterInfo.private_data = pQueryBuffer;
                queryAdapterInfo.private_data_size = queryBufferSize;
                status = pQueryAdapterInfo(&queryAdapterInfo);
                pQueryArgs = pQueryBuffer;
            }
            if (NT_SUCCESS(status) && pQueryArgs->status == LOADER_QUERY_REGISTRY_STATUS_SUCCESS)
            {
                char cszLibraryName[MAX_PATH];
                result = WideCharToMultiByte(
                    CP_UTF8,
                    0,
                    pQueryArgs->output_string,
                    -1,
                    cszLibraryName,
                    MAX_PATH,
                    NULL,
                    NULL);
                if (!result)
                {
                    KHR_ICD_TRACE("WideCharToMultiByte status != SUCCESS\n");
                }
                else
                {
                    ret |= adapterAdd(cszLibraryName, adapters[AdapterIndex].luid);
                }
            }
            else if (status == (NTSTATUS)STATUS_INVALID_PARAMETER)
            {
                free(pQueryBuffer);
                goto out;
            }
            free(pQueryBuffer);
        }
out:
        if (pCloseAdapter)
        {
            for (UINT AdapterIndex = 0; AdapterIndex < adapterCount; AdapterIndex++)
            {
                LoaderCloseAdapter closeAdapter = {0};
                closeAdapter.handle = adapters[AdapterIndex].handle;
                status = pCloseAdapter(&closeAdapter);
                if (!NT_SUCCESS(status))
                {
                    KHR_ICD_TRACE("D3DKMTCloseAdapter status != SUCCESS\n");
                }
            }
        }
        free(adapters);
    }

    FreeLibrary(h);

    return ret;
}
