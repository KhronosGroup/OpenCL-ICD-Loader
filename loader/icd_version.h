/*
 * Copyright (c) 2016-2020 The Khronos Group Inc.
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

#ifndef _ICD_VERSION_H_
#define _ICD_VERSION_H_

#define OPENCL_ICD_LOADER_VAL(_v) #_v
#define OPENCL_ICD_LOADER_TOSTRING(_d) OPENCL_ICD_LOADER_VAL(_d)
#define OPENCL_ICD_LOADER_VERSION_STRING \
    OPENCL_ICD_LOADER_TOSTRING(OPENCL_ICD_LOADER_VERSION_MAJOR) "." \
    OPENCL_ICD_LOADER_TOSTRING(OPENCL_ICD_LOADER_VERSION_MINOR) "." \
    OPENCL_ICD_LOADER_TOSTRING(OPENCL_ICD_LOADER_VERSION_REV)

#endif
