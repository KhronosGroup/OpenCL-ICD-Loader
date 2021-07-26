/*
 * Copyright (c) 2016-2021 The Khronos Group Inc.
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

#ifndef _ICD_DEVICE_VISIBLE_H_
#define _ICD_DEVICE_VISIBLE_H_

#include <CL/cl.h>

typedef struct KHRVisibilityRec KHRVisibility;

struct KHRVisibilityRec {
  char *library;
  unsigned platformIndex;
  cl_device_type deviceType;
  unsigned numVisibleDevices;
  unsigned *deviceIndices;

  cl_platform_id platformID;
  cl_device_id *deviceIDs;

  KHRVisibility *next;
};

int khrIcdOsLibraryFileMatch(const char *name, const char *fileName);

void khrIcdVisibilityAdd(char *library, unsigned platformIndex,
                         cl_device_type deviceType, unsigned numVisibleDevices,
                         unsigned *deviceIndices);
void khrIcdVisibilityReplaceLibraryName(const char *oldName,
                                        const char *newName);
void khrIcdVisibilitySetPlatform(const char *libraryFile, unsigned index,
                                 cl_platform_id platform);

int khrIcdCheckLibraryVisible(const char *libraryFile);
int khrIcdCheckPlatformVisible(const char *libraryFile, unsigned index);
int khrIcdCheckDeviceVisible(cl_platform_id platform, cl_device_id device);

void khrIcdOsGetOpenCLVisibleDevices(void);
#endif
