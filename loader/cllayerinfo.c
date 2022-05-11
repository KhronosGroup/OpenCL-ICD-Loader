/*
 * Copyright (c) 2022 The Khronos Group Inc.
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
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl_layer.h>

#define CL_LAYER_NAME               0x4241
#define CL_LAYER_OPTIONS            0x4242

typedef struct {
    const char *name;
    const char *value;
    const char *default_value;
    const char *description;
} cl_layer_option;

extern void khrIcdInitializeTrace(void);

void printLayerInfo(const struct KHRLayer *layer) {
    cl_layer_api_version api_version = 0;
    pfn_clGetLayerInfo p_clGetLayerInfo = (pfn_clGetLayerInfo)(size_t)layer->p_clGetLayerInfo;
    cl_int result = CL_SUCCESS;
    size_t sz;

    printf("%s:\n", layer->libraryName);
    result = p_clGetLayerInfo(CL_LAYER_API_VERSION, sizeof(api_version), &api_version, NULL);
    if (CL_SUCCESS == result)
        printf("\tCL_LAYER_API_VERSION: %d\n", (int)api_version);

    result = p_clGetLayerInfo(CL_LAYER_NAME, 0, NULL, &sz);
    if (CL_SUCCESS == result)
    {
        char *name = (char *)malloc(sz);
        if (name)
        {
            result = p_clGetLayerInfo(CL_LAYER_NAME, sz, name, NULL);
            if (CL_SUCCESS == result)
                 printf("\tCL_LAYER_NAME: %s\n", name);
            free(name);
        }
    }
    result = p_clGetLayerInfo(CL_LAYER_OPTIONS, 0, NULL, &sz);
    if (CL_SUCCESS == result)
    {
        cl_layer_option *options = (cl_layer_option *)malloc(sz);
        if (options)
        {
            result = p_clGetLayerInfo(CL_LAYER_OPTIONS, sz, options, NULL);
            if (CL_SUCCESS == result)
            {
                size_t i = 0;
                printf("\tCL_LAYER_OPTIONS:\n");
                while (options[i].name)
                {
                    if (options[i].description)
                        printf("\t\t# %s\n", options[i].description);
                    printf("\t\t%s = %s # (default: %s)\n", options[i].name, options[i].value, options[i].default_value);
                    i++;
                }
            }
            free(options);
        }
    }
}

int main (int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    khrIcdInitialize();
    if (!khrFirstLayer)
        return 0;
    const struct KHRLayer *layer = khrFirstLayer;
    while (layer) {
        printLayerInfo(layer);
        layer = layer->next;
    }
    return 0;
}
