/*
 * Copyright (c) 2017 The Khronos Group Inc.
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
#include "icd_windows_hkr.h"
#include <windows.h>
#include <SetupAPI.h>
#include <devguid.h>

#define KHR_SAFE_RELEASE(mem)       \
    do                              \
    {                               \
        free(mem);                  \
        mem = NULL;                 \
    } while (0)

static const char HKR_PREFIX[] = "SYSTEM\\CurrentControlSet\\Control\\Class\\";
#ifdef _WIN64
static const char OPENCL_REG_SUB_KEY[] = "OpenCLDriverName";
#else
static const char OPENCL_REG_SUB_KEY[] = "OpenCLDriverNameWow"
#endif

// Given a display adapter HKR (GUID\000x), returns the full registry path
// to that adapter (i.e. SYSTEM\...\Class\GUID\000x).
static char* khrGetFullHKRPath(const char* hkr)
{
    char* cszHkrFullPath;
    size_t szHkrFullPath;
    errno_t ret;

    szHkrFullPath = (sizeof(HKR_PREFIX) - 1) + strlen(hkr) + 1;
    cszHkrFullPath = malloc(szHkrFullPath);
    if (!cszHkrFullPath)
    {
        KHR_ICD_TRACE("failed to allocate memory\n");
        return NULL;
    }

    RtlZeroMemory(cszHkrFullPath, szHkrFullPath);

    ret = strcat_s(cszHkrFullPath, szHkrFullPath, HKR_PREFIX);
    KHR_ICD_ASSERT(ret == 0);
    ret = strcat_s(cszHkrFullPath, szHkrFullPath, hkr);
    KHR_ICD_ASSERT(ret == 0);

    return cszHkrFullPath;
}

// Returns a string property for a device or NULL otherwise.
// Caller must release the buffer returned by this function.
static char* khrGetDeviceStringProperty(
    HDEVINFO deviceInfoSet,
    PSP_DEVINFO_DATA deviceInfoData,
    DWORD dwProperty)
{
    char* cszProperty;
    DWORD dwPropertySize;
    DWORD dwReqSize;
    DWORD dwDataType;

    dwPropertySize = 1024;
    cszProperty = malloc(dwPropertySize);
    if (!cszProperty)
    {
        KHR_ICD_TRACE("failed to allocate memory\n");
        return NULL;
    }

    while (!SetupDiGetDeviceRegistryProperty(
        deviceInfoSet,
        deviceInfoData,
        dwProperty,
        &dwDataType,
        (LPBYTE)cszProperty,
        dwPropertySize,
        &dwReqSize))
    {
        if (ERROR_INSUFFICIENT_BUFFER != GetLastError())
        {
            goto failed;
        }

        if (REG_SZ != dwDataType)
        {
            goto failed;
        }

        dwPropertySize = dwReqSize;
        free(cszProperty);
        cszProperty = malloc(dwPropertySize);
        if (!cszProperty)
        {
            KHR_ICD_TRACE("failed to allocate memory\n");
            goto failed;
        }
    }

    return cszProperty;

failed:
    if (cszProperty)
    {
        free(cszProperty);
    }

    return NULL;
}

// Enumerates each of the vendors (display adapters) HKR entries
// and searches for OpenCLDriverName entry.
BOOL CALLBACK khrIcdOsVendorsEnumerateHKR(void)
{
    SP_DEVINFO_DATA deviceInfoData = { 0 };
    HDEVINFO deviceInfoSet;
    DWORD dwError;
    DWORD dwDeviceIndex = 0;
    char *hwId, *devDesc, *hkr, *fullHkr;
    HKEY hkrKey = NULL;

    deviceInfoSet = SetupDiGetClassDevs(
        &GUID_DEVCLASS_DISPLAY,
        NULL,
        NULL,
        DIGCF_PRESENT);

    KHR_ICD_ASSERT(INVALID_HANDLE_VALUE != deviceInfoSet);

    if (INVALID_HANDLE_VALUE == deviceInfoSet)
    {
        dwError = GetLastError();
        KHR_ICD_TRACE("Failed to get display adapter class device instance %d\n", dwError);
        return FALSE;
    }

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    hwId = devDesc = hkr = fullHkr = NULL;

    KHR_ICD_TRACE("Enumerating OpenCL ICDs HKR entries...\n");

    while (SetupDiEnumDeviceInfo(
        deviceInfoSet,
        dwDeviceIndex,
        &deviceInfoData))
    {
        LSTATUS result;
        DWORD dwLibraryNameType = 0;
        char cszOclPath[MAX_PATH] = { '\0' };
        DWORD dwOclPathSize = sizeof(cszOclPath);

        dwDeviceIndex++;

        hwId = khrGetDeviceStringProperty(
            deviceInfoSet,
            &deviceInfoData,
            SPDRP_HARDWAREID);

        if (!hwId)
        {
            KHR_ICD_TRACE("Failed to get HW ID, continuing\n");
            goto NextIter;
        }

        devDesc = khrGetDeviceStringProperty(
            deviceInfoSet,
            &deviceInfoData,
            SPDRP_FRIENDLYNAME);

        if (!devDesc)
        {
            devDesc = khrGetDeviceStringProperty(
                deviceInfoSet,
                &deviceInfoData,
                SPDRP_DEVICEDESC);
        }

        if (!devDesc)
        {
            KHR_ICD_TRACE("Failed to get device description, continuing\n");
            goto NextIter;
        }

        hkr = khrGetDeviceStringProperty(
            deviceInfoSet,
            &deviceInfoData,
            SPDRP_DRIVER);

        if (!hkr)
        {
            KHR_ICD_TRACE("Failed to get HKR, continuing\n");
            goto NextIter;
        }

        fullHkr = khrGetFullHKRPath(hkr);
        if (!fullHkr)
        {
            KHR_ICD_TRACE("Failed to get fullHkr, continuing\n");
            goto NextIter;
        }

        // FIXME: we only really care about `hkr` and `fullHkr`, the rest is nice for
        //        diagnostics but probably should not be fetched (for performance).
        KHR_ICD_TRACE("%d) Device HW ID: %s\n", dwDeviceIndex, hwId);
        KHR_ICD_TRACE("   Device Description: %s\n", devDesc);
        KHR_ICD_TRACE("   HKR: %s\n\n", hkr);
        KHR_ICD_TRACE("   Full HKR: %s\n\n", fullHkr);

        KHR_ICD_TRACE("Opening key %s...\n", fullHkr);
        result = RegOpenKeyEx(
            HKEY_LOCAL_MACHINE,
            fullHkr,
            0,
            KEY_READ,
            &hkrKey);
        if (ERROR_SUCCESS != result)
        {
            KHR_ICD_TRACE("Failed to open key %s, continuing\n", fullHkr);
            goto NextIter;
        }

        result = RegQueryValueEx(
            hkrKey,
            OPENCL_REG_SUB_KEY,
            NULL,
            &dwLibraryNameType,
            (LPBYTE)cszOclPath,
            &dwOclPathSize);
        if (ERROR_SUCCESS != result)
        {
            KHR_ICD_TRACE("Failed to open sub key %s, continuing\n", OPENCL_REG_SUB_KEY);
            goto NextIter;
        }

        result = RegCloseKey(hkrKey);
        if (ERROR_SUCCESS != result)
        {
            KHR_ICD_TRACE("Failed to close sub key %s, ignoring\n", OPENCL_REG_SUB_KEY);
        }

        if (REG_MULTI_SZ != dwLibraryNameType)
        {
            KHR_ICD_TRACE("Unexpected registry entry! continuing\n");
            goto NextIter;
        }
        KHR_ICD_TRACE("   Value: %s\n\n", cszOclPath);

        khrIcdVendorAdd(cszOclPath);

    NextIter:
        KHR_SAFE_RELEASE(hwId);
        KHR_SAFE_RELEASE(devDesc);
        KHR_SAFE_RELEASE(hkr);
        KHR_SAFE_RELEASE(fullHkr);
    }

    KHR_ICD_ASSERT(ERROR_NO_MORE_ITEMS == GetLastError() &&
                   "Device enumeration failed unexpectedly");

    if (deviceInfoSet)
        (void)SetupDiDestroyDeviceInfoList(deviceInfoSet);

    return TRUE;
}
