/*
 * Copyright (c) 2020 The Khronos Group Inc.
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

#include "icd_print_layer.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define CL_LAYER_NAME               0x4241
#define CL_LAYER_OPTIONS            0x4242

typedef struct {
    const char *name;
    const char *value;
    const char *default_value;
    const char *description;
} cl_layer_option;

struct _cl_icd_dispatch dispatch;

const struct _cl_icd_dispatch *tdispatch;

static cl_layer_api_version api_version = CL_LAYER_API_VERSION_100;
static const char name[] = "print_layer";

static bool option_a = false;
static float option_b = 0.0;

static cl_layer_option options_strings[] = {
  { "option_a", NULL, NULL, "Test option a" },
  { "option_b", NULL, NULL, "Test option b" },
  { NULL, NULL, NULL, NULL}
};

static void fill_default_options() {
  size_t sz = 0;
  options_strings[0].default_value = option_a ? "true" : "false";
  sz = snprintf(NULL, 0, "%f", option_b);
  char *str = (char *)malloc(sz);
  if (str) {
    snprintf(str, sz, "%f", option_b);
    options_strings[1].default_value = str;
  }
}

static void fill_options() {
  size_t sz = 0;
  options_strings[0].value = option_a ? "true" : "false";
  sz = snprintf(NULL, 0, "%f", option_b);
  char *str = (char *)malloc(sz);
  if (str) {
    snprintf(str, sz, "%f", option_b);
    options_strings[1].value = str;
  }
}

static inline cl_int
set_param_value(
    size_t      param_value_size,
    void       *param_value,
    size_t     *param_value_size_ret,
    size_t      src_size,
    const void *src) {
  if (param_value && param_value_size < src_size)
    return CL_INVALID_VALUE;
  if (param_value)
    memcpy(param_value, src, src_size);
  if (param_value_size_ret)
    *param_value_size_ret = src_size;
  return CL_SUCCESS;
}

CL_API_ENTRY cl_int CL_API_CALL
clGetLayerInfo(
    cl_layer_info  param_name,
    size_t         param_value_size,
    void          *param_value,
    size_t        *param_value_size_ret) {
  size_t sz = 0;
  const void *src = NULL;
  if (param_value_size && !param_value)
    return CL_INVALID_VALUE;
  if (!param_value && !param_value_size_ret)
    return CL_INVALID_VALUE;
  switch (param_name) {
  case CL_LAYER_API_VERSION:
    sz = sizeof(api_version);
    src = &api_version;
    break;
  case CL_LAYER_NAME:
    sz = sizeof(name);
    src = name;
    break;
  case CL_LAYER_OPTIONS:
    sz = sizeof(options_strings);
    src = options_strings;
    break;
  default:
    return CL_INVALID_VALUE;
  }
  return set_param_value(param_value_size, param_value, param_value_size_ret, sz, src);
}

CL_API_ENTRY cl_int CL_API_CALL
clInitLayer(
    cl_uint                         num_entries,
    const struct _cl_icd_dispatch  *target_dispatch,
    cl_uint                        *num_entries_out,
    const struct _cl_icd_dispatch **layer_dispatch_ret) {
  if (!target_dispatch || !layer_dispatch_ret ||!num_entries_out || num_entries < sizeof(dispatch)/sizeof(dispatch.clGetPlatformIDs))
    return CL_INVALID_VALUE;

  _init_dispatch();

  tdispatch = target_dispatch;
  *layer_dispatch_ret = &dispatch;
  *num_entries_out = sizeof(dispatch)/sizeof(dispatch.clGetPlatformIDs);

  fill_default_options();
  // Parse option there
  option_a = true;
  option_b = 1.0;
  fill_options();
  return CL_SUCCESS;
}


