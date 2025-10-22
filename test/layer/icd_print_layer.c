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

#if !defined(CL_LAYER_PROPERTIES_LIST_END)
typedef cl_properties cl_layer_properties;

#define CL_LAYER_PROPERTIES_LIST_END         ((cl_layer_properties)0)
#endif //!defined(CL_LAYER_PROPERTIES_LIST_END)

const struct _cl_icd_dispatch *tdispatch;

static cl_layer_api_version api_version = CL_LAYER_API_VERSION_100;

static const char name[] = "print_layer";

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
  default:
    return CL_INVALID_VALUE;
  }
  return set_param_value(param_value_size, param_value, param_value_size_ret, sz, src);
}

static void deinitLayerAtExit(void) {
  printf("Cleaning up %s, API version: %d\n", name, api_version);
  printf("atexit() deinitialization\n");
}

static void deinitLayerFunction(void) {
  printf("Cleaning up %s, API version: %d\n", name, api_version);
  printf("Function deinitialization\n");
}

static cl_int
checkAndInitDispatch(
    cl_uint                         num_entries,
    const struct _cl_icd_dispatch  *target_dispatch,
    cl_uint                        *num_entries_ret,
    const struct _cl_icd_dispatch **layer_dispatch_ret) {
  if (!target_dispatch || !layer_dispatch_ret || !num_entries_ret || num_entries < sizeof(dispatch)/sizeof(dispatch.clGetPlatformIDs))
    return CL_INVALID_VALUE;

  tdispatch = target_dispatch;
  *layer_dispatch_ret = &dispatch;
  *num_entries_ret = sizeof(dispatch)/sizeof(dispatch.clGetPlatformIDs);

  return CL_SUCCESS;
}

CL_API_ENTRY cl_int CL_API_CALL
clInitLayer(
    cl_uint                         num_entries,
    const struct _cl_icd_dispatch  *target_dispatch,
    cl_uint                        *num_entries_ret,
    const struct _cl_icd_dispatch **layer_dispatch_ret)
{
  cl_int result = CL_SUCCESS;
  result = checkAndInitDispatch(num_entries, target_dispatch, num_entries_ret, layer_dispatch_ret);
  if (CL_SUCCESS != result)
    return result;

  atexit(deinitLayerAtExit);
  return CL_SUCCESS;
}

CL_API_ENTRY cl_int CL_API_CALL
clInitLayerWithProperties(
    cl_uint                    num_entries,
    const cl_icd_dispatch     *target_dispatch,
    cl_uint                   *num_entries_ret,
    const cl_icd_dispatch    **layer_dispatch_ret,
    const cl_layer_properties *properties)
{
  (void)properties;
  return checkAndInitDispatch(num_entries, target_dispatch, num_entries_ret, layer_dispatch_ret);
}

CL_API_ENTRY cl_int CL_API_CALL
clDeinitLayer(void) {
  deinitLayerFunction();
  return CL_SUCCESS;
}
