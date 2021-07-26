/*
 * Copyright (c) 2021 The Khronos Group Inc.
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
#include "icd_device_visible.h"
#include "icd_envvars.h"
#include "icd_dispatch.h"
#include <CL/cl.h>
#include <stdlib.h>
#include <string.h>

static KHRVisibility *khrVisibilities = NULL;

void khrIcdVisibilityAdd(char *library, unsigned platformIndex, cl_device_type deviceType,
                         unsigned numVisibleDevices, unsigned *deviceIndices)
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

void khrIcdVisibilitySetPlatform(const char *libraryFile, unsigned index, cl_platform_id platform)
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

static char* ParseIntegerList(char* str, unsigned* numValuesRet, unsigned* valuesRet)
{
    unsigned numValues = 0;
    unsigned value;
    char* p = str;

    numValues = 0;
    p = str;
    while ((*p >= '0' && *p <= '9') || *p == ',')
    {
        if (*p >= '0' && *p <= '9')
        {
            value = 0;
            for (; *p >= '0' && *p <= '9'; ++p)
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


static char* ParseVisibilityEntry(char* str)
{
    // e.g., d:\\foo.dll,0,gpu,0,2
    //       d:\\foo1.dll,0,cpu,0::d:\\foo2.dll,0,any,4,5
    //       d:\\foo.dll,0,gpu (use all gpu devices in this platform)
    //       d:\\foo.dll,0     (use all devices in the platform)
    size_t libraryLength = 0;
    char* library = NULL;
    unsigned platformIndex = 0;
    cl_device_type deviceType = CL_DEVICE_TYPE_ALL;
    unsigned numVisibleDevices = 0;
    unsigned* deviceIndices = NULL;
    char* p = str;

    if (str == NULL || *str == '\0')
    {
        return NULL;
    }
    // parse library / file name.
    while (*p != '\0' && *p != ',') ++p;
    libraryLength = p - str;
    library = (char*)malloc(libraryLength + 1);
    if (!library)
    {
        KHR_ICD_TRACE("Failed to allocate memory\n");
        goto Cleanup;
    }
    strncpy(library, str, libraryLength);
    library[libraryLength] = '\0';

    if (*p != ',')
    {
        KHR_ICD_TRACE("OPENCL_VISIBLE_DEVICES only provides library name. Failed to parse.\n");
        goto Cleanup;
    }
    ++p;
    // Get platform index.
    do
    {
        if (*p >= '0' && *p <= '9')
        {
            platformIndex = platformIndex * 10 + (*p - '0');
        }
        else
        {
            KHR_ICD_TRACE("Failed to parse platform index in OPENCL_VISIBLE_DEVICES\n");
            goto Cleanup;
        }
        ++p;
    } while (*p != '\0' && *p != ',');

    if (*p != ',' || *(p + 1) == ',') goto Done;

    ++p;
    // Get device type.
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

    if (*p != ',' || *(p + 1) == ',') goto Done;
    ++p;
    // Get device indexs.
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

void khrIcdOsGetOpenCLVisibleDevices(void)
{
    char* env = khrIcd_getenv("OPENCL_VISIBLE_DEVICES");
    char* envOrig = env;

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

        if (*env != '\0' && (*env != ':' && *(env + 1) != ':'))
        {
            KHR_ICD_TRACE("Failed to parse OPENCL_VISIBLE_DEVICES\n");
            break;
        }
    }
    // env != null
    khrIcd_free_getenv(envOrig);
}

int khrIcdOsLibraryFileMatch(const char* name, const char* fileName)
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
        return fileName[fileNameLength - nameLength - 1] == DIRECTORY_SYMBOL &&
            strcmp(name, fileName + (fileNameLength - nameLength)) == 0;
    }
    return 0;
}
