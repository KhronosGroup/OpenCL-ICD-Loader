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

#include "icd_trace.h"
#include "icd_library.h"
#include "icd_windows_formats.h"
#include <windows.h>

/*
 *
 * Dynamic library loading functions
 *
 */

// dynamically load a library.  returns NULL on failure
void *khrIcdOsLibraryLoad(const char *libraryName)
{
    HMODULE hTemp = LoadLibraryExA(libraryName, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    if (!hTemp && GetLastError() == ERROR_INVALID_PARAMETER)
    {
        hTemp = LoadLibraryExA(libraryName, NULL, 0);
    }
    if (!hTemp)
    {
        KHR_ICD_TRACE("Failed to load driver. Windows error code is %"PRIuDW".\n", GetLastError());
    }
    return (void*)hTemp;
}

// get a function pointer from a loaded library.  returns NULL on failure.
void *khrIcdOsLibraryGetFunctionAddress(void *library, const char *functionName)
{
    if (!library || !functionName)
    {
        return NULL;
    }
    return GetProcAddress( (HMODULE)library, functionName);
}

// unload a library.
void khrIcdOsLibraryUnload(void *library)
{
    FreeLibrary( (HMODULE)library);
}


