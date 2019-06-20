/*
 * Copyright (c) 2016-2019 The Khronos Group Inc.
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

#ifndef _ICD_ENVVARS_H_
#define _ICD_ENVVARS_H_

// Environment variables
#if defined(__linux__) || defined(__APPLE__)

static inline char *khrIcd_getenv(const char *name) {
    // No allocation of memory necessary for Linux.
    return getenv(name);
}

static inline char *khrIcd_secure_getenv(const char *name) {
#if defined(__APPLE__)
    // Apple does not appear to have a secure getenv implementation.
    // The main difference between secure getenv and getenv is that secure getenv
    // returns NULL if the process is being run with elevated privileges by a normal user.
    // The idea is to prevent the reading of malicious environment variables by a process
    // that can do damage.
    // This algorithm is derived from glibc code that sets an internal
    // variable (__libc_enable_secure) if the process is running under setuid or setgid.
    return geteuid() != getuid() || getegid() != getgid() ? NULL : khrIcd_getenv(name);
#else
// Linux
#ifdef HAVE_SECURE_GETENV
    return secure_getenv(name);
#elif defined(HAVE___SECURE_GETENV)
    return __secure_getenv(name);
#else
#pragma message(                                                                       \
    "Warning:  Falling back to non-secure getenv for environmental lookups!  Consider" \
    " updating to a different libc.")
    return khrIcd_getenv(name);
#endif
#endif
}

static inline void khrIcd_free_getenv(char *val) {
    // No freeing of memory necessary for Linux, but we should at least touch
    // val to get rid of compiler warnings.
    (void)val;
}

#elif defined(WIN32)

static inline char *khrIcd_getenv(const char *name) {
    char *retVal;
    DWORD valSize;

    valSize = GetEnvironmentVariableA(name, NULL, 0);

    // valSize DOES include the null terminator, so for any set variable
    // will always be at least 1. If it's 0, the variable wasn't set.
    if (valSize == 0) return NULL;

    // Allocate the space necessary for the registry entry
    retVal = (char *)malloc(valSize);

    if (NULL != retVal) {
        GetEnvironmentVariableA(name, retVal, valSize);
    }

    return retVal;
}

static inline char *khrIcd_secure_getenv(const char *name) {
    // No secure version for Windows as far as I know
    return khrIcd_getenv(name);
}

static inline void khrIcd_free_getenv(char *val) {
    free((void *)val);
}

#else

static inline char *khrIcd_getenv(const char *name) {
    // stub func
    (void)name;
    return NULL;
}
static inline void khrIcd_free_getenv(char *val) {
    // stub func
    (void)val;
}

#endif

#endif