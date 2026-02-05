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

#ifndef _ICD_TRACE_H_
#define _ICD_TRACE_H_

#include <stdio.h>

extern int khrEnableTrace;

// internal tracing macros
#define KHR_ICD_TRACE(...) \
do \
{ \
    if (khrEnableTrace) \
    { \
        fprintf(stderr, "KHR ICD trace at %s:%d: ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
    } \
} while (0)

#ifdef _WIN32
#define KHR_ICD_WIDE_TRACE(...) \
do \
{ \
    if (khrEnableTrace) \
    { \
        fwprintf(stderr, L"KHR ICD trace at %hs:%d: ", __FILE__, __LINE__); \
        fwprintf(stderr, __VA_ARGS__); \
    } \
} while (0)

#else
#define KHR_ICD_WIDE_TRACE(...)
#endif

#endif
