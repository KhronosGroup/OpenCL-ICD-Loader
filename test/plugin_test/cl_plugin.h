/*
 * Copyright (c) 2026 The Khronos Group Inc.
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
#ifndef _CL_PLUGIN_H_
#define _CL_PLUGIN_H_

#define PLUGIN_INIT plugin_init
#define XSTRING(x) TO_STRING(x)
#define TO_STRING(x) #x
#define PLUGIN_INIT_NAME XSTRING(PLUGIN_INIT)

#define PLUGIN_SUCCESS 0
#define PLUGIN_ERROR   1

typedef int plugin_init_fn(void);
typedef plugin_init_fn *plugin_init_pfn;

#endif
