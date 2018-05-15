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
#include "icd_dispatch.h"
#include <CL/cl.h>
#include <stdlib.h>
#include <string.h>

static KHRVisibility *khrVisibilities = NULL;

void khrIcdVisibilityAdd(char *library, unsigned platformIndex, cl_device_type deviceType, unsigned numVisibleDevices, unsigned *deviceIndices)
{
    KHRVisibility *visibility = NULL;

    visibility = (KHRVisibility*)malloc(sizeof(*visibility));
    if (!visibility)
    {
        KHR_ICD_TRACE("Failed to allocate memory\n");
        return;
    }
    memset(visibility, 0, sizeof(*visibility));

    visibility->library = library;
    visibility->platformIndex = platformIndex;
    visibility->deviceType = deviceType;
    visibility->numVisibleDevices = numVisibleDevices;
    visibility->deviceIndices = deviceIndices;

    if (numVisibleDevices > 0)
    {
        visibility->deviceIDs = (cl_device_id*)malloc(sizeof(cl_device_id) * numVisibleDevices);
        if (!visibility->deviceIDs)
        {
            KHR_ICD_TRACE("Failed to allocate memory\n");
            free(visibility);
            return;
        }
        memset(visibility->deviceIDs, 0, sizeof(cl_device_id) * numVisibleDevices);
    }

    // add this entry at the tail of the list
    {
        KHRVisibility **prevNextPointer = NULL;
        for (prevNextPointer = &khrVisibilities; *prevNextPointer; prevNextPointer = &((*prevNextPointer)->next));
        *prevNextPointer = visibility;
    }
}

void khrIcdVisibilityReplaceLibraryName(const char *oldName, const char *newName)
{
    KHRVisibility *iterator;
    for (iterator = khrVisibilities; iterator; iterator = iterator->next)
    {
        if (strcmp(iterator->library, oldName) == 0)
        {
            char *oldBuffer = iterator->library;
            char *buffer = (char*)malloc(strlen(newName) + 1);
            if (!buffer)
            {
                KHR_ICD_TRACE("Failed to allocate memory\n");
                continue;
            }
            strcpy(buffer, newName);

            iterator->library = buffer;
            free(oldBuffer);
        }
    }
}

void khrIcdVisibilitySetPlatform(char *libraryFile, unsigned index, cl_platform_id platform)
{
    KHRVisibility *iterator;
    for (iterator = khrVisibilities; iterator; iterator = iterator->next)
    {
        if (khrIcdOsLibraryFileMatch(iterator->library, libraryFile) &&
            iterator->platformIndex == index &&
            iterator->platformID == NULL)
        {
            cl_uint numDevices = 0;
            cl_device_id *devices = NULL;
            cl_int result;
            unsigned i;

            iterator->platformID = platform;
            if (iterator->numVisibleDevices == 0)
            {
                continue;
            }

            result = platform->dispatch->clGetDeviceIDs(platform, iterator->deviceType, 0, NULL, &numDevices);
            if (CL_SUCCESS != result)
            {
                continue;
            }

            devices = (cl_device_id*)malloc(sizeof(cl_device_id) * numDevices);
            if (!devices)
            {
                continue;
            }
            result = platform->dispatch->clGetDeviceIDs(platform, iterator->deviceType, numDevices, devices, NULL);
            if (CL_SUCCESS != result)
            {
                free(devices);
                continue;
            }

            for (i = 0; i < iterator->numVisibleDevices; ++i)
            {
                if (iterator->deviceIndices[i] < numDevices)
                {
                    iterator->deviceIDs[i] = devices[iterator->deviceIndices[i]];
                }
                else
                {
                    iterator->deviceIDs[i] = NULL;
                }
            }
        }
    }
}

int khrIcdCheckLibraryVisible(const char *libraryFile)
{
    KHRVisibility *iterator;
    if (!khrVisibilities) return 1;
    for (iterator = khrVisibilities; iterator; iterator = iterator->next)
    {
        if (khrIcdOsLibraryFileMatch(iterator->library, libraryFile))
        {
            return 1;
        }
    }
    return 0;
}

int khrIcdCheckPlatformVisible(const char *libraryFile, unsigned index)
{
    KHRVisibility *iterator;
    if (!khrVisibilities) return 1;
    for (iterator = khrVisibilities; iterator; iterator = iterator->next)
    {
        if (khrIcdOsLibraryFileMatch(iterator->library, libraryFile) &&
            iterator->platformIndex == index)
        {
            return 1;
        }
    }
    return 0;
}

int khrIcdCheckDeviceVisible(cl_platform_id platform, cl_device_id device)
{
    KHRVisibility *iterator;
    unsigned i;
    if (!khrVisibilities) return 1;
    for (iterator = khrVisibilities; iterator; iterator = iterator->next)
    {
        if (iterator->platformID == platform)
        {
            if (iterator->numVisibleDevices == 0)
            {
                return 1;
            }
            for (i = 0; i < iterator->numVisibleDevices; ++i)
            {
                if (iterator->deviceIDs[i] == device)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

