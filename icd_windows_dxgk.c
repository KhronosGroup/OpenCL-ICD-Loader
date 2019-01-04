/*
 * Copyright (c) 2018 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software source and associated documentation files (the "Materials"),
 * to deal in the Materials without restriction, including without limitation
 * the rights to use, copy, modify, compile, merge, publish, distribute,
 * sublicense, and/or sell copies of the Materials, and to permit persons to
 * whom the Materials are furnished to do so, subject the following terms and
 * conditions:
 *
 * All modifications to the Materials used to create a binary that is
 * distributed to third parties shall be provided to Khronos with an
 * unrestricted license to use for the purposes of implementing bug fixes and
 * enhancements to the Materials;
 *
 * If the binary is used as part of an OpenCL(TM) implementation, whether binary
 * is distributed together with or separately to that implementation, then
 * recipient must become an OpenCL Adopter and follow the published OpenCL
 * conformance process for that implementation, details at:
 * http://www.khronos.org/conformance/;
 *
 * The above copyright notice, the OpenCL trademark license, and this permission
 * notice shall be included in all copies or substantial portions of the
 * Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE USE OR OTHER DEALINGS IN
 * THE MATERIALS.
 *
 * OpenCL is a trademark of Apple Inc. used under license by Khronos.
 */

#include "icd.h"
#include <windows.h>
#include "icd_windows_hkr.h"
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
    // Get handle to GDI Runtime
    HMODULE h = LoadLibrary("gdi32.dll");
    if (h && GetProcAddress((HMODULE)h, "D3DKMTSubmitPresentBltToHwQueue")) // OS Version check
    {
        D3DKMT_ADAPTERINFO* pAdapterInfo;
        D3DKMT_ENUMADAPTERS2 EnumAdapters;
        NTSTATUS Status = STATUS_SUCCESS;

        char cszLibraryName[1024] = { 0 };
        EnumAdapters.NumAdapters = 0;
        EnumAdapters.pAdapters = NULL;
        PFND3DKMT_ENUMADAPTERS2 pEnumAdapters2 = (PFND3DKMT_ENUMADAPTERS2)GetProcAddress((HMODULE)h, "D3DKMTEnumAdapters2");
        if (!pEnumAdapters2)
        {
            FreeLibrary(h);
            return FALSE;
        }
        Status = pEnumAdapters2(&EnumAdapters);
        if (!NT_SUCCESS(Status) && (Status != STATUS_BUFFER_TOO_SMALL))
        {
            FreeLibrary(h);
            return FALSE;
        }
        pAdapterInfo = (D3DKMT_ADAPTERINFO*)malloc(sizeof(D3DKMT_ADAPTERINFO)*(EnumAdapters.NumAdapters));
        EnumAdapters.pAdapters = pAdapterInfo;
        Status = pEnumAdapters2(&EnumAdapters);
        if (!NT_SUCCESS(Status))
        {
            FreeLibrary(h);
            if (pAdapterInfo) free(pAdapterInfo);
            return FALSE;
        }
        const char* cszOpenCLRegKeyName = GetOpenCLRegKeyName();
        const int OpenCLRegKeyNameSize = (int)(strlen(cszOpenCLRegKeyName) + 1);
        for (UINT AdapterIndex = 0; AdapterIndex < EnumAdapters.NumAdapters; AdapterIndex++)
        {
            D3DDDI_QUERYREGISTRY_INFO QueryArgs = {0};
            D3DDDI_QUERYREGISTRY_INFO* pQueryArgs = &QueryArgs;
            D3DDDI_QUERYREGISTRY_INFO* pQueryBuffer = NULL;
            QueryArgs.QueryType = D3DDDI_QUERYREGISTRY_ADAPTERKEY;
            QueryArgs.QueryFlags.TranslatePath = TRUE;
            QueryArgs.ValueType = REG_SZ;
            MultiByteToWideChar(
                CP_ACP,
                0,
                cszOpenCLRegKeyName,
                OpenCLRegKeyNameSize,
                QueryArgs.ValueName,
                ARRAYSIZE(QueryArgs.ValueName));
            D3DKMT_QUERYADAPTERINFO QueryAdapterInfo = {0};
            QueryAdapterInfo.hAdapter = pAdapterInfo[AdapterIndex].hAdapter;
            QueryAdapterInfo.Type = KMTQAITYPE_QUERYREGISTRY;
            QueryAdapterInfo.pPrivateDriverData = &QueryArgs;
            QueryAdapterInfo.PrivateDriverDataSize = sizeof(QueryArgs);
            Status = D3DKMTQueryAdapterInfo(&QueryAdapterInfo);
            if (!NT_SUCCESS(Status))
            {
                // Continue trying to get as much info on each adapter as possible.
                // It's too late to return FALSE and claim WDDM2_4 enumeration is not available here.
                continue;
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
                    while ((*pWchar != L'\0') && (i<1023))
                    {
                        cszLibraryName[i] = (char)*pWchar;
                        i++;
                        pWchar++;
                    }
                    if (i < 1023) AdapterAdd(cszLibraryName, pAdapterInfo[AdapterIndex].AdapterLuid);
                }
            }
            if (pQueryBuffer) free(pQueryBuffer);
        }
        if (pAdapterInfo) free(pAdapterInfo);
        FreeLibrary(h);
        return TRUE;
    }
#endif
    return FALSE;
}
