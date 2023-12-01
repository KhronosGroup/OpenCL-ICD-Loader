/*
 * Copyright (c) 2012-2020 The Khronos Group Inc.
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
#include "icd_dispatch.h"
#include "icd_version.h"

#include <stdlib.h>
#include <string.h>

static clGetICDLoaderInfoOCLICD_t clGetICDLoaderInfoOCLICD;
cl_int CL_API_CALL
clGetICDLoaderInfoOCLICD(
    cl_icdl_info param_name,
    size_t       param_value_size,
    void *       param_value,
    size_t *     param_value_size_ret)
{
    static const char cl_icdl_OCL_VERSION[] = OPENCL_ICD_LOADER_OCL_VERSION_STRING;
    static const char cl_icdl_VERSION[]     = OPENCL_ICD_LOADER_VERSION_STRING;
    static const char cl_icdl_NAME[]        = OPENCL_ICD_LOADER_NAME_STRING;
    static const char cl_icdl_VENDOR[]      = OPENCL_ICD_LOADER_VENDOR_STRING;
    size_t            pvs;
    void *            pv;

#define KHR_ICD_CASE_STRING_PARAM_NAME(name)                                   \
    case CL_ICDL_ ## name:                                                     \
        pvs = strlen(cl_icdl_ ## name) + 1;                                    \
        pv = (void *)cl_icdl_ ## name;                                         \
        break

    switch (param_name) {
    KHR_ICD_CASE_STRING_PARAM_NAME(OCL_VERSION);
    KHR_ICD_CASE_STRING_PARAM_NAME(VERSION);
    KHR_ICD_CASE_STRING_PARAM_NAME(NAME);
    KHR_ICD_CASE_STRING_PARAM_NAME(VENDOR);
    default:
        return CL_INVALID_VALUE;
    }

#undef KHR_ICD_CASE_PARAM_NAME

    if (param_value) {
        if (param_value_size < pvs)
            return CL_INVALID_VALUE;
        memcpy(param_value, pv, pvs);
    }
    if (param_value_size_ret != NULL)
        *param_value_size_ret = pvs;
    return CL_SUCCESS;
}

#if defined(CL_ENABLE_LOADER_MANAGED_DISPATCH)

static clCreateInstanceKHR_t clCreateInstanceKHR;
cl_instance_khr CL_API_CALL
clCreateInstanceKHR(
    const cl_instance_properties_khr *properties,
    cl_int *errcode_ret)
{
#define KHR_ICD_ALLOC_AND_ZERO(var, num, type)                                 \
    do                                                                         \
    {                                                                          \
        var = (type *)malloc(num * sizeof(type));                              \
        if (!var)                                                              \
        {                                                                      \
           err = CL_OUT_OF_HOST_MEMORY;                                        \
           goto error;                                                         \
        }                                                                      \
        memset(var, 0, num * sizeof(type));                                    \
    } while (0)

    (void) properties;
    cl_int err = CL_SUCCESS;
    cl_instance_khr instance = NULL;
    cl_uint num_platforms = 0;

    if (!khrIcdVendors)
    {
       err = CL_PLATFORM_NOT_FOUND_KHR;
       goto error;
    }

    for (KHRicdVendor* vendor = khrIcdVendors; vendor; vendor = vendor->next)
    {
        if (vendor->clIcdCreateInstancePlatform)
            num_platforms++;
    }

    KHR_ICD_ALLOC_AND_ZERO(instance, 1, struct _cl_instance_khr);
    KHR_ICD_ALLOC_AND_ZERO(instance->platforms, num_platforms, cl_platform_id);
    KHR_ICD_ALLOC_AND_ZERO(instance->vendors, num_platforms, KHRicdVendor *);
    KHR_ICD_ALLOC_AND_ZERO(instance->dispDatas, num_platforms, struct KHRDisp);

    num_platforms = 0;
    for (KHRicdVendor* vendor = khrIcdVendors; vendor; vendor = vendor->next)
    {
        if (vendor->clIcdCreateInstancePlatform)
        {
            cl_platform_id platform;
            platform = vendor->clIcdCreateInstancePlatform(vendor->platform, &err);
            if (CL_SUCCESS != err)
                continue;
            vendor->clIcdSetPlatformDispatchData(platform, instance->dispDatas + num_platforms);
            instance->platforms[num_platforms] = platform;
            instance->vendors[num_platforms] = vendor;
            memcpy(instance->dispDatas + num_platforms, &vendor->dispData, sizeof(struct KHRDisp));
            num_platforms++;
        }
    }

    if (!num_platforms)
    {
        err = CL_PLATFORM_NOT_FOUND_KHR;
        goto error;
    }

    instance->num_platforms = num_platforms;

    if (errcode_ret)
        *errcode_ret = CL_SUCCESS;
    return instance;
error:
    if (instance)
    {
        free(instance->dispDatas);
        free(instance->vendors);
        free(instance->platforms);
        free(instance);
    }
    if (errcode_ret)
        *errcode_ret = err;
#undef KHR_ICD_ALLOC_AND_ZERO
    return NULL;
}

static clDestroyInstanceKHR_t clDestroyInstanceKHR;
cl_int CL_API_CALL
clDestroyInstanceKHR(
    cl_instance_khr instance)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(instance, CL_INVALID_INSTANCE_KHR);
    for (cl_uint i = 0; i < instance->num_platforms; i++)
        instance->vendors[i]->clIcdDestroyInstancePlatform(instance->platforms[i]);
    free(instance->dispDatas);
    free(instance->vendors);
    free(instance->platforms);
    free(instance);
    return CL_SUCCESS;
}

static clGetPlatformIDsForInstanceKHR_t clGetPlatformIDsForInstanceKHR;
cl_int CL_API_CALL
clGetPlatformIDsForInstanceKHR(
    cl_instance_khr instance,
    cl_uint num_entries,
    cl_platform_id* platforms,
    cl_uint* num_platforms)
{
    cl_uint i;

    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(instance, CL_INVALID_INSTANCE_KHR);
    // should be impossible since create would have refused to
    // create an empty instance
    if (!instance->num_platforms)
    {
        return CL_INVALID_INSTANCE_KHR;
    }
    if (!num_entries && platforms)
    {
        return CL_INVALID_VALUE;
    }
    if (!platforms && !num_platforms)
    {
        return CL_INVALID_VALUE;
    }
    if (num_platforms)
    {
        *num_platforms = instance->num_platforms;
    }
    if (platforms)
    {
        for (i = 0; i < num_entries; ++i)
        {
            platforms[i] = NULL;
        }
        if (instance->num_platforms < num_entries)
        {
            num_entries = instance->num_platforms;
        }
        for (i = 0; i < num_entries; ++i)
        {
            platforms[i] = instance->platforms[i];
        }
    }
    return CL_SUCCESS;
}
#endif // defined(CL_ENABLE_LOADER_MANAGED_DISPATCH)

static void* khrIcdGetExtensionFunctionAddress(const char* function_name)
{
// Most extensions, including multi-vendor KHR and EXT extensions,
// do not need to be ICD-aware and do not require any ICD loader
// modifications.  The KHR and EXT extensions below were added for
// backwards compatibility only.
#define KHR_ICD_CHECK_EXTENSION_FUNCTION(name)                                 \
    do                                                                         \
    {                                                                          \
        if (!strcmp(function_name, #name))                                     \
        {                                                                      \
            return (void*)(size_t)&name;                                       \
        }                                                                      \
    } while (0)

    // Functions supporting the creation of OpenCL Memory Objects
    // from OpenGL Objects (cl_apple_gl_sharing, cl_khr_gl_sharing)
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromGLBuffer);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromGLTexture);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromGLTexture2D);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromGLTexture3D);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromGLRenderbuffer);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clGetGLObjectInfo);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clGetGLTextureInfo);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueAcquireGLObjects);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueReleaseGLObjects);

    // cl_khr_gl_sharing
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clGetGLContextInfoKHR);

    // cl_khr_gl_event
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateEventFromGLsyncKHR);

#if defined(_WIN32)
    // cl_khr_d3d10_sharing
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clGetDeviceIDsFromD3D10KHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromD3D10BufferKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromD3D10Texture2DKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromD3D10Texture3DKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueAcquireD3D10ObjectsKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueReleaseD3D10ObjectsKHR);
    // cl_khr_d3d11_sharing
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clGetDeviceIDsFromD3D11KHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromD3D11BufferKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromD3D11Texture2DKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromD3D11Texture3DKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueAcquireD3D11ObjectsKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueReleaseD3D11ObjectsKHR);
    // cl_khr_dx9_media_sharing
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clGetDeviceIDsFromDX9MediaAdapterKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromDX9MediaSurfaceKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueAcquireDX9MediaSurfacesKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueReleaseDX9MediaSurfacesKHR);
#endif

    // cl_ext_device_fission
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateSubDevicesEXT);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clRetainDeviceEXT);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clReleaseDeviceEXT);

    // cl_khr_egl_image
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateFromEGLImageKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueAcquireEGLObjectsKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clEnqueueReleaseEGLObjectsKHR);

    // cl_khr_egl_event
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateEventFromEGLSyncKHR);

    // cl_khr_sub_groups
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clGetKernelSubGroupInfoKHR);

    // cl_icdl
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clGetICDLoaderInfoOCLICD);

#if defined(CL_ENABLE_LOADER_MANAGED_DISPATCH)
    // cl_khr_instances
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clCreateInstanceKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clDestroyInstanceKHR);
    KHR_ICD_CHECK_EXTENSION_FUNCTION(clGetPlatformIDsForInstanceKHR);
#endif

#undef KHR_ICD_CHECK_EXTENSION_FUNCTION

    return NULL;
}

#ifdef __cplusplus
extern "C" {
#endif

static inline cl_int clGetPlatformIDs_body(
    cl_uint num_entries,
    cl_platform_id* platforms,
    cl_uint* num_platforms)
{
    KHRicdVendor* vendor = NULL;
    cl_uint i;

    if (!num_entries && platforms)
    {
        return CL_INVALID_VALUE;
    }
    if (!platforms && !num_platforms)
    {
        return CL_INVALID_VALUE;
    }
    // set num_platforms to 0 and set all platform pointers to NULL
    if (num_platforms)
    {
        *num_platforms = 0;
    }
    for (i = 0; i < num_entries && platforms; ++i)
    {
        platforms[i] = NULL;
    }
    // return error if we have no platforms
    if (!khrIcdVendors)
    {
        return CL_PLATFORM_NOT_FOUND_KHR;
    }
    // otherwise enumerate all platforms
    for (vendor = khrIcdVendors; vendor; vendor = vendor->next)
    {
        if (num_entries && platforms)
        {
            *(platforms++) = vendor->platform;
            --num_entries;
        }
        if (num_platforms)
        {
            ++(*num_platforms);
        }
    }
    return CL_SUCCESS;
}

cl_int CL_API_CALL clGetPlatformIDs_disp(
    cl_uint num_entries,
    cl_platform_id* platforms,
    cl_uint* num_platforms)
{
    return clGetPlatformIDs_body(
        num_entries,
        platforms,
        num_platforms);
}

CL_API_ENTRY cl_int CL_API_CALL clGetPlatformIDs(
    cl_uint num_entries,
    cl_platform_id* platforms,
    cl_uint* num_platforms)
{
    // initialize the platforms (in case they have not been already)
    khrIcdInitialize();

#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetPlatformIDs(
            num_entries,
            platforms,
            num_platforms);
#endif // defined(CL_ENABLE_LAYERS)
    return clGetPlatformIDs_body(
        num_entries,
        platforms,
        num_platforms);
}

static inline void* clGetExtensionFunctionAddress_body(
    const char* function_name)
{
    void* function_address = NULL;
    size_t function_name_length = 0;
    KHRicdVendor* vendor = NULL;

    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(function_name, NULL);

    // check if this is an ICD-aware extension
    function_address = khrIcdGetExtensionFunctionAddress(function_name);
    if (function_address)
    {
        return function_address;
    }

    // fall back to vendor extension detection
    function_name_length = strlen(function_name);
    for (vendor = khrIcdVendors; vendor; vendor = vendor->next)
    {
        size_t vendor_suffix_length = strlen(vendor->suffix);
        if (vendor_suffix_length <= function_name_length &&
            vendor_suffix_length > 0)
        {
            const char* function_suffix =
                function_name + function_name_length - vendor_suffix_length;
            if (!strcmp(function_suffix, vendor->suffix))
            {
                return vendor->clGetExtensionFunctionAddress(function_name);
            }
        }
    }

    return NULL;
}

void* CL_API_CALL clGetExtensionFunctionAddress_disp(
    const char* function_name)
{
    return clGetExtensionFunctionAddress_body(
        function_name);
}

CL_API_ENTRY void* CL_API_CALL clGetExtensionFunctionAddress(
    const char* function_name)
{
    // make sure the ICD is initialized
    khrIcdInitialize();

#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetExtensionFunctionAddress(
            function_name);
#endif // defined(CL_ENABLE_LAYERS)
    return clGetExtensionFunctionAddress_body(
        function_name);
}

static inline void* clGetExtensionFunctionAddressForPlatform_body(
    cl_platform_id platform,
    const char* function_name)
{
    void* function_address = NULL;

    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(function_name, NULL);

    // check if this is an ICD-aware extension
    function_address = khrIcdGetExtensionFunctionAddress(function_name);
    if (function_address)
    {
        return function_address;
    }

    // This is not an ICD-aware extension, so call into the implementation
    // to get the extension function address.

    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, NULL);
    return KHR_ICD2_DISPATCH(platform)->clGetExtensionFunctionAddressForPlatform(
        platform,
        function_name);
}

void* CL_API_CALL clGetExtensionFunctionAddressForPlatform_disp(
    cl_platform_id platform,
    const char* function_name)
{
    return clGetExtensionFunctionAddressForPlatform_body(
        platform,
        function_name);
}

CL_API_ENTRY void* CL_API_CALL clGetExtensionFunctionAddressForPlatform(
    cl_platform_id platform,
    const char* function_name)
{
    // make sure the ICD is initialized
    khrIcdInitialize();
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetExtensionFunctionAddressForPlatform(
            platform,
            function_name);
#endif // defined(CL_ENABLE_LAYERS)
    return clGetExtensionFunctionAddressForPlatform_body(
        platform,
        function_name);
}

#ifdef __cplusplus
}
#endif
