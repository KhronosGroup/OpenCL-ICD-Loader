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

#include "icd.h"
#include "icd_windows_dxgk.h"

#if defined(OPENCL_ICD_LOADER_REQUIRE_WDK)
#include <windows.h>

#ifndef NTSTATUS
typedef LONG NTSTATUS;
#define STATUS_SUCCESS  ((NTSTATUS)0x00000000L)
#define STATUS_BUFFER_TOO_SMALL ((NTSTATUS)0xC0000023)
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

#include <d3dkmthk.h>
#endif

bool khrIcdOsVendorsEnumerateDXGK(void)
{
    bool ret = false;
#if defined(OPENCL_ICD_LOADER_REQUIRE_WDK)
#if defined(DXGKDDI_INTERFACE_VERSION_WDDM2_4) && (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
    {
        D3DKMT_ADAPTERINFO* pAdapterInfo = NULL;
        D3DKMT_ENUMADAPTERS2 EnumAdapters;
        NTSTATUS Status = STATUS_SUCCESS;

        // Get handle to GDI Runtime
        HMODULE h = LoadLibrary("gdi32.dll");
        KHR_ICD_ASSERT(h != NULL);

        char cszLibraryName[MAX_PATH] = { 0 };
        PFND3DKMT_ENUMADAPTERS2 pEnumAdapters2 = (PFND3DKMT_ENUMADAPTERS2)GetProcAddress((HMODULE)h, "D3DKMTEnumAdapters2");
        if (!pEnumAdapters2)
        {
            KHR_ICD_TRACE("GetProcAddress failed for D3DKMT_ENUMADAPTERS2\n");
            goto out;
        }
        while (1)
        {
            EnumAdapters.NumAdapters = 0;
            EnumAdapters.pAdapters = NULL;
            Status = pEnumAdapters2(&EnumAdapters);
            if (Status == STATUS_BUFFER_TOO_SMALL)
            {
                // Number of Adapters increased between calls, retry;
                continue;
            }
            else if (!NT_SUCCESS(Status))
            {
                KHR_ICD_TRACE("D3DKMT_ENUMADAPTERS2 status != SUCCESS\n");
                goto out;
            }
            break;
        }
        pAdapterInfo = (D3DKMT_ADAPTERINFO*)malloc(sizeof(D3DKMT_ADAPTERINFO)*(EnumAdapters.NumAdapters));
        if (pAdapterInfo == NULL)
        {
            KHR_ICD_TRACE("Allocation failure for AdapterInfo buffer\n");
            goto out;
        }
        EnumAdapters.pAdapters = pAdapterInfo;
        Status = pEnumAdapters2(&EnumAdapters);
        if (!NT_SUCCESS(Status))
        {
            KHR_ICD_TRACE("D3DKMT_ENUMADAPTERS2 status != SUCCESS\n");
            goto out;
        }
        for (UINT AdapterIndex = 0; AdapterIndex < EnumAdapters.NumAdapters; AdapterIndex++)
        {
            D3DDDI_QUERYREGISTRY_INFO QueryArgs = {0};
            D3DDDI_QUERYREGISTRY_INFO* pQueryArgs = &QueryArgs;
            D3DDDI_QUERYREGISTRY_INFO* pQueryBuffer = NULL;
            QueryArgs.QueryType = D3DDDI_QUERYREGISTRY_ADAPTERKEY;
            QueryArgs.QueryFlags.TranslatePath = TRUE;
            QueryArgs.ValueType = REG_SZ;
#ifdef _WIN64
            wcscpy_s(QueryArgs.ValueName, ARRAYSIZE(L"OpenCLDriverName"), L"OpenCLDriverName");
#else
            // There is no WOW prefix for 32bit Windows hence make a specific check
            BOOL is_wow64;
            if (IsWow64Process(GetCurrentProcess(), &is_wow64) && is_wow64)
            {
                wcscpy_s(QueryArgs.ValueName, ARRAYSIZE(L"OpenCLDriverNameWow"), L"OpenCLDriverNameWow");
            }
            else
            {
                wcscpy_s(QueryArgs.ValueName, ARRAYSIZE(L"OpenCLDriverName"), L"OpenCLDriverName");
            }
#endif
            D3DKMT_QUERYADAPTERINFO QueryAdapterInfo = {0};
            QueryAdapterInfo.hAdapter = pAdapterInfo[AdapterIndex].hAdapter;
            QueryAdapterInfo.Type = KMTQAITYPE_QUERYREGISTRY;
            QueryAdapterInfo.pPrivateDriverData = &QueryArgs;
            QueryAdapterInfo.PrivateDriverDataSize = sizeof(QueryArgs);
            Status = D3DKMTQueryAdapterInfo(&QueryAdapterInfo);
            if (!NT_SUCCESS(Status))
            {
                KHR_ICD_TRACE("D3DKMT_QUERYADAPTERINFO status != SUCCESS\n");
                goto out;
            }
            if (NT_SUCCESS(Status) && pQueryArgs->Status == D3DDDI_QUERYREGISTRY_STATUS_BUFFER_OVERFLOW)
            {
                ULONG QueryBufferSize = sizeof(D3DDDI_QUERYREGISTRY_INFO) + QueryArgs.OutputValueSize;
                pQueryBuffer = (D3DDDI_QUERYREGISTRY_INFO*)malloc(QueryBufferSize);
                memcpy(pQueryBuffer, &QueryArgs, sizeof(D3DDDI_QUERYREGISTRY_INFO));
                QueryAdapterInfo.pPrivateDriverData = pQueryBuffer;
                QueryAdapterInfo.PrivateDriverDataSize = QueryBufferSize;
                Status = D3DKMTQueryAdapterInfo(&QueryAdapterInfo);
                pQueryArgs = pQueryBuffer;
            }
            if (NT_SUCCESS(Status) && pQueryArgs->Status == D3DDDI_QUERYREGISTRY_STATUS_SUCCESS)
            {
                wchar_t* pWchar = pQueryArgs->OutputString;
                memset(cszLibraryName, 0, sizeof(cszLibraryName));
                {
                    size_t len = wcstombs(cszLibraryName, pWchar, sizeof(cszLibraryName));
                    KHR_ICD_ASSERT(len == (sizeof(cszLibraryName) - 1));
                    khrIcdVendorAdd(cszLibraryName);
                }
            }
            else if (Status == STATUS_INVALID_PARAMETER && pQueryArgs->Status == D3DDDI_QUERYREGISTRY_STATUS_FAIL)
            {
                free(pQueryBuffer);
                goto out;
            }
            free(pQueryBuffer);
        }
        ret = true;
out:
      free(pAdapterInfo);
      FreeLibrary(h);
    }
#endif
#endif
    return ret;
}
