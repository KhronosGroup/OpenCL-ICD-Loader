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

#include "icd.h"
#include "icd_envvars.h"

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>

static pthread_once_t initialized = PTHREAD_ONCE_INIT;

/*
 *
 * Vendor enumeration functions
 *
 */

// go through the list of vendors in the two configuration files
void khrIcdOsVendorsEnumerate(void)
{
    DIR *dir = NULL;
    struct dirent *dirEntry = NULL;
    const char* vendorPath = ICD_VENDOR_PATH;
    char* envPath = NULL;

    khrIcdVendorsEnumerateEnv();

    envPath = khrIcd_secure_getenv("OCL_ICD_VENDORS");
    if (NULL != envPath)
    {
        vendorPath = envPath;
    }

    dir = opendir(vendorPath);
    if (NULL == dir)
    {
        KHR_ICD_TRACE("Failed to open path %s, continuing\n", vendorPath);
    }
    else
    {
        // attempt to load all files in the directory
        for (dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir))
        {
            struct stat statBuff;
            const char* extension = ".icd";
            char* fileName = NULL;

            // make sure the file name ends in .icd
            if (strlen(extension) > strlen(dirEntry->d_name))
            {
                continue;
            }
            if (strcmp(dirEntry->d_name + strlen(dirEntry->d_name) - strlen(extension), extension))
            {
                continue;
            }

            // allocate space for the full path of the vendor library name
            fileName = malloc(strlen(dirEntry->d_name) + strlen(vendorPath) + 2);
            if (!fileName)
            {
                KHR_ICD_TRACE("Failed allocate space for ICD file path\n");
                continue;
            }
            sprintf(fileName, "%s/%s", vendorPath, dirEntry->d_name);

            if (stat(fileName, &statBuff))
            {
                KHR_ICD_TRACE("Failed stat for: %s, continuing\n", fileName);
                free(fileName);
                continue;
            }

            if (S_ISREG(statBuff.st_mode) || S_ISLNK(statBuff.st_mode))
            {
                FILE *fin = NULL;
                char* buffer = NULL;
                long bufferSize = 0;

                // open the file and read its contents
                fin = fopen(fileName, "r");
                if (!fin)
                {
                    free(fileName);
                    continue;
                }
                fseek(fin, 0, SEEK_END);
                bufferSize = ftell(fin);

                buffer = malloc(bufferSize+1);
                if (!buffer)
                {
                    free(fileName);
                    fclose(fin);
                    continue;
                }
                memset(buffer, 0, bufferSize+1);
                fseek(fin, 0, SEEK_SET);
                if (bufferSize != (long)fread(buffer, 1, bufferSize, fin))
                {
                    free(fileName);
                    free(buffer);
                    fclose(fin);
                    continue;
                }
                // ignore a newline at the end of the file
                if (buffer[bufferSize-1] == '\n') buffer[bufferSize-1] = '\0';

                // load the string read from the file
                khrIcdVendorAdd(buffer);

                free(fileName);
                free(buffer);
                fclose(fin);
            }
            else
            {
                KHR_ICD_TRACE("File %s is not a regular file nor symbolic link, continuing\n", fileName);
                free(fileName);
                continue;
            }
        }

        closedir(dir);
    }

    if (NULL != envPath)
    {
        khrIcd_free_getenv(envPath);
    }
#if defined(CL_ENABLE_LAYERS)
    khrIcdLayersEnumerateEnv();
#endif // defined(CL_ENABLE_LAYERS)
}

// go through the list of vendors only once
void khrIcdOsVendorsEnumerateOnce(void)
{
    pthread_once(&initialized, khrIcdOsVendorsEnumerate);
}

/*
 *
 * Dynamic library loading functions
 *
 */

// dynamically load a library.  returns NULL on failure
void *khrIcdOsLibraryLoad(const char *libraryName)
{
    void* ret = dlopen (libraryName, RTLD_NOW);
    if (NULL == ret)
    {
        KHR_ICD_TRACE("Failed to load driver because %s.\n", dlerror());
    }
    return ret;
}

// get a function pointer from a loaded library.  returns NULL on failure.
void *khrIcdOsLibraryGetFunctionAddress(void *library, const char *functionName)
{
    return dlsym(library, functionName);
}

// unload a library
void khrIcdOsLibraryUnload(void *library)
{
    dlclose(library);
}
