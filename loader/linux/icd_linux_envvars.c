/*
 * Copyright (c) 2016-2026 The Khronos Group Inc.
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

// for secure_getenv():
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "icd_cmake_config.h"

#include "icd_envvars.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static char *khrIcd_dup(const char *val)
{
    if (!val)
        return NULL;
    size_t sz = strlen(val) + 1;
    char *ret = malloc(sz);
    if (!ret)
        return NULL;
    memcpy(ret, val, sz);
    return ret;
}

char *khrIcd_getenv(const char *name) {
    // A copy of the variable is returned in order to avoid modification
    return khrIcd_dup(getenv(name));
}

char *khrIcd_secure_getenv(const char *name) {
#if defined(__APPLE__) || defined(__QNXNTO__)
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
    return khrIcd_dup(secure_getenv(name));
#elif defined(HAVE___SECURE_GETENV)
    return khrIcd_dup(__secure_getenv(name));
#else
#pragma message(                                                                       \
    "Warning:  Falling back to non-secure getenv for environmental lookups!  Consider" \
    " updating to a different libc.")
    return khrIcd_getenv(name);
#endif
#endif
}

void khrIcd_free_getenv(char *val) {
    free((void*)val);
}
