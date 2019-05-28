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
#include <windows.h>
#include "icd_windows_dxgk.h"
#include <assert.h>

#ifndef NTSTATUS
typedef LONG NTSTATUS;
#define STATUS_SUCCESS  ((NTSTATUS)0x00000000L)
#define STATUS_BUFFER_TOO_SMALL ((NTSTATUS)0xC0000023)
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

#include "d3dkmthk.h"

bool khrIcdOsVendorsEnumerateDXGK(void)
{
#if defined(DXGKDDI_INTERFACE_VERSION_WDDM2_4) && (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_4)
    {
        D3DKMT_ADAPTERINFO* pAdapterInfo;
        D3DKMT_ENUMADAPTERS2 EnumAdapters;
        NTSTATUS Status = STATUS_SUCCESS;

        // Get handle to GDI Runtime
        HMODULE h = LoadLibrary("gdi32.dll");

        char cszLibraryName[MAX_PATH] = { 0 };
        EnumAdapters.NumAdapters = 0;
        EnumAdapters.pAdapters = NULL;
        PFND3DKMT_ENUMADAPTERS2 pEnumAdapters2 = (PFND3DKMT_ENUMADAPTERS2)GetProcAddress((HMODULE)h, "D3DKMTEnumAdapters2");
        if (!pEnumAdapters2)
        {
          goto out;
        }
        Status = pEnumAdapters2(&EnumAdapters);
        if (!NT_SUCCESS(Status) && (Status != STATUS_BUFFER_TOO_SMALL))
        {
          goto out;
        }
        pAdapterInfo = (D3DKMT_ADAPTERINFO*)malloc(sizeof(D3DKMT_ADAPTERINFO)*(EnumAdapters.NumAdapters));
        EnumAdapters.pAdapters = pAdapterInfo;
        Status = pEnumAdapters2(&EnumAdapters);
        if (!NT_SUCCESS(Status))
        {
            free(pAdapterInfo);
            goto out;
        }
        for (UINT AdapterIndex = 0; AdapterIndex < EnumAdapters.NumAdapters; AdapterIndex++)
        {
            D3DDDI_QUERYREGISTRY_INFO QueryArgs = {0};
            D3DDDI_QUERYREGISTRY_INFO* pQueryArgs = &QueryArgs;
            D3DDDI_QUERYREGISTRY_INFO* pQueryBuffer = NULL;
            QueryArgs.QueryType = D3DDDI_QUERYREGISTRY_ADAPTERKEY;
            QueryArgs.QueryFlags.TranslatePath = TRUE;
            QueryArgs.ValueType = REG_MULTI_SZ;
#ifdef _WIN64
            wcscpy_s(QueryArgs.ValueName, ARRAYSIZE(L"OpenCLDriverName"), L"OpenCLDriverName");
#else
            wcscpy_s(QueryArgs.ValueName, ARRAYSIZE(L"OpenCLDriverNameWow"), L"OpenCLDriverNameWow");
#endif
            D3DKMT_QUERYADAPTERINFO QueryAdapterInfo = {0};
            QueryAdapterInfo.hAdapter = pAdapterInfo[AdapterIndex].hAdapter;
            QueryAdapterInfo.Type = KMTQAITYPE_QUERYREGISTRY;
            QueryAdapterInfo.pPrivateDriverData = &QueryArgs;
            QueryAdapterInfo.PrivateDriverDataSize = sizeof(QueryArgs);
            Status = D3DKMTQueryAdapterInfo(&QueryAdapterInfo);
            if (!NT_SUCCESS(Status))
            {
                free(pAdapterInfo);
                goto out;
            }
            if (NT_SUCCESS(Status) && pQueryArgs->Status == D3DDDI_QUERYREGISTRY_STATUS_BUFFER_OVERFLOW)
            {
                unsigned int QueryBufferSize = sizeof(D3DDDI_QUERYREGISTRY_INFO) + QueryArgs.OutputValueSize;
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
                unsigned int i = 0;
                memset(cszLibraryName, 0, sizeof(cszLibraryName));
                {
                    size_t ret = wcstombs(cszLibraryName, pWchar, sizeof(cszLibraryName));
                    KHR_ICD_ASSERT(ret == (sizeof(cszLibraryName) - 1));
                    if (i < (sizeof(cszLibraryName) - 1)) khrIcdVendorAdd(cszLibraryName);
                }
            }
            free(pQueryBuffer);
        }
        free(pAdapterInfo);
        FreeLibrary(h);
        return TRUE;
out:
      FreeLibrary(h);
    }
#endif
    return FALSE;
}
