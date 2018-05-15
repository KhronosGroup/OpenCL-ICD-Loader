/*
 * Copyright (c) 2018 ManyCoreSoft Co., Ltd.
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
#include "icd_envvar.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static pthread_once_t initialized = PTHREAD_ONCE_INIT;

static const char *ParseIntegerList(const char *str, unsigned *numValuesRet, unsigned *valuesRet)
{
    unsigned numValues = 0;
    unsigned value;
    const char *p = str;

    numValues = 0;
    p = str;
    while ((*p >= '0' && *p <= '9') || *p == ',')
    {
        if (*p >= '0' && *p <= '9')
        {
            value = 0;
            for ( ; *p >= '0' && *p <= '9'; ++p)
            {
                value = value * 10 + (*p - '0');
            }
            if (valuesRet) valuesRet[numValues] = value;
            numValues++;
        }
        else
        {
            ++p;
        }
    }
    if (numValuesRet)
    {
        *numValuesRet = numValues;
    }
    return p;
}

static const char *ParseVisibilityEntry(const char *str)
{
    // e.g., foo.so:0:gpu:0,2
    //       foo.so:1:cpu:0
    //       foo.so:0:any:4,5
    //       foo.so:0:gpu (use all gpu devices in the platform)
    //       foo.so:0 (use all devices in the platform)
    size_t libraryLength = 0;
    char *library = NULL;
    unsigned platformIndex = 0;
    cl_device_type deviceType = CL_DEVICE_TYPE_ALL;
    unsigned numVisibleDevices = 0;
    unsigned *deviceIndices = NULL;
    const char *p = str;

    if (str == NULL || *str == '\0')
    {
        return NULL;
    }

    while (*p != '\0' && *p != ':') ++p;
    libraryLength = p - str;
    library = (char*)malloc(libraryLength + 1);
    if (!library)
    {
        KHR_ICD_TRACE("Failed to allocate memory\n");
        goto Cleanup;
    }
    strncpy(library, str, libraryLength);
    library[libraryLength] = '\0';

    if (*p != ':')
    {
        KHR_ICD_TRACE("Failed to parse OPENCL_VISIBLE_DEVICES\n");
        goto Cleanup;
    }
    ++p;

    do
    {
        if (*p >= '0' && *p <= '9')
        {
            platformIndex = platformIndex * 10 + (*p - '0');
        }
        else
        {
            KHR_ICD_TRACE("Failed to parse OPENCL_VISIBLE_DEVICES\n");
            goto Cleanup;
        }
        ++p;
    }
    while (*p != '\0' && *p != ':');

    if (*p != ':' || *(p + 1) == ':') goto Done;
    ++p;

    if (strncmp(p, "gpu", 3) == 0)
    {
        deviceType = CL_DEVICE_TYPE_GPU;
        p += 3;
    }
    else if (strncmp(p, "cpu", 3) == 0)
    {
        deviceType = CL_DEVICE_TYPE_CPU;
        p += 3;
    }
    else if (strncmp(p, "accelerator", 11) == 0)
    {
        deviceType = CL_DEVICE_TYPE_ACCELERATOR;
        p += 11;
    }
    else if (strncmp(p, "custom", 6) == 0)
    {
        deviceType = CL_DEVICE_TYPE_CUSTOM;
        p += 6;
    }
    else if (strncmp(p, "any", 3) == 0)
    {
        deviceType = CL_DEVICE_TYPE_ALL;
        p += 3;
    }
    else
    {
        KHR_ICD_TRACE("Failed to parse OPENCL_VISIBLE_DEVICES\n");
        goto Cleanup;
    }

    if (*p != ':' || *(p + 1) == ':') goto Done;
    ++p;

    ParseIntegerList(p, &numVisibleDevices, NULL);
    if (numVisibleDevices > 0)
    {
        deviceIndices = (unsigned*)malloc(sizeof(unsigned) * numVisibleDevices);
        if (!deviceIndices)
        {
            KHR_ICD_TRACE("Failed to allocate memory\n");
            goto Cleanup;
        }
    }
    p = ParseIntegerList(p, NULL, deviceIndices);

Done:
    khrIcdVisibilityAdd(library, platformIndex, deviceType, numVisibleDevices, deviceIndices);
    return p;

Cleanup:
    if (library) free(library);
    if (deviceIndices) free(deviceIndices);
    return NULL;
}

static void khrIcdOsGetOpenCLVisibleDevices(void)
{
    const char *env = getenv("OPENCL_VISIBLE_DEVICES");
    if (env == NULL || *env == '\0')
    {
        return;
    }

    while (*env != '\0')
    {
        if (*env == ':' && *(env + 1) == ':')
        {
           env += 2;
           continue;
        }

        env = ParseVisibilityEntry(env);
        if (!env) break;

        if (*env == '\0' || (*env == ':' && *(env + 1) == ':'))
        {
            // Do nothing
        }
        else
        {
            KHR_ICD_TRACE("Failed to parse OPENCL_VISIBLE_DEVICES\n");
            break;
        }
    }
}

void khrIcdOsGetOpenCLVisibleDevicesOnce(void)
{
    pthread_once(&initialized, khrIcdOsGetOpenCLVisibleDevices);
}

int khrIcdOsLibraryFileMatch(const char *name, const char *fileName)
{
    size_t nameLength = 0;
    size_t fileNameLength = 0;

    if (!name || !fileName) return 0;

    nameLength = strlen(name);
    fileNameLength = strlen(fileName);

    if (nameLength == fileNameLength)
    {
        return strcmp(name, fileName) == 0;
    }
    else if (nameLength < fileNameLength)
    {
        return fileName[fileNameLength - nameLength - 1] == '/' &&
               strcmp(name, fileName + (fileNameLength - nameLength)) == 0;
    }
    return 0;
}

