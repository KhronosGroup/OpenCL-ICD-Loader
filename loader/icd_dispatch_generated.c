/*
 * Copyright (c) 2012-2023 The Khronos Group Inc.
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

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// Core APIs:
#if defined(CL_ENABLE_LAYERS)
extern cl_int CL_API_CALL clGetPlatformIDs_disp(
    cl_uint num_entries,
    cl_platform_id* platforms,
    cl_uint* num_platforms) CL_API_SUFFIX__VERSION_1_0;
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clGetPlatformInfo(
    cl_platform_id platform,
    cl_platform_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetPlatformInfo(
            platform,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    return platform->dispatch->clGetPlatformInfo(
        platform,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetPlatformInfo_disp(
    cl_platform_id platform,
    cl_platform_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    return platform->dispatch->clGetPlatformInfo(
        platform,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDs(
    cl_platform_id platform,
    cl_device_type device_type,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetDeviceIDs(
            platform,
            device_type,
            num_entries,
            devices,
            num_devices);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    return platform->dispatch->clGetDeviceIDs(
        platform,
        device_type,
        num_entries,
        devices,
        num_devices);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetDeviceIDs_disp(
    cl_platform_id platform,
    cl_device_type device_type,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    return platform->dispatch->clGetDeviceIDs(
        platform,
        device_type,
        num_entries,
        devices,
        num_devices);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetDeviceInfo(
    cl_device_id device,
    cl_device_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetDeviceInfo(
            device,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clGetDeviceInfo(
        device,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetDeviceInfo_disp(
    cl_device_id device,
    cl_device_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clGetDeviceInfo(
        device,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_context CL_API_CALL clCreateContext(
    const cl_context_properties* properties,
    cl_uint num_devices,
    const cl_device_id* devices,
    void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data),
    void* user_data,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateContext(
            properties,
            num_devices,
            devices,
            pfn_notify,
            user_data,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    if (num_devices == 0 || devices == NULL) {
        KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(NULL, CL_INVALID_VALUE);
    }
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(devices[0], CL_INVALID_DEVICE);
    return devices[0]->dispatch->clCreateContext(
        properties,
        num_devices,
        devices,
        pfn_notify,
        user_data,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_context CL_API_CALL clCreateContext_disp(
    const cl_context_properties* properties,
    cl_uint num_devices,
    const cl_device_id* devices,
    void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data),
    void* user_data,
    cl_int* errcode_ret)
{
    if (num_devices == 0 || devices == NULL) {
        KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(NULL, CL_INVALID_VALUE);
    }
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(devices[0], CL_INVALID_DEVICE);
    return devices[0]->dispatch->clCreateContext(
        properties,
        num_devices,
        devices,
        pfn_notify,
        user_data,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_context CL_API_CALL clCreateContextFromType(
    const cl_context_properties* properties,
    cl_device_type device_type,
    void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data),
    void* user_data,
    cl_int* errcode_ret)
{
    khrIcdInitialize();
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateContextFromType(
            properties,
            device_type,
            pfn_notify,
            user_data,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    cl_platform_id platform = NULL;
    khrIcdContextPropertiesGetPlatform(properties, &platform);
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(platform, CL_INVALID_PLATFORM);
    return platform->dispatch->clCreateContextFromType(
        properties,
        device_type,
        pfn_notify,
        user_data,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_context CL_API_CALL clCreateContextFromType_disp(
    const cl_context_properties* properties,
    cl_device_type device_type,
    void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data),
    void* user_data,
    cl_int* errcode_ret)
{
    khrIcdInitialize();
    cl_platform_id platform = NULL;
    khrIcdContextPropertiesGetPlatform(properties, &platform);
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(platform, CL_INVALID_PLATFORM);
    return platform->dispatch->clCreateContextFromType(
        properties,
        device_type,
        pfn_notify,
        user_data,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clRetainContext(
    cl_context context)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clRetainContext(
            context);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clRetainContext(
        context);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clRetainContext_disp(
    cl_context context)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clRetainContext(
        context);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clReleaseContext(
    cl_context context)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clReleaseContext(
            context);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clReleaseContext(
        context);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clReleaseContext_disp(
    cl_context context)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clReleaseContext(
        context);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetContextInfo(
    cl_context context,
    cl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetContextInfo(
            context,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clGetContextInfo(
        context,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetContextInfo_disp(
    cl_context context,
    cl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clGetContextInfo(
        context,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clRetainCommandQueue(
    cl_command_queue command_queue)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clRetainCommandQueue(
            command_queue);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clRetainCommandQueue(
        command_queue);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clRetainCommandQueue_disp(
    cl_command_queue command_queue)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clRetainCommandQueue(
        command_queue);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clReleaseCommandQueue(
    cl_command_queue command_queue)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clReleaseCommandQueue(
            command_queue);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clReleaseCommandQueue(
        command_queue);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clReleaseCommandQueue_disp(
    cl_command_queue command_queue)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clReleaseCommandQueue(
        command_queue);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetCommandQueueInfo(
    cl_command_queue command_queue,
    cl_command_queue_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetCommandQueueInfo(
            command_queue,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clGetCommandQueueInfo(
        command_queue,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetCommandQueueInfo_disp(
    cl_command_queue command_queue,
    cl_command_queue_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clGetCommandQueueInfo(
        command_queue,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_mem CL_API_CALL clCreateBuffer(
    cl_context context,
    cl_mem_flags flags,
    size_t size,
    void* host_ptr,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateBuffer(
            context,
            flags,
            size,
            host_ptr,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateBuffer(
        context,
        flags,
        size,
        host_ptr,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateBuffer_disp(
    cl_context context,
    cl_mem_flags flags,
    size_t size,
    void* host_ptr,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateBuffer(
        context,
        flags,
        size,
        host_ptr,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clRetainMemObject(
    cl_mem memobj)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clRetainMemObject(
            memobj);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    return memobj->dispatch->clRetainMemObject(
        memobj);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clRetainMemObject_disp(
    cl_mem memobj)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    return memobj->dispatch->clRetainMemObject(
        memobj);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clReleaseMemObject(
    cl_mem memobj)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clReleaseMemObject(
            memobj);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    return memobj->dispatch->clReleaseMemObject(
        memobj);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clReleaseMemObject_disp(
    cl_mem memobj)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    return memobj->dispatch->clReleaseMemObject(
        memobj);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetSupportedImageFormats(
    cl_context context,
    cl_mem_flags flags,
    cl_mem_object_type image_type,
    cl_uint num_entries,
    cl_image_format* image_formats,
    cl_uint* num_image_formats)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetSupportedImageFormats(
            context,
            flags,
            image_type,
            num_entries,
            image_formats,
            num_image_formats);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clGetSupportedImageFormats(
        context,
        flags,
        image_type,
        num_entries,
        image_formats,
        num_image_formats);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetSupportedImageFormats_disp(
    cl_context context,
    cl_mem_flags flags,
    cl_mem_object_type image_type,
    cl_uint num_entries,
    cl_image_format* image_formats,
    cl_uint* num_image_formats)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clGetSupportedImageFormats(
        context,
        flags,
        image_type,
        num_entries,
        image_formats,
        num_image_formats);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetMemObjectInfo(
    cl_mem memobj,
    cl_mem_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetMemObjectInfo(
            memobj,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    return memobj->dispatch->clGetMemObjectInfo(
        memobj,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetMemObjectInfo_disp(
    cl_mem memobj,
    cl_mem_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    return memobj->dispatch->clGetMemObjectInfo(
        memobj,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetImageInfo(
    cl_mem image,
    cl_image_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetImageInfo(
            image,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(image, CL_INVALID_MEM_OBJECT);
    return image->dispatch->clGetImageInfo(
        image,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetImageInfo_disp(
    cl_mem image,
    cl_image_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(image, CL_INVALID_MEM_OBJECT);
    return image->dispatch->clGetImageInfo(
        image,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clRetainSampler(
    cl_sampler sampler)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clRetainSampler(
            sampler);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(sampler, CL_INVALID_SAMPLER);
    return sampler->dispatch->clRetainSampler(
        sampler);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clRetainSampler_disp(
    cl_sampler sampler)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(sampler, CL_INVALID_SAMPLER);
    return sampler->dispatch->clRetainSampler(
        sampler);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clReleaseSampler(
    cl_sampler sampler)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clReleaseSampler(
            sampler);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(sampler, CL_INVALID_SAMPLER);
    return sampler->dispatch->clReleaseSampler(
        sampler);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clReleaseSampler_disp(
    cl_sampler sampler)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(sampler, CL_INVALID_SAMPLER);
    return sampler->dispatch->clReleaseSampler(
        sampler);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetSamplerInfo(
    cl_sampler sampler,
    cl_sampler_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetSamplerInfo(
            sampler,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(sampler, CL_INVALID_SAMPLER);
    return sampler->dispatch->clGetSamplerInfo(
        sampler,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetSamplerInfo_disp(
    cl_sampler sampler,
    cl_sampler_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(sampler, CL_INVALID_SAMPLER);
    return sampler->dispatch->clGetSamplerInfo(
        sampler,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_program CL_API_CALL clCreateProgramWithSource(
    cl_context context,
    cl_uint count,
    const char** strings,
    const size_t* lengths,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateProgramWithSource(
            context,
            count,
            strings,
            lengths,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateProgramWithSource(
        context,
        count,
        strings,
        lengths,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_program CL_API_CALL clCreateProgramWithSource_disp(
    cl_context context,
    cl_uint count,
    const char** strings,
    const size_t* lengths,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateProgramWithSource(
        context,
        count,
        strings,
        lengths,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_program CL_API_CALL clCreateProgramWithBinary(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const size_t* lengths,
    const unsigned char** binaries,
    cl_int* binary_status,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateProgramWithBinary(
            context,
            num_devices,
            device_list,
            lengths,
            binaries,
            binary_status,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateProgramWithBinary(
        context,
        num_devices,
        device_list,
        lengths,
        binaries,
        binary_status,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_program CL_API_CALL clCreateProgramWithBinary_disp(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const size_t* lengths,
    const unsigned char** binaries,
    cl_int* binary_status,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateProgramWithBinary(
        context,
        num_devices,
        device_list,
        lengths,
        binaries,
        binary_status,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clRetainProgram(
    cl_program program)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clRetainProgram(
            program);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clRetainProgram(
        program);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clRetainProgram_disp(
    cl_program program)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clRetainProgram(
        program);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clReleaseProgram(
    cl_program program)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clReleaseProgram(
            program);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clReleaseProgram(
        program);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clReleaseProgram_disp(
    cl_program program)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clReleaseProgram(
        program);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clBuildProgram(
    cl_program program,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clBuildProgram(
            program,
            num_devices,
            device_list,
            options,
            pfn_notify,
            user_data);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clBuildProgram(
        program,
        num_devices,
        device_list,
        options,
        pfn_notify,
        user_data);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clBuildProgram_disp(
    cl_program program,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clBuildProgram(
        program,
        num_devices,
        device_list,
        options,
        pfn_notify,
        user_data);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetProgramInfo(
    cl_program program,
    cl_program_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetProgramInfo(
            program,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clGetProgramInfo(
        program,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetProgramInfo_disp(
    cl_program program,
    cl_program_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clGetProgramInfo(
        program,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetProgramBuildInfo(
    cl_program program,
    cl_device_id device,
    cl_program_build_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetProgramBuildInfo(
            program,
            device,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clGetProgramBuildInfo(
        program,
        device,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetProgramBuildInfo_disp(
    cl_program program,
    cl_device_id device,
    cl_program_build_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clGetProgramBuildInfo(
        program,
        device,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_kernel CL_API_CALL clCreateKernel(
    cl_program program,
    const char* kernel_name,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateKernel(
            program,
            kernel_name,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(program, CL_INVALID_PROGRAM);
    return program->dispatch->clCreateKernel(
        program,
        kernel_name,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_kernel CL_API_CALL clCreateKernel_disp(
    cl_program program,
    const char* kernel_name,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(program, CL_INVALID_PROGRAM);
    return program->dispatch->clCreateKernel(
        program,
        kernel_name,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clCreateKernelsInProgram(
    cl_program program,
    cl_uint num_kernels,
    cl_kernel* kernels,
    cl_uint* num_kernels_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateKernelsInProgram(
            program,
            num_kernels,
            kernels,
            num_kernels_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clCreateKernelsInProgram(
        program,
        num_kernels,
        kernels,
        num_kernels_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clCreateKernelsInProgram_disp(
    cl_program program,
    cl_uint num_kernels,
    cl_kernel* kernels,
    cl_uint* num_kernels_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clCreateKernelsInProgram(
        program,
        num_kernels,
        kernels,
        num_kernels_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clRetainKernel(
    cl_kernel kernel)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clRetainKernel(
            kernel);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clRetainKernel(
        kernel);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clRetainKernel_disp(
    cl_kernel kernel)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clRetainKernel(
        kernel);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clReleaseKernel(
    cl_kernel kernel)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clReleaseKernel(
            kernel);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clReleaseKernel(
        kernel);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clReleaseKernel_disp(
    cl_kernel kernel)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clReleaseKernel(
        kernel);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetKernelArg(
    cl_kernel kernel,
    cl_uint arg_index,
    size_t arg_size,
    const void* arg_value)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetKernelArg(
            kernel,
            arg_index,
            arg_size,
            arg_value);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clSetKernelArg(
        kernel,
        arg_index,
        arg_size,
        arg_value);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetKernelArg_disp(
    cl_kernel kernel,
    cl_uint arg_index,
    size_t arg_size,
    const void* arg_value)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clSetKernelArg(
        kernel,
        arg_index,
        arg_size,
        arg_value);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetKernelInfo(
    cl_kernel kernel,
    cl_kernel_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetKernelInfo(
            kernel,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clGetKernelInfo(
        kernel,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetKernelInfo_disp(
    cl_kernel kernel,
    cl_kernel_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clGetKernelInfo(
        kernel,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetKernelWorkGroupInfo(
    cl_kernel kernel,
    cl_device_id device,
    cl_kernel_work_group_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetKernelWorkGroupInfo(
            kernel,
            device,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clGetKernelWorkGroupInfo(
        kernel,
        device,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetKernelWorkGroupInfo_disp(
    cl_kernel kernel,
    cl_device_id device,
    cl_kernel_work_group_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clGetKernelWorkGroupInfo(
        kernel,
        device,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clWaitForEvents(
    cl_uint num_events,
    const cl_event* event_list)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clWaitForEvents(
            num_events,
            event_list);
#endif // defined(CL_ENABLE_LAYERS)
    if (num_events == 0 || event_list == NULL) {
        return CL_INVALID_VALUE;
    }
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event_list[0], CL_INVALID_EVENT);
    return event_list[0]->dispatch->clWaitForEvents(
        num_events,
        event_list);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clWaitForEvents_disp(
    cl_uint num_events,
    const cl_event* event_list)
{
    if (num_events == 0 || event_list == NULL) {
        return CL_INVALID_VALUE;
    }
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event_list[0], CL_INVALID_EVENT);
    return event_list[0]->dispatch->clWaitForEvents(
        num_events,
        event_list);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetEventInfo(
    cl_event event,
    cl_event_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetEventInfo(
            event,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clGetEventInfo(
        event,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetEventInfo_disp(
    cl_event event,
    cl_event_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clGetEventInfo(
        event,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clRetainEvent(
    cl_event event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clRetainEvent(
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clRetainEvent(
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clRetainEvent_disp(
    cl_event event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clRetainEvent(
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clReleaseEvent(
    cl_event event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clReleaseEvent(
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clReleaseEvent(
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clReleaseEvent_disp(
    cl_event event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clReleaseEvent(
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetEventProfilingInfo(
    cl_event event,
    cl_profiling_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetEventProfilingInfo(
            event,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clGetEventProfilingInfo(
        event,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetEventProfilingInfo_disp(
    cl_event event,
    cl_profiling_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clGetEventProfilingInfo(
        event,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clFlush(
    cl_command_queue command_queue)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clFlush(
            command_queue);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clFlush(
        command_queue);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clFlush_disp(
    cl_command_queue command_queue)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clFlush(
        command_queue);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clFinish(
    cl_command_queue command_queue)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clFinish(
            command_queue);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clFinish(
        command_queue);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clFinish_disp(
    cl_command_queue command_queue)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clFinish(
        command_queue);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueReadBuffer(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_read,
    size_t offset,
    size_t size,
    void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueReadBuffer(
            command_queue,
            buffer,
            blocking_read,
            offset,
            size,
            ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueReadBuffer(
        command_queue,
        buffer,
        blocking_read,
        offset,
        size,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueReadBuffer_disp(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_read,
    size_t offset,
    size_t size,
    void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueReadBuffer(
        command_queue,
        buffer,
        blocking_read,
        offset,
        size,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueWriteBuffer(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_write,
    size_t offset,
    size_t size,
    const void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueWriteBuffer(
            command_queue,
            buffer,
            blocking_write,
            offset,
            size,
            ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueWriteBuffer(
        command_queue,
        buffer,
        blocking_write,
        offset,
        size,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueWriteBuffer_disp(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_write,
    size_t offset,
    size_t size,
    const void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueWriteBuffer(
        command_queue,
        buffer,
        blocking_write,
        offset,
        size,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueCopyBuffer(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_buffer,
    size_t src_offset,
    size_t dst_offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueCopyBuffer(
            command_queue,
            src_buffer,
            dst_buffer,
            src_offset,
            dst_offset,
            size,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyBuffer(
        command_queue,
        src_buffer,
        dst_buffer,
        src_offset,
        dst_offset,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueCopyBuffer_disp(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_buffer,
    size_t src_offset,
    size_t dst_offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyBuffer(
        command_queue,
        src_buffer,
        dst_buffer,
        src_offset,
        dst_offset,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueReadImage(
    cl_command_queue command_queue,
    cl_mem image,
    cl_bool blocking_read,
    const size_t* origin,
    const size_t* region,
    size_t row_pitch,
    size_t slice_pitch,
    void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueReadImage(
            command_queue,
            image,
            blocking_read,
            origin,
            region,
            row_pitch,
            slice_pitch,
            ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueReadImage(
        command_queue,
        image,
        blocking_read,
        origin,
        region,
        row_pitch,
        slice_pitch,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueReadImage_disp(
    cl_command_queue command_queue,
    cl_mem image,
    cl_bool blocking_read,
    const size_t* origin,
    const size_t* region,
    size_t row_pitch,
    size_t slice_pitch,
    void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueReadImage(
        command_queue,
        image,
        blocking_read,
        origin,
        region,
        row_pitch,
        slice_pitch,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueWriteImage(
    cl_command_queue command_queue,
    cl_mem image,
    cl_bool blocking_write,
    const size_t* origin,
    const size_t* region,
    size_t input_row_pitch,
    size_t input_slice_pitch,
    const void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueWriteImage(
            command_queue,
            image,
            blocking_write,
            origin,
            region,
            input_row_pitch,
            input_slice_pitch,
            ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueWriteImage(
        command_queue,
        image,
        blocking_write,
        origin,
        region,
        input_row_pitch,
        input_slice_pitch,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueWriteImage_disp(
    cl_command_queue command_queue,
    cl_mem image,
    cl_bool blocking_write,
    const size_t* origin,
    const size_t* region,
    size_t input_row_pitch,
    size_t input_slice_pitch,
    const void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueWriteImage(
        command_queue,
        image,
        blocking_write,
        origin,
        region,
        input_row_pitch,
        input_slice_pitch,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueCopyImage(
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_image,
    const size_t* src_origin,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueCopyImage(
            command_queue,
            src_image,
            dst_image,
            src_origin,
            dst_origin,
            region,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyImage(
        command_queue,
        src_image,
        dst_image,
        src_origin,
        dst_origin,
        region,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueCopyImage_disp(
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_image,
    const size_t* src_origin,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyImage(
        command_queue,
        src_image,
        dst_image,
        src_origin,
        dst_origin,
        region,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueCopyImageToBuffer(
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_buffer,
    const size_t* src_origin,
    const size_t* region,
    size_t dst_offset,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueCopyImageToBuffer(
            command_queue,
            src_image,
            dst_buffer,
            src_origin,
            region,
            dst_offset,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyImageToBuffer(
        command_queue,
        src_image,
        dst_buffer,
        src_origin,
        region,
        dst_offset,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueCopyImageToBuffer_disp(
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_buffer,
    const size_t* src_origin,
    const size_t* region,
    size_t dst_offset,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyImageToBuffer(
        command_queue,
        src_image,
        dst_buffer,
        src_origin,
        region,
        dst_offset,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueCopyBufferToImage(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_image,
    size_t src_offset,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueCopyBufferToImage(
            command_queue,
            src_buffer,
            dst_image,
            src_offset,
            dst_origin,
            region,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyBufferToImage(
        command_queue,
        src_buffer,
        dst_image,
        src_offset,
        dst_origin,
        region,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueCopyBufferToImage_disp(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_image,
    size_t src_offset,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyBufferToImage(
        command_queue,
        src_buffer,
        dst_image,
        src_offset,
        dst_origin,
        region,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY void* CL_API_CALL clEnqueueMapBuffer(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_map,
    cl_map_flags map_flags,
    size_t offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueMapBuffer(
            command_queue,
            buffer,
            blocking_map,
            map_flags,
            offset,
            size,
            num_events_in_wait_list,
            event_wait_list,
            event,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMapBuffer(
        command_queue,
        buffer,
        blocking_map,
        map_flags,
        offset,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static void* CL_API_CALL clEnqueueMapBuffer_disp(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_map,
    cl_map_flags map_flags,
    size_t offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMapBuffer(
        command_queue,
        buffer,
        blocking_map,
        map_flags,
        offset,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY void* CL_API_CALL clEnqueueMapImage(
    cl_command_queue command_queue,
    cl_mem image,
    cl_bool blocking_map,
    cl_map_flags map_flags,
    const size_t* origin,
    const size_t* region,
    size_t* image_row_pitch,
    size_t* image_slice_pitch,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueMapImage(
            command_queue,
            image,
            blocking_map,
            map_flags,
            origin,
            region,
            image_row_pitch,
            image_slice_pitch,
            num_events_in_wait_list,
            event_wait_list,
            event,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMapImage(
        command_queue,
        image,
        blocking_map,
        map_flags,
        origin,
        region,
        image_row_pitch,
        image_slice_pitch,
        num_events_in_wait_list,
        event_wait_list,
        event,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static void* CL_API_CALL clEnqueueMapImage_disp(
    cl_command_queue command_queue,
    cl_mem image,
    cl_bool blocking_map,
    cl_map_flags map_flags,
    const size_t* origin,
    const size_t* region,
    size_t* image_row_pitch,
    size_t* image_slice_pitch,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMapImage(
        command_queue,
        image,
        blocking_map,
        map_flags,
        origin,
        region,
        image_row_pitch,
        image_slice_pitch,
        num_events_in_wait_list,
        event_wait_list,
        event,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueUnmapMemObject(
    cl_command_queue command_queue,
    cl_mem memobj,
    void* mapped_ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueUnmapMemObject(
            command_queue,
            memobj,
            mapped_ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueUnmapMemObject(
        command_queue,
        memobj,
        mapped_ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueUnmapMemObject_disp(
    cl_command_queue command_queue,
    cl_mem memobj,
    void* mapped_ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueUnmapMemObject(
        command_queue,
        memobj,
        mapped_ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueNDRangeKernel(
    cl_command_queue command_queue,
    cl_kernel kernel,
    cl_uint work_dim,
    const size_t* global_work_offset,
    const size_t* global_work_size,
    const size_t* local_work_size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueNDRangeKernel(
            command_queue,
            kernel,
            work_dim,
            global_work_offset,
            global_work_size,
            local_work_size,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueNDRangeKernel(
        command_queue,
        kernel,
        work_dim,
        global_work_offset,
        global_work_size,
        local_work_size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueNDRangeKernel_disp(
    cl_command_queue command_queue,
    cl_kernel kernel,
    cl_uint work_dim,
    const size_t* global_work_offset,
    const size_t* global_work_size,
    const size_t* local_work_size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueNDRangeKernel(
        command_queue,
        kernel,
        work_dim,
        global_work_offset,
        global_work_size,
        local_work_size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueNativeKernel(
    cl_command_queue command_queue,
    void (CL_CALLBACK* user_func)(void*),
    void* args,
    size_t cb_args,
    cl_uint num_mem_objects,
    const cl_mem* mem_list,
    const void** args_mem_loc,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueNativeKernel(
            command_queue,
            user_func,
            args,
            cb_args,
            num_mem_objects,
            mem_list,
            args_mem_loc,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueNativeKernel(
        command_queue,
        user_func,
        args,
        cb_args,
        num_mem_objects,
        mem_list,
        args_mem_loc,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueNativeKernel_disp(
    cl_command_queue command_queue,
    void (CL_CALLBACK* user_func)(void*),
    void* args,
    size_t cb_args,
    cl_uint num_mem_objects,
    const cl_mem* mem_list,
    const void** args_mem_loc,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueNativeKernel(
        command_queue,
        user_func,
        args,
        cb_args,
        num_mem_objects,
        mem_list,
        args_mem_loc,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetCommandQueueProperty(
    cl_command_queue command_queue,
    cl_command_queue_properties properties,
    cl_bool enable,
    cl_command_queue_properties* old_properties)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetCommandQueueProperty(
            command_queue,
            properties,
            enable,
            old_properties);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clSetCommandQueueProperty(
        command_queue,
        properties,
        enable,
        old_properties);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetCommandQueueProperty_disp(
    cl_command_queue command_queue,
    cl_command_queue_properties properties,
    cl_bool enable,
    cl_command_queue_properties* old_properties)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clSetCommandQueueProperty(
        command_queue,
        properties,
        enable,
        old_properties);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_mem CL_API_CALL clCreateImage2D(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    size_t image_width,
    size_t image_height,
    size_t image_row_pitch,
    void* host_ptr,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateImage2D(
            context,
            flags,
            image_format,
            image_width,
            image_height,
            image_row_pitch,
            host_ptr,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateImage2D(
        context,
        flags,
        image_format,
        image_width,
        image_height,
        image_row_pitch,
        host_ptr,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateImage2D_disp(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    size_t image_width,
    size_t image_height,
    size_t image_row_pitch,
    void* host_ptr,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateImage2D(
        context,
        flags,
        image_format,
        image_width,
        image_height,
        image_row_pitch,
        host_ptr,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_mem CL_API_CALL clCreateImage3D(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    size_t image_width,
    size_t image_height,
    size_t image_depth,
    size_t image_row_pitch,
    size_t image_slice_pitch,
    void* host_ptr,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateImage3D(
            context,
            flags,
            image_format,
            image_width,
            image_height,
            image_depth,
            image_row_pitch,
            image_slice_pitch,
            host_ptr,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateImage3D(
        context,
        flags,
        image_format,
        image_width,
        image_height,
        image_depth,
        image_row_pitch,
        image_slice_pitch,
        host_ptr,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateImage3D_disp(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    size_t image_width,
    size_t image_height,
    size_t image_depth,
    size_t image_row_pitch,
    size_t image_slice_pitch,
    void* host_ptr,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateImage3D(
        context,
        flags,
        image_format,
        image_width,
        image_height,
        image_depth,
        image_row_pitch,
        image_slice_pitch,
        host_ptr,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueMarker(
    cl_command_queue command_queue,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueMarker(
            command_queue,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMarker(
        command_queue,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueMarker_disp(
    cl_command_queue command_queue,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMarker(
        command_queue,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueWaitForEvents(
    cl_command_queue command_queue,
    cl_uint num_events,
    const cl_event* event_list)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueWaitForEvents(
            command_queue,
            num_events,
            event_list);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueWaitForEvents(
        command_queue,
        num_events,
        event_list);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueWaitForEvents_disp(
    cl_command_queue command_queue,
    cl_uint num_events,
    const cl_event* event_list)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueWaitForEvents(
        command_queue,
        num_events,
        event_list);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueBarrier(
    cl_command_queue command_queue)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueBarrier(
            command_queue);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueBarrier(
        command_queue);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueBarrier_disp(
    cl_command_queue command_queue)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueBarrier(
        command_queue);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clUnloadCompiler(
    void )
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clUnloadCompiler(
            );
#endif // defined(CL_ENABLE_LAYERS)
    // Nothing!
    return CL_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clUnloadCompiler_disp(
    void )
{
    // Nothing!
    return CL_SUCCESS;
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
extern void* CL_API_CALL clGetExtensionFunctionAddress_disp(
    const char* func_name) CL_API_SUFFIX__VERSION_1_1_DEPRECATED;
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_command_queue CL_API_CALL clCreateCommandQueue(
    cl_context context,
    cl_device_id device,
    cl_command_queue_properties properties,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateCommandQueue(
            context,
            device,
            properties,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateCommandQueue(
        context,
        device,
        properties,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_command_queue CL_API_CALL clCreateCommandQueue_disp(
    cl_context context,
    cl_device_id device,
    cl_command_queue_properties properties,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateCommandQueue(
        context,
        device,
        properties,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_sampler CL_API_CALL clCreateSampler(
    cl_context context,
    cl_bool normalized_coords,
    cl_addressing_mode addressing_mode,
    cl_filter_mode filter_mode,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateSampler(
            context,
            normalized_coords,
            addressing_mode,
            filter_mode,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateSampler(
        context,
        normalized_coords,
        addressing_mode,
        filter_mode,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_sampler CL_API_CALL clCreateSampler_disp(
    cl_context context,
    cl_bool normalized_coords,
    cl_addressing_mode addressing_mode,
    cl_filter_mode filter_mode,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateSampler(
        context,
        normalized_coords,
        addressing_mode,
        filter_mode,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueTask(
    cl_command_queue command_queue,
    cl_kernel kernel,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueTask(
            command_queue,
            kernel,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueTask(
        command_queue,
        kernel,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueTask_disp(
    cl_command_queue command_queue,
    cl_kernel kernel,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueTask(
        command_queue,
        kernel,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_mem CL_API_CALL clCreateSubBuffer(
    cl_mem buffer,
    cl_mem_flags flags,
    cl_buffer_create_type buffer_create_type,
    const void* buffer_create_info,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateSubBuffer(
            buffer,
            flags,
            buffer_create_type,
            buffer_create_info,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(buffer, CL_INVALID_MEM_OBJECT);
    return buffer->dispatch->clCreateSubBuffer(
        buffer,
        flags,
        buffer_create_type,
        buffer_create_info,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateSubBuffer_disp(
    cl_mem buffer,
    cl_mem_flags flags,
    cl_buffer_create_type buffer_create_type,
    const void* buffer_create_info,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(buffer, CL_INVALID_MEM_OBJECT);
    return buffer->dispatch->clCreateSubBuffer(
        buffer,
        flags,
        buffer_create_type,
        buffer_create_info,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetMemObjectDestructorCallback(
    cl_mem memobj,
    void (CL_CALLBACK* pfn_notify)(cl_mem memobj, void* user_data),
    void* user_data)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetMemObjectDestructorCallback(
            memobj,
            pfn_notify,
            user_data);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    return memobj->dispatch->clSetMemObjectDestructorCallback(
        memobj,
        pfn_notify,
        user_data);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetMemObjectDestructorCallback_disp(
    cl_mem memobj,
    void (CL_CALLBACK* pfn_notify)(cl_mem memobj, void* user_data),
    void* user_data)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    return memobj->dispatch->clSetMemObjectDestructorCallback(
        memobj,
        pfn_notify,
        user_data);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_event CL_API_CALL clCreateUserEvent(
    cl_context context,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateUserEvent(
            context,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateUserEvent(
        context,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_event CL_API_CALL clCreateUserEvent_disp(
    cl_context context,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateUserEvent(
        context,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetUserEventStatus(
    cl_event event,
    cl_int execution_status)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetUserEventStatus(
            event,
            execution_status);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clSetUserEventStatus(
        event,
        execution_status);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetUserEventStatus_disp(
    cl_event event,
    cl_int execution_status)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clSetUserEventStatus(
        event,
        execution_status);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetEventCallback(
    cl_event event,
    cl_int command_exec_callback_type,
    void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data),
    void* user_data)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetEventCallback(
            event,
            command_exec_callback_type,
            pfn_notify,
            user_data);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clSetEventCallback(
        event,
        command_exec_callback_type,
        pfn_notify,
        user_data);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetEventCallback_disp(
    cl_event event,
    cl_int command_exec_callback_type,
    void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data),
    void* user_data)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(event, CL_INVALID_EVENT);
    return event->dispatch->clSetEventCallback(
        event,
        command_exec_callback_type,
        pfn_notify,
        user_data);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueReadBufferRect(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_read,
    const size_t* buffer_origin,
    const size_t* host_origin,
    const size_t* region,
    size_t buffer_row_pitch,
    size_t buffer_slice_pitch,
    size_t host_row_pitch,
    size_t host_slice_pitch,
    void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueReadBufferRect(
            command_queue,
            buffer,
            blocking_read,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueReadBufferRect(
        command_queue,
        buffer,
        blocking_read,
        buffer_origin,
        host_origin,
        region,
        buffer_row_pitch,
        buffer_slice_pitch,
        host_row_pitch,
        host_slice_pitch,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueReadBufferRect_disp(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_read,
    const size_t* buffer_origin,
    const size_t* host_origin,
    const size_t* region,
    size_t buffer_row_pitch,
    size_t buffer_slice_pitch,
    size_t host_row_pitch,
    size_t host_slice_pitch,
    void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueReadBufferRect(
        command_queue,
        buffer,
        blocking_read,
        buffer_origin,
        host_origin,
        region,
        buffer_row_pitch,
        buffer_slice_pitch,
        host_row_pitch,
        host_slice_pitch,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueWriteBufferRect(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_write,
    const size_t* buffer_origin,
    const size_t* host_origin,
    const size_t* region,
    size_t buffer_row_pitch,
    size_t buffer_slice_pitch,
    size_t host_row_pitch,
    size_t host_slice_pitch,
    const void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueWriteBufferRect(
            command_queue,
            buffer,
            blocking_write,
            buffer_origin,
            host_origin,
            region,
            buffer_row_pitch,
            buffer_slice_pitch,
            host_row_pitch,
            host_slice_pitch,
            ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueWriteBufferRect(
        command_queue,
        buffer,
        blocking_write,
        buffer_origin,
        host_origin,
        region,
        buffer_row_pitch,
        buffer_slice_pitch,
        host_row_pitch,
        host_slice_pitch,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueWriteBufferRect_disp(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_write,
    const size_t* buffer_origin,
    const size_t* host_origin,
    const size_t* region,
    size_t buffer_row_pitch,
    size_t buffer_slice_pitch,
    size_t host_row_pitch,
    size_t host_slice_pitch,
    const void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueWriteBufferRect(
        command_queue,
        buffer,
        blocking_write,
        buffer_origin,
        host_origin,
        region,
        buffer_row_pitch,
        buffer_slice_pitch,
        host_row_pitch,
        host_slice_pitch,
        ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueCopyBufferRect(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_buffer,
    const size_t* src_origin,
    const size_t* dst_origin,
    const size_t* region,
    size_t src_row_pitch,
    size_t src_slice_pitch,
    size_t dst_row_pitch,
    size_t dst_slice_pitch,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueCopyBufferRect(
            command_queue,
            src_buffer,
            dst_buffer,
            src_origin,
            dst_origin,
            region,
            src_row_pitch,
            src_slice_pitch,
            dst_row_pitch,
            dst_slice_pitch,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyBufferRect(
        command_queue,
        src_buffer,
        dst_buffer,
        src_origin,
        dst_origin,
        region,
        src_row_pitch,
        src_slice_pitch,
        dst_row_pitch,
        dst_slice_pitch,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueCopyBufferRect_disp(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_buffer,
    const size_t* src_origin,
    const size_t* dst_origin,
    const size_t* region,
    size_t src_row_pitch,
    size_t src_slice_pitch,
    size_t dst_row_pitch,
    size_t dst_slice_pitch,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueCopyBufferRect(
        command_queue,
        src_buffer,
        dst_buffer,
        src_origin,
        dst_origin,
        region,
        src_row_pitch,
        src_slice_pitch,
        dst_row_pitch,
        dst_slice_pitch,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clCreateSubDevices(
    cl_device_id in_device,
    const cl_device_partition_property* properties,
    cl_uint num_devices,
    cl_device_id* out_devices,
    cl_uint* num_devices_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateSubDevices(
            in_device,
            properties,
            num_devices,
            out_devices,
            num_devices_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(in_device, CL_INVALID_DEVICE);
    return in_device->dispatch->clCreateSubDevices(
        in_device,
        properties,
        num_devices,
        out_devices,
        num_devices_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clCreateSubDevices_disp(
    cl_device_id in_device,
    const cl_device_partition_property* properties,
    cl_uint num_devices,
    cl_device_id* out_devices,
    cl_uint* num_devices_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(in_device, CL_INVALID_DEVICE);
    return in_device->dispatch->clCreateSubDevices(
        in_device,
        properties,
        num_devices,
        out_devices,
        num_devices_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clRetainDevice(
    cl_device_id device)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clRetainDevice(
            device);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clRetainDevice(
        device);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clRetainDevice_disp(
    cl_device_id device)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clRetainDevice(
        device);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clReleaseDevice(
    cl_device_id device)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clReleaseDevice(
            device);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clReleaseDevice(
        device);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clReleaseDevice_disp(
    cl_device_id device)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clReleaseDevice(
        device);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_mem CL_API_CALL clCreateImage(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    const cl_image_desc* image_desc,
    void* host_ptr,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateImage(
            context,
            flags,
            image_format,
            image_desc,
            host_ptr,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateImage(
        context,
        flags,
        image_format,
        image_desc,
        host_ptr,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateImage_disp(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    const cl_image_desc* image_desc,
    void* host_ptr,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateImage(
        context,
        flags,
        image_format,
        image_desc,
        host_ptr,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_program CL_API_CALL clCreateProgramWithBuiltInKernels(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* kernel_names,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateProgramWithBuiltInKernels(
            context,
            num_devices,
            device_list,
            kernel_names,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateProgramWithBuiltInKernels(
        context,
        num_devices,
        device_list,
        kernel_names,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_program CL_API_CALL clCreateProgramWithBuiltInKernels_disp(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* kernel_names,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateProgramWithBuiltInKernels(
        context,
        num_devices,
        device_list,
        kernel_names,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clCompileProgram(
    cl_program program,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    cl_uint num_input_headers,
    const cl_program* input_headers,
    const char** header_include_names,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCompileProgram(
            program,
            num_devices,
            device_list,
            options,
            num_input_headers,
            input_headers,
            header_include_names,
            pfn_notify,
            user_data);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clCompileProgram(
        program,
        num_devices,
        device_list,
        options,
        num_input_headers,
        input_headers,
        header_include_names,
        pfn_notify,
        user_data);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clCompileProgram_disp(
    cl_program program,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    cl_uint num_input_headers,
    const cl_program* input_headers,
    const char** header_include_names,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clCompileProgram(
        program,
        num_devices,
        device_list,
        options,
        num_input_headers,
        input_headers,
        header_include_names,
        pfn_notify,
        user_data);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_program CL_API_CALL clLinkProgram(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    cl_uint num_input_programs,
    const cl_program* input_programs,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clLinkProgram(
            context,
            num_devices,
            device_list,
            options,
            num_input_programs,
            input_programs,
            pfn_notify,
            user_data,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clLinkProgram(
        context,
        num_devices,
        device_list,
        options,
        num_input_programs,
        input_programs,
        pfn_notify,
        user_data,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_program CL_API_CALL clLinkProgram_disp(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    cl_uint num_input_programs,
    const cl_program* input_programs,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clLinkProgram(
        context,
        num_devices,
        device_list,
        options,
        num_input_programs,
        input_programs,
        pfn_notify,
        user_data,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clUnloadPlatformCompiler(
    cl_platform_id platform)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clUnloadPlatformCompiler(
            platform);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    return platform->dispatch->clUnloadPlatformCompiler(
        platform);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clUnloadPlatformCompiler_disp(
    cl_platform_id platform)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    return platform->dispatch->clUnloadPlatformCompiler(
        platform);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetKernelArgInfo(
    cl_kernel kernel,
    cl_uint arg_index,
    cl_kernel_arg_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetKernelArgInfo(
            kernel,
            arg_index,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clGetKernelArgInfo(
        kernel,
        arg_index,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetKernelArgInfo_disp(
    cl_kernel kernel,
    cl_uint arg_index,
    cl_kernel_arg_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clGetKernelArgInfo(
        kernel,
        arg_index,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueFillBuffer(
    cl_command_queue command_queue,
    cl_mem buffer,
    const void* pattern,
    size_t pattern_size,
    size_t offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueFillBuffer(
            command_queue,
            buffer,
            pattern,
            pattern_size,
            offset,
            size,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueFillBuffer(
        command_queue,
        buffer,
        pattern,
        pattern_size,
        offset,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueFillBuffer_disp(
    cl_command_queue command_queue,
    cl_mem buffer,
    const void* pattern,
    size_t pattern_size,
    size_t offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueFillBuffer(
        command_queue,
        buffer,
        pattern,
        pattern_size,
        offset,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueFillImage(
    cl_command_queue command_queue,
    cl_mem image,
    const void* fill_color,
    const size_t* origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueFillImage(
            command_queue,
            image,
            fill_color,
            origin,
            region,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueFillImage(
        command_queue,
        image,
        fill_color,
        origin,
        region,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueFillImage_disp(
    cl_command_queue command_queue,
    cl_mem image,
    const void* fill_color,
    const size_t* origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueFillImage(
        command_queue,
        image,
        fill_color,
        origin,
        region,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueMigrateMemObjects(
    cl_command_queue command_queue,
    cl_uint num_mem_objects,
    const cl_mem* mem_objects,
    cl_mem_migration_flags flags,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueMigrateMemObjects(
            command_queue,
            num_mem_objects,
            mem_objects,
            flags,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMigrateMemObjects(
        command_queue,
        num_mem_objects,
        mem_objects,
        flags,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueMigrateMemObjects_disp(
    cl_command_queue command_queue,
    cl_uint num_mem_objects,
    const cl_mem* mem_objects,
    cl_mem_migration_flags flags,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMigrateMemObjects(
        command_queue,
        num_mem_objects,
        mem_objects,
        flags,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueMarkerWithWaitList(
    cl_command_queue command_queue,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueMarkerWithWaitList(
            command_queue,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMarkerWithWaitList(
        command_queue,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueMarkerWithWaitList_disp(
    cl_command_queue command_queue,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueMarkerWithWaitList(
        command_queue,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueBarrierWithWaitList(
    cl_command_queue command_queue,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueBarrierWithWaitList(
            command_queue,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueBarrierWithWaitList(
        command_queue,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueBarrierWithWaitList_disp(
    cl_command_queue command_queue,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueBarrierWithWaitList(
        command_queue,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
extern void* CL_API_CALL clGetExtensionFunctionAddressForPlatform_disp(
    cl_platform_id platform,
    const char* func_name) CL_API_SUFFIX__VERSION_1_2;
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_command_queue CL_API_CALL clCreateCommandQueueWithProperties(
    cl_context context,
    cl_device_id device,
    const cl_queue_properties* properties,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateCommandQueueWithProperties(
            context,
            device,
            properties,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateCommandQueueWithProperties(
        context,
        device,
        properties,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_command_queue CL_API_CALL clCreateCommandQueueWithProperties_disp(
    cl_context context,
    cl_device_id device,
    const cl_queue_properties* properties,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateCommandQueueWithProperties(
        context,
        device,
        properties,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_mem CL_API_CALL clCreatePipe(
    cl_context context,
    cl_mem_flags flags,
    cl_uint pipe_packet_size,
    cl_uint pipe_max_packets,
    const cl_pipe_properties* properties,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreatePipe(
            context,
            flags,
            pipe_packet_size,
            pipe_max_packets,
            properties,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreatePipe(
        context,
        flags,
        pipe_packet_size,
        pipe_max_packets,
        properties,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreatePipe_disp(
    cl_context context,
    cl_mem_flags flags,
    cl_uint pipe_packet_size,
    cl_uint pipe_max_packets,
    const cl_pipe_properties* properties,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreatePipe(
        context,
        flags,
        pipe_packet_size,
        pipe_max_packets,
        properties,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetPipeInfo(
    cl_mem pipe,
    cl_pipe_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetPipeInfo(
            pipe,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(pipe, CL_INVALID_MEM_OBJECT);
    return pipe->dispatch->clGetPipeInfo(
        pipe,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetPipeInfo_disp(
    cl_mem pipe,
    cl_pipe_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(pipe, CL_INVALID_MEM_OBJECT);
    return pipe->dispatch->clGetPipeInfo(
        pipe,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY void* CL_API_CALL clSVMAlloc(
    cl_context context,
    cl_svm_mem_flags flags,
    size_t size,
    cl_uint alignment)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSVMAlloc(
            context,
            flags,
            size,
            alignment);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, NULL);
    return context->dispatch->clSVMAlloc(
        context,
        flags,
        size,
        alignment);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static void* CL_API_CALL clSVMAlloc_disp(
    cl_context context,
    cl_svm_mem_flags flags,
    size_t size,
    cl_uint alignment)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, NULL);
    return context->dispatch->clSVMAlloc(
        context,
        flags,
        size,
        alignment);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY void CL_API_CALL clSVMFree(
    cl_context context,
    void* svm_pointer)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
    {
        khrFirstLayer->dispatch.clSVMFree(
            context,
            svm_pointer);
    }
    else
#endif // defined(CL_ENABLE_LAYERS)
    if (context != NULL)
    context->dispatch->clSVMFree(
        context,
        svm_pointer);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static void CL_API_CALL clSVMFree_disp(
    cl_context context,
    void* svm_pointer)
{
    if (context != NULL)
    context->dispatch->clSVMFree(
        context,
        svm_pointer);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_sampler CL_API_CALL clCreateSamplerWithProperties(
    cl_context context,
    const cl_sampler_properties* sampler_properties,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateSamplerWithProperties(
            context,
            sampler_properties,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateSamplerWithProperties(
        context,
        sampler_properties,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_sampler CL_API_CALL clCreateSamplerWithProperties_disp(
    cl_context context,
    const cl_sampler_properties* sampler_properties,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateSamplerWithProperties(
        context,
        sampler_properties,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetKernelArgSVMPointer(
    cl_kernel kernel,
    cl_uint arg_index,
    const void* arg_value)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetKernelArgSVMPointer(
            kernel,
            arg_index,
            arg_value);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clSetKernelArgSVMPointer(
        kernel,
        arg_index,
        arg_value);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetKernelArgSVMPointer_disp(
    cl_kernel kernel,
    cl_uint arg_index,
    const void* arg_value)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clSetKernelArgSVMPointer(
        kernel,
        arg_index,
        arg_value);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetKernelExecInfo(
    cl_kernel kernel,
    cl_kernel_exec_info param_name,
    size_t param_value_size,
    const void* param_value)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetKernelExecInfo(
            kernel,
            param_name,
            param_value_size,
            param_value);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clSetKernelExecInfo(
        kernel,
        param_name,
        param_value_size,
        param_value);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetKernelExecInfo_disp(
    cl_kernel kernel,
    cl_kernel_exec_info param_name,
    size_t param_value_size,
    const void* param_value)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clSetKernelExecInfo(
        kernel,
        param_name,
        param_value_size,
        param_value);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueSVMFree(
    cl_command_queue command_queue,
    cl_uint num_svm_pointers,
    void* svm_pointers[],
    void (CL_CALLBACK* pfn_free_func)(cl_command_queue queue, cl_uint num_svm_pointers, void* svm_pointers[], void* user_data),
    void* user_data,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueSVMFree(
            command_queue,
            num_svm_pointers,
            svm_pointers,
            pfn_free_func,
            user_data,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMFree(
        command_queue,
        num_svm_pointers,
        svm_pointers,
        pfn_free_func,
        user_data,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueSVMFree_disp(
    cl_command_queue command_queue,
    cl_uint num_svm_pointers,
    void* svm_pointers[],
    void (CL_CALLBACK* pfn_free_func)(cl_command_queue queue, cl_uint num_svm_pointers, void* svm_pointers[], void* user_data),
    void* user_data,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMFree(
        command_queue,
        num_svm_pointers,
        svm_pointers,
        pfn_free_func,
        user_data,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueSVMMemcpy(
    cl_command_queue command_queue,
    cl_bool blocking_copy,
    void* dst_ptr,
    const void* src_ptr,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueSVMMemcpy(
            command_queue,
            blocking_copy,
            dst_ptr,
            src_ptr,
            size,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMMemcpy(
        command_queue,
        blocking_copy,
        dst_ptr,
        src_ptr,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueSVMMemcpy_disp(
    cl_command_queue command_queue,
    cl_bool blocking_copy,
    void* dst_ptr,
    const void* src_ptr,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMMemcpy(
        command_queue,
        blocking_copy,
        dst_ptr,
        src_ptr,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueSVMMemFill(
    cl_command_queue command_queue,
    void* svm_ptr,
    const void* pattern,
    size_t pattern_size,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueSVMMemFill(
            command_queue,
            svm_ptr,
            pattern,
            pattern_size,
            size,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMMemFill(
        command_queue,
        svm_ptr,
        pattern,
        pattern_size,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueSVMMemFill_disp(
    cl_command_queue command_queue,
    void* svm_ptr,
    const void* pattern,
    size_t pattern_size,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMMemFill(
        command_queue,
        svm_ptr,
        pattern,
        pattern_size,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueSVMMap(
    cl_command_queue command_queue,
    cl_bool blocking_map,
    cl_map_flags flags,
    void* svm_ptr,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueSVMMap(
            command_queue,
            blocking_map,
            flags,
            svm_ptr,
            size,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMMap(
        command_queue,
        blocking_map,
        flags,
        svm_ptr,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueSVMMap_disp(
    cl_command_queue command_queue,
    cl_bool blocking_map,
    cl_map_flags flags,
    void* svm_ptr,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMMap(
        command_queue,
        blocking_map,
        flags,
        svm_ptr,
        size,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueSVMUnmap(
    cl_command_queue command_queue,
    void* svm_ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueSVMUnmap(
            command_queue,
            svm_ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMUnmap(
        command_queue,
        svm_ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueSVMUnmap_disp(
    cl_command_queue command_queue,
    void* svm_ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMUnmap(
        command_queue,
        svm_ptr,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetDefaultDeviceCommandQueue(
    cl_context context,
    cl_device_id device,
    cl_command_queue command_queue)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetDefaultDeviceCommandQueue(
            context,
            device,
            command_queue);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clSetDefaultDeviceCommandQueue(
        context,
        device,
        command_queue);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetDefaultDeviceCommandQueue_disp(
    cl_context context,
    cl_device_id device,
    cl_command_queue command_queue)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clSetDefaultDeviceCommandQueue(
        context,
        device,
        command_queue);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetDeviceAndHostTimer(
    cl_device_id device,
    cl_ulong* device_timestamp,
    cl_ulong* host_timestamp)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetDeviceAndHostTimer(
            device,
            device_timestamp,
            host_timestamp);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clGetDeviceAndHostTimer(
        device,
        device_timestamp,
        host_timestamp);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetDeviceAndHostTimer_disp(
    cl_device_id device,
    cl_ulong* device_timestamp,
    cl_ulong* host_timestamp)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clGetDeviceAndHostTimer(
        device,
        device_timestamp,
        host_timestamp);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetHostTimer(
    cl_device_id device,
    cl_ulong* host_timestamp)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetHostTimer(
            device,
            host_timestamp);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clGetHostTimer(
        device,
        host_timestamp);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetHostTimer_disp(
    cl_device_id device,
    cl_ulong* host_timestamp)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    return device->dispatch->clGetHostTimer(
        device,
        host_timestamp);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_program CL_API_CALL clCreateProgramWithIL(
    cl_context context,
    const void* il,
    size_t length,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateProgramWithIL(
            context,
            il,
            length,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateProgramWithIL(
        context,
        il,
        length,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_program CL_API_CALL clCreateProgramWithIL_disp(
    cl_context context,
    const void* il,
    size_t length,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateProgramWithIL(
        context,
        il,
        length,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_kernel CL_API_CALL clCloneKernel(
    cl_kernel source_kernel,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCloneKernel(
            source_kernel,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(source_kernel, CL_INVALID_KERNEL);
    return source_kernel->dispatch->clCloneKernel(
        source_kernel,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_kernel CL_API_CALL clCloneKernel_disp(
    cl_kernel source_kernel,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(source_kernel, CL_INVALID_KERNEL);
    return source_kernel->dispatch->clCloneKernel(
        source_kernel,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clGetKernelSubGroupInfo(
    cl_kernel kernel,
    cl_device_id device,
    cl_kernel_sub_group_info param_name,
    size_t input_value_size,
    const void* input_value,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetKernelSubGroupInfo(
            kernel,
            device,
            param_name,
            input_value_size,
            input_value,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clGetKernelSubGroupInfo(
        kernel,
        device,
        param_name,
        input_value_size,
        input_value,
        param_value_size,
        param_value,
        param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetKernelSubGroupInfo_disp(
    cl_kernel kernel,
    cl_device_id device,
    cl_kernel_sub_group_info param_name,
    size_t input_value_size,
    const void* input_value,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(kernel, CL_INVALID_KERNEL);
    return kernel->dispatch->clGetKernelSubGroupInfo(
        kernel,
        device,
        param_name,
        input_value_size,
        input_value,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clEnqueueSVMMigrateMem(
    cl_command_queue command_queue,
    cl_uint num_svm_pointers,
    const void** svm_pointers,
    const size_t* sizes,
    cl_mem_migration_flags flags,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueSVMMigrateMem(
            command_queue,
            num_svm_pointers,
            svm_pointers,
            sizes,
            flags,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMMigrateMem(
        command_queue,
        num_svm_pointers,
        svm_pointers,
        sizes,
        flags,
        num_events_in_wait_list,
        event_wait_list,
        event);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueSVMMigrateMem_disp(
    cl_command_queue command_queue,
    cl_uint num_svm_pointers,
    const void** svm_pointers,
    const size_t* sizes,
    cl_mem_migration_flags flags,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    return command_queue->dispatch->clEnqueueSVMMigrateMem(
        command_queue,
        num_svm_pointers,
        svm_pointers,
        sizes,
        flags,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetProgramSpecializationConstant(
    cl_program program,
    cl_uint spec_id,
    size_t spec_size,
    const void* spec_value)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetProgramSpecializationConstant(
            program,
            spec_id,
            spec_size,
            spec_value);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clSetProgramSpecializationConstant(
        program,
        spec_id,
        spec_size,
        spec_value);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetProgramSpecializationConstant_disp(
    cl_program program,
    cl_uint spec_id,
    size_t spec_size,
    const void* spec_value)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clSetProgramSpecializationConstant(
        program,
        spec_id,
        spec_size,
        spec_value);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetProgramReleaseCallback(
    cl_program program,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetProgramReleaseCallback(
            program,
            pfn_notify,
            user_data);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clSetProgramReleaseCallback(
        program,
        pfn_notify,
        user_data);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetProgramReleaseCallback_disp(
    cl_program program,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(program, CL_INVALID_PROGRAM);
    return program->dispatch->clSetProgramReleaseCallback(
        program,
        pfn_notify,
        user_data);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_int CL_API_CALL clSetContextDestructorCallback(
    cl_context context,
    void (CL_CALLBACK* pfn_notify)(cl_context context, void* user_data),
    void* user_data)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clSetContextDestructorCallback(
            context,
            pfn_notify,
            user_data);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clSetContextDestructorCallback(
        context,
        pfn_notify,
        user_data);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clSetContextDestructorCallback_disp(
    cl_context context,
    void (CL_CALLBACK* pfn_notify)(cl_context context, void* user_data),
    void* user_data)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(context, CL_INVALID_CONTEXT);
    return context->dispatch->clSetContextDestructorCallback(
        context,
        pfn_notify,
        user_data);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_mem CL_API_CALL clCreateBufferWithProperties(
    cl_context context,
    const cl_mem_properties* properties,
    cl_mem_flags flags,
    size_t size,
    void* host_ptr,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateBufferWithProperties(
            context,
            properties,
            flags,
            size,
            host_ptr,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateBufferWithProperties(
        context,
        properties,
        flags,
        size,
        host_ptr,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateBufferWithProperties_disp(
    cl_context context,
    const cl_mem_properties* properties,
    cl_mem_flags flags,
    size_t size,
    void* host_ptr,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateBufferWithProperties(
        context,
        properties,
        flags,
        size,
        host_ptr,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

CL_API_ENTRY cl_mem CL_API_CALL clCreateImageWithProperties(
    cl_context context,
    const cl_mem_properties* properties,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    const cl_image_desc* image_desc,
    void* host_ptr,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateImageWithProperties(
            context,
            properties,
            flags,
            image_format,
            image_desc,
            host_ptr,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateImageWithProperties(
        context,
        properties,
        flags,
        image_format,
        image_desc,
        host_ptr,
        errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateImageWithProperties_disp(
    cl_context context,
    const cl_mem_properties* properties,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    const cl_image_desc* image_desc,
    void* host_ptr,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    return context->dispatch->clCreateImageWithProperties(
        context,
        properties,
        flags,
        image_format,
        image_desc,
        host_ptr,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

// cl_ext_device_fission

CL_API_ENTRY cl_int CL_API_CALL clReleaseDeviceEXT(
    cl_device_id device)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clReleaseDeviceEXT(
            device);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(device->dispatch->clReleaseDeviceEXT);
    return device->dispatch->clReleaseDeviceEXT(
        device);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clReleaseDeviceEXT_disp(
    cl_device_id device)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(device->dispatch->clReleaseDeviceEXT);
    return device->dispatch->clReleaseDeviceEXT(
        device);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clRetainDeviceEXT(
    cl_device_id device)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clRetainDeviceEXT(
            device);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(device->dispatch->clRetainDeviceEXT);
    return device->dispatch->clRetainDeviceEXT(
        device);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clRetainDeviceEXT_disp(
    cl_device_id device)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(device, CL_INVALID_DEVICE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(device->dispatch->clRetainDeviceEXT);
    return device->dispatch->clRetainDeviceEXT(
        device);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clCreateSubDevicesEXT(
    cl_device_id in_device,
    const cl_device_partition_property_ext* properties,
    cl_uint num_entries,
    cl_device_id* out_devices,
    cl_uint* num_devices)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateSubDevicesEXT(
            in_device,
            properties,
            num_entries,
            out_devices,
            num_devices);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(in_device, CL_INVALID_DEVICE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(in_device->dispatch->clCreateSubDevicesEXT);
    return in_device->dispatch->clCreateSubDevicesEXT(
        in_device,
        properties,
        num_entries,
        out_devices,
        num_devices);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clCreateSubDevicesEXT_disp(
    cl_device_id in_device,
    const cl_device_partition_property_ext* properties,
    cl_uint num_entries,
    cl_device_id* out_devices,
    cl_uint* num_devices)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(in_device, CL_INVALID_DEVICE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(in_device->dispatch->clCreateSubDevicesEXT);
    return in_device->dispatch->clCreateSubDevicesEXT(
        in_device,
        properties,
        num_entries,
        out_devices,
        num_devices);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_d3d10_sharing

#if defined(_WIN32)

CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDsFromD3D10KHR(
    cl_platform_id platform,
    cl_d3d10_device_source_khr d3d_device_source,
    void* d3d_object,
    cl_d3d10_device_set_khr d3d_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetDeviceIDsFromD3D10KHR(
            platform,
            d3d_device_source,
            d3d_object,
            d3d_device_set,
            num_entries,
            devices,
            num_devices);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(platform->dispatch->clGetDeviceIDsFromD3D10KHR);
    return platform->dispatch->clGetDeviceIDsFromD3D10KHR(
        platform,
        d3d_device_source,
        d3d_object,
        d3d_device_set,
        num_entries,
        devices,
        num_devices);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetDeviceIDsFromD3D10KHR_disp(
    cl_platform_id platform,
    cl_d3d10_device_source_khr d3d_device_source,
    void* d3d_object,
    cl_d3d10_device_set_khr d3d_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(platform->dispatch->clGetDeviceIDsFromD3D10KHR);
    return platform->dispatch->clGetDeviceIDsFromD3D10KHR(
        platform,
        d3d_device_source,
        d3d_object,
        d3d_device_set,
        num_entries,
        devices,
        num_devices);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D10BufferKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Buffer* resource,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromD3D10BufferKHR(
            context,
            flags,
            resource,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D10BufferKHR);
    return context->dispatch->clCreateFromD3D10BufferKHR(
        context,
        flags,
        resource,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromD3D10BufferKHR_disp(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Buffer* resource,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D10BufferKHR);
    return context->dispatch->clCreateFromD3D10BufferKHR(
        context,
        flags,
        resource,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D10Texture2DKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Texture2D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromD3D10Texture2DKHR(
            context,
            flags,
            resource,
            subresource,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D10Texture2DKHR);
    return context->dispatch->clCreateFromD3D10Texture2DKHR(
        context,
        flags,
        resource,
        subresource,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromD3D10Texture2DKHR_disp(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Texture2D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D10Texture2DKHR);
    return context->dispatch->clCreateFromD3D10Texture2DKHR(
        context,
        flags,
        resource,
        subresource,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D10Texture3DKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Texture3D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromD3D10Texture3DKHR(
            context,
            flags,
            resource,
            subresource,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D10Texture3DKHR);
    return context->dispatch->clCreateFromD3D10Texture3DKHR(
        context,
        flags,
        resource,
        subresource,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromD3D10Texture3DKHR_disp(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Texture3D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D10Texture3DKHR);
    return context->dispatch->clCreateFromD3D10Texture3DKHR(
        context,
        flags,
        resource,
        subresource,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireD3D10ObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueAcquireD3D10ObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireD3D10ObjectsKHR);
    return command_queue->dispatch->clEnqueueAcquireD3D10ObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueAcquireD3D10ObjectsKHR_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireD3D10ObjectsKHR);
    return command_queue->dispatch->clEnqueueAcquireD3D10ObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseD3D10ObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueReleaseD3D10ObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseD3D10ObjectsKHR);
    return command_queue->dispatch->clEnqueueReleaseD3D10ObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueReleaseD3D10ObjectsKHR_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseD3D10ObjectsKHR);
    return command_queue->dispatch->clEnqueueReleaseD3D10ObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

#endif // defined(_WIN32)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_d3d11_sharing

#if defined(_WIN32)

CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDsFromD3D11KHR(
    cl_platform_id platform,
    cl_d3d11_device_source_khr d3d_device_source,
    void* d3d_object,
    cl_d3d11_device_set_khr d3d_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetDeviceIDsFromD3D11KHR(
            platform,
            d3d_device_source,
            d3d_object,
            d3d_device_set,
            num_entries,
            devices,
            num_devices);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(platform->dispatch->clGetDeviceIDsFromD3D11KHR);
    return platform->dispatch->clGetDeviceIDsFromD3D11KHR(
        platform,
        d3d_device_source,
        d3d_object,
        d3d_device_set,
        num_entries,
        devices,
        num_devices);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetDeviceIDsFromD3D11KHR_disp(
    cl_platform_id platform,
    cl_d3d11_device_source_khr d3d_device_source,
    void* d3d_object,
    cl_d3d11_device_set_khr d3d_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(platform->dispatch->clGetDeviceIDsFromD3D11KHR);
    return platform->dispatch->clGetDeviceIDsFromD3D11KHR(
        platform,
        d3d_device_source,
        d3d_object,
        d3d_device_set,
        num_entries,
        devices,
        num_devices);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D11BufferKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Buffer* resource,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromD3D11BufferKHR(
            context,
            flags,
            resource,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D11BufferKHR);
    return context->dispatch->clCreateFromD3D11BufferKHR(
        context,
        flags,
        resource,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromD3D11BufferKHR_disp(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Buffer* resource,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D11BufferKHR);
    return context->dispatch->clCreateFromD3D11BufferKHR(
        context,
        flags,
        resource,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D11Texture2DKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Texture2D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromD3D11Texture2DKHR(
            context,
            flags,
            resource,
            subresource,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D11Texture2DKHR);
    return context->dispatch->clCreateFromD3D11Texture2DKHR(
        context,
        flags,
        resource,
        subresource,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromD3D11Texture2DKHR_disp(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Texture2D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D11Texture2DKHR);
    return context->dispatch->clCreateFromD3D11Texture2DKHR(
        context,
        flags,
        resource,
        subresource,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromD3D11Texture3DKHR(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Texture3D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromD3D11Texture3DKHR(
            context,
            flags,
            resource,
            subresource,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D11Texture3DKHR);
    return context->dispatch->clCreateFromD3D11Texture3DKHR(
        context,
        flags,
        resource,
        subresource,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromD3D11Texture3DKHR_disp(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Texture3D* resource,
    UINT subresource,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromD3D11Texture3DKHR);
    return context->dispatch->clCreateFromD3D11Texture3DKHR(
        context,
        flags,
        resource,
        subresource,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireD3D11ObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueAcquireD3D11ObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireD3D11ObjectsKHR);
    return command_queue->dispatch->clEnqueueAcquireD3D11ObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueAcquireD3D11ObjectsKHR_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireD3D11ObjectsKHR);
    return command_queue->dispatch->clEnqueueAcquireD3D11ObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseD3D11ObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueReleaseD3D11ObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseD3D11ObjectsKHR);
    return command_queue->dispatch->clEnqueueReleaseD3D11ObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueReleaseD3D11ObjectsKHR_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseD3D11ObjectsKHR);
    return command_queue->dispatch->clEnqueueReleaseD3D11ObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

#endif // defined(_WIN32)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_dx9_media_sharing

#if defined(_WIN32)

CL_API_ENTRY cl_int CL_API_CALL clGetDeviceIDsFromDX9MediaAdapterKHR(
    cl_platform_id platform,
    cl_uint num_media_adapters,
    cl_dx9_media_adapter_type_khr* media_adapter_type,
    void* media_adapters,
    cl_dx9_media_adapter_set_khr media_adapter_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetDeviceIDsFromDX9MediaAdapterKHR(
            platform,
            num_media_adapters,
            media_adapter_type,
            media_adapters,
            media_adapter_set,
            num_entries,
            devices,
            num_devices);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(platform->dispatch->clGetDeviceIDsFromDX9MediaAdapterKHR);
    return platform->dispatch->clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform,
        num_media_adapters,
        media_adapter_type,
        media_adapters,
        media_adapter_set,
        num_entries,
        devices,
        num_devices);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetDeviceIDsFromDX9MediaAdapterKHR_disp(
    cl_platform_id platform,
    cl_uint num_media_adapters,
    cl_dx9_media_adapter_type_khr* media_adapter_type,
    void* media_adapters,
    cl_dx9_media_adapter_set_khr media_adapter_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(platform->dispatch->clGetDeviceIDsFromDX9MediaAdapterKHR);
    return platform->dispatch->clGetDeviceIDsFromDX9MediaAdapterKHR(
        platform,
        num_media_adapters,
        media_adapter_type,
        media_adapters,
        media_adapter_set,
        num_entries,
        devices,
        num_devices);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromDX9MediaSurfaceKHR(
    cl_context context,
    cl_mem_flags flags,
    cl_dx9_media_adapter_type_khr adapter_type,
    void* surface_info,
    cl_uint plane,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromDX9MediaSurfaceKHR(
            context,
            flags,
            adapter_type,
            surface_info,
            plane,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromDX9MediaSurfaceKHR);
    return context->dispatch->clCreateFromDX9MediaSurfaceKHR(
        context,
        flags,
        adapter_type,
        surface_info,
        plane,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromDX9MediaSurfaceKHR_disp(
    cl_context context,
    cl_mem_flags flags,
    cl_dx9_media_adapter_type_khr adapter_type,
    void* surface_info,
    cl_uint plane,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromDX9MediaSurfaceKHR);
    return context->dispatch->clCreateFromDX9MediaSurfaceKHR(
        context,
        flags,
        adapter_type,
        surface_info,
        plane,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireDX9MediaSurfacesKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueAcquireDX9MediaSurfacesKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireDX9MediaSurfacesKHR);
    return command_queue->dispatch->clEnqueueAcquireDX9MediaSurfacesKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueAcquireDX9MediaSurfacesKHR_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireDX9MediaSurfacesKHR);
    return command_queue->dispatch->clEnqueueAcquireDX9MediaSurfacesKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseDX9MediaSurfacesKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueReleaseDX9MediaSurfacesKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseDX9MediaSurfacesKHR);
    return command_queue->dispatch->clEnqueueReleaseDX9MediaSurfacesKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueReleaseDX9MediaSurfacesKHR_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseDX9MediaSurfacesKHR);
    return command_queue->dispatch->clEnqueueReleaseDX9MediaSurfacesKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

#endif // defined(_WIN32)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_egl_event

CL_API_ENTRY cl_event CL_API_CALL clCreateEventFromEGLSyncKHR(
    cl_context context,
    CLeglSyncKHR sync,
    CLeglDisplayKHR display,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateEventFromEGLSyncKHR(
            context,
            sync,
            display,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateEventFromEGLSyncKHR);
    return context->dispatch->clCreateEventFromEGLSyncKHR(
        context,
        sync,
        display,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_event CL_API_CALL clCreateEventFromEGLSyncKHR_disp(
    cl_context context,
    CLeglSyncKHR sync,
    CLeglDisplayKHR display,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateEventFromEGLSyncKHR);
    return context->dispatch->clCreateEventFromEGLSyncKHR(
        context,
        sync,
        display,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_egl_image

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromEGLImageKHR(
    cl_context context,
    CLeglDisplayKHR egldisplay,
    CLeglImageKHR eglimage,
    cl_mem_flags flags,
    const cl_egl_image_properties_khr* properties,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromEGLImageKHR(
            context,
            egldisplay,
            eglimage,
            flags,
            properties,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromEGLImageKHR);
    return context->dispatch->clCreateFromEGLImageKHR(
        context,
        egldisplay,
        eglimage,
        flags,
        properties,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromEGLImageKHR_disp(
    cl_context context,
    CLeglDisplayKHR egldisplay,
    CLeglImageKHR eglimage,
    cl_mem_flags flags,
    const cl_egl_image_properties_khr* properties,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromEGLImageKHR);
    return context->dispatch->clCreateFromEGLImageKHR(
        context,
        egldisplay,
        eglimage,
        flags,
        properties,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireEGLObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueAcquireEGLObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireEGLObjectsKHR);
    return command_queue->dispatch->clEnqueueAcquireEGLObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueAcquireEGLObjectsKHR_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireEGLObjectsKHR);
    return command_queue->dispatch->clEnqueueAcquireEGLObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseEGLObjectsKHR(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueReleaseEGLObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseEGLObjectsKHR);
    return command_queue->dispatch->clEnqueueReleaseEGLObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueReleaseEGLObjectsKHR_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseEGLObjectsKHR);
    return command_queue->dispatch->clEnqueueReleaseEGLObjectsKHR(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_gl_event

CL_API_ENTRY cl_event CL_API_CALL clCreateEventFromGLsyncKHR(
    cl_context context,
    cl_GLsync sync,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateEventFromGLsyncKHR(
            context,
            sync,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateEventFromGLsyncKHR);
    return context->dispatch->clCreateEventFromGLsyncKHR(
        context,
        sync,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_event CL_API_CALL clCreateEventFromGLsyncKHR_disp(
    cl_context context,
    cl_GLsync sync,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateEventFromGLsyncKHR);
    return context->dispatch->clCreateEventFromGLsyncKHR(
        context,
        sync,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_gl_sharing

CL_API_ENTRY cl_int CL_API_CALL clGetGLContextInfoKHR(
    const cl_context_properties* properties,
    cl_gl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetGLContextInfoKHR(
            properties,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    cl_platform_id platform = NULL;
    khrIcdContextPropertiesGetPlatform(properties, &platform);
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(platform->dispatch->clGetGLContextInfoKHR);
    return platform->dispatch->clGetGLContextInfoKHR(
        properties,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetGLContextInfoKHR_disp(
    const cl_context_properties* properties,
    cl_gl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    cl_platform_id platform = NULL;
    khrIcdContextPropertiesGetPlatform(properties, &platform);
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(platform->dispatch->clGetGLContextInfoKHR);
    return platform->dispatch->clGetGLContextInfoKHR(
        properties,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromGLBuffer(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint bufobj,
    int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromGLBuffer(
            context,
            flags,
            bufobj,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLBuffer);
    return context->dispatch->clCreateFromGLBuffer(
        context,
        flags,
        bufobj,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromGLBuffer_disp(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint bufobj,
    int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLBuffer);
    return context->dispatch->clCreateFromGLBuffer(
        context,
        flags,
        bufobj,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromGLTexture(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromGLTexture(
            context,
            flags,
            target,
            miplevel,
            texture,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLTexture);
    return context->dispatch->clCreateFromGLTexture(
        context,
        flags,
        target,
        miplevel,
        texture,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromGLTexture_disp(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLTexture);
    return context->dispatch->clCreateFromGLTexture(
        context,
        flags,
        target,
        miplevel,
        texture,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromGLRenderbuffer(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint renderbuffer,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromGLRenderbuffer(
            context,
            flags,
            renderbuffer,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLRenderbuffer);
    return context->dispatch->clCreateFromGLRenderbuffer(
        context,
        flags,
        renderbuffer,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromGLRenderbuffer_disp(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint renderbuffer,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLRenderbuffer);
    return context->dispatch->clCreateFromGLRenderbuffer(
        context,
        flags,
        renderbuffer,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clGetGLObjectInfo(
    cl_mem memobj,
    cl_gl_object_type* gl_object_type,
    cl_GLuint* gl_object_name)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetGLObjectInfo(
            memobj,
            gl_object_type,
            gl_object_name);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(memobj->dispatch->clGetGLObjectInfo);
    return memobj->dispatch->clGetGLObjectInfo(
        memobj,
        gl_object_type,
        gl_object_name);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetGLObjectInfo_disp(
    cl_mem memobj,
    cl_gl_object_type* gl_object_type,
    cl_GLuint* gl_object_name)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(memobj->dispatch->clGetGLObjectInfo);
    return memobj->dispatch->clGetGLObjectInfo(
        memobj,
        gl_object_type,
        gl_object_name);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clGetGLTextureInfo(
    cl_mem memobj,
    cl_gl_texture_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetGLTextureInfo(
            memobj,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(memobj->dispatch->clGetGLTextureInfo);
    return memobj->dispatch->clGetGLTextureInfo(
        memobj,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetGLTextureInfo_disp(
    cl_mem memobj,
    cl_gl_texture_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(memobj, CL_INVALID_MEM_OBJECT);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(memobj->dispatch->clGetGLTextureInfo);
    return memobj->dispatch->clGetGLTextureInfo(
        memobj,
        param_name,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueAcquireGLObjects(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueAcquireGLObjects(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireGLObjects);
    return command_queue->dispatch->clEnqueueAcquireGLObjects(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueAcquireGLObjects_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueAcquireGLObjects);
    return command_queue->dispatch->clEnqueueAcquireGLObjects(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_int CL_API_CALL clEnqueueReleaseGLObjects(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clEnqueueReleaseGLObjects(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseGLObjects);
    return command_queue->dispatch->clEnqueueReleaseGLObjects(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clEnqueueReleaseGLObjects_disp(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(command_queue, CL_INVALID_COMMAND_QUEUE);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(command_queue->dispatch->clEnqueueReleaseGLObjects);
    return command_queue->dispatch->clEnqueueReleaseGLObjects(
        command_queue,
        num_objects,
        mem_objects,
        num_events_in_wait_list,
        event_wait_list,
        event);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromGLTexture2D(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromGLTexture2D(
            context,
            flags,
            target,
            miplevel,
            texture,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLTexture2D);
    return context->dispatch->clCreateFromGLTexture2D(
        context,
        flags,
        target,
        miplevel,
        texture,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromGLTexture2D_disp(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLTexture2D);
    return context->dispatch->clCreateFromGLTexture2D(
        context,
        flags,
        target,
        miplevel,
        texture,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

CL_API_ENTRY cl_mem CL_API_CALL clCreateFromGLTexture3D(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clCreateFromGLTexture3D(
            context,
            flags,
            target,
            miplevel,
            texture,
            errcode_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLTexture3D);
    return context->dispatch->clCreateFromGLTexture3D(
        context,
        flags,
        target,
        miplevel,
        texture,
        errcode_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_mem CL_API_CALL clCreateFromGLTexture3D_disp(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(context, CL_INVALID_CONTEXT);
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(context->dispatch->clCreateFromGLTexture3D);
    return context->dispatch->clCreateFromGLTexture3D(
        context,
        flags,
        target,
        miplevel,
        texture,
        errcode_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_subgroups

CL_API_ENTRY cl_int CL_API_CALL clGetKernelSubGroupInfoKHR(
    cl_kernel in_kernel,
    cl_device_id in_device,
    cl_kernel_sub_group_info param_name,
    size_t input_value_size,
    const void* input_value,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.clGetKernelSubGroupInfoKHR(
            in_kernel,
            in_device,
            param_name,
            input_value_size,
            input_value,
            param_value_size,
            param_value,
            param_value_size_ret);
#endif // defined(CL_ENABLE_LAYERS)
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(in_kernel, CL_INVALID_KERNEL);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(in_kernel->dispatch->clGetKernelSubGroupInfoKHR);
    return in_kernel->dispatch->clGetKernelSubGroupInfoKHR(
        in_kernel,
        in_device,
        param_name,
        input_value_size,
        input_value,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#if defined(CL_ENABLE_LAYERS)
static cl_int CL_API_CALL clGetKernelSubGroupInfoKHR_disp(
    cl_kernel in_kernel,
    cl_device_id in_device,
    cl_kernel_sub_group_info param_name,
    size_t input_value_size,
    const void* input_value,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret)
{
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(in_kernel, CL_INVALID_KERNEL);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(in_kernel->dispatch->clGetKernelSubGroupInfoKHR);
    return in_kernel->dispatch->clGetKernelSubGroupInfoKHR(
        in_kernel,
        in_device,
        param_name,
        input_value_size,
        input_value,
        param_value_size,
        param_value,
        param_value_size_ret);
}
#endif // defined(CL_ENABLE_LAYERS)

///////////////////////////////////////////////////////////////////////////////

#if defined(CL_ENABLE_LAYERS)
struct _cl_icd_dispatch khrMasterDispatch = {
    &clGetPlatformIDs_disp,
    &clGetPlatformInfo_disp,
    &clGetDeviceIDs_disp,
    &clGetDeviceInfo_disp,
    &clCreateContext_disp,
    &clCreateContextFromType_disp,
    &clRetainContext_disp,
    &clReleaseContext_disp,
    &clGetContextInfo_disp,
    &clCreateCommandQueue_disp,
    &clRetainCommandQueue_disp,
    &clReleaseCommandQueue_disp,
    &clGetCommandQueueInfo_disp,
    &clSetCommandQueueProperty_disp,
    &clCreateBuffer_disp,
    &clCreateImage2D_disp,
    &clCreateImage3D_disp,
    &clRetainMemObject_disp,
    &clReleaseMemObject_disp,
    &clGetSupportedImageFormats_disp,
    &clGetMemObjectInfo_disp,
    &clGetImageInfo_disp,
    &clCreateSampler_disp,
    &clRetainSampler_disp,
    &clReleaseSampler_disp,
    &clGetSamplerInfo_disp,
    &clCreateProgramWithSource_disp,
    &clCreateProgramWithBinary_disp,
    &clRetainProgram_disp,
    &clReleaseProgram_disp,
    &clBuildProgram_disp,
    &clUnloadCompiler_disp,
    &clGetProgramInfo_disp,
    &clGetProgramBuildInfo_disp,
    &clCreateKernel_disp,
    &clCreateKernelsInProgram_disp,
    &clRetainKernel_disp,
    &clReleaseKernel_disp,
    &clSetKernelArg_disp,
    &clGetKernelInfo_disp,
    &clGetKernelWorkGroupInfo_disp,
    &clWaitForEvents_disp,
    &clGetEventInfo_disp,
    &clRetainEvent_disp,
    &clReleaseEvent_disp,
    &clGetEventProfilingInfo_disp,
    &clFlush_disp,
    &clFinish_disp,
    &clEnqueueReadBuffer_disp,
    &clEnqueueWriteBuffer_disp,
    &clEnqueueCopyBuffer_disp,
    &clEnqueueReadImage_disp,
    &clEnqueueWriteImage_disp,
    &clEnqueueCopyImage_disp,
    &clEnqueueCopyImageToBuffer_disp,
    &clEnqueueCopyBufferToImage_disp,
    &clEnqueueMapBuffer_disp,
    &clEnqueueMapImage_disp,
    &clEnqueueUnmapMemObject_disp,
    &clEnqueueNDRangeKernel_disp,
    &clEnqueueTask_disp,
    &clEnqueueNativeKernel_disp,
    &clEnqueueMarker_disp,
    &clEnqueueWaitForEvents_disp,
    &clEnqueueBarrier_disp,
    &clGetExtensionFunctionAddress_disp,
    &clCreateFromGLBuffer_disp,
    &clCreateFromGLTexture2D_disp,
    &clCreateFromGLTexture3D_disp,
    &clCreateFromGLRenderbuffer_disp,
    &clGetGLObjectInfo_disp,
    &clGetGLTextureInfo_disp,
    &clEnqueueAcquireGLObjects_disp,
    &clEnqueueReleaseGLObjects_disp,
    &clGetGLContextInfoKHR_disp,

  /* cl_khr_d3d10_sharing */
#if defined(_WIN32)
    &clGetDeviceIDsFromD3D10KHR_disp,
    &clCreateFromD3D10BufferKHR_disp,
    &clCreateFromD3D10Texture2DKHR_disp,
    &clCreateFromD3D10Texture3DKHR_disp,
    &clEnqueueAcquireD3D10ObjectsKHR_disp,
    &clEnqueueReleaseD3D10ObjectsKHR_disp,
#else
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#endif

  /* OpenCL 1.1 */
    &clSetEventCallback_disp,
    &clCreateSubBuffer_disp,
    &clSetMemObjectDestructorCallback_disp,
    &clCreateUserEvent_disp,
    &clSetUserEventStatus_disp,
    &clEnqueueReadBufferRect_disp,
    &clEnqueueWriteBufferRect_disp,
    &clEnqueueCopyBufferRect_disp,

  /* cl_ext_device_fission */
    &clCreateSubDevicesEXT_disp,
    &clRetainDeviceEXT_disp,
    &clReleaseDeviceEXT_disp,

  /* cl_khr_gl_event */
    &clCreateEventFromGLsyncKHR_disp,

  /* OpenCL 1.2 */
    &clCreateSubDevices_disp,
    &clRetainDevice_disp,
    &clReleaseDevice_disp,
    &clCreateImage_disp,
    &clCreateProgramWithBuiltInKernels_disp,
    &clCompileProgram_disp,
    &clLinkProgram_disp,
    &clUnloadPlatformCompiler_disp,
    &clGetKernelArgInfo_disp,
    &clEnqueueFillBuffer_disp,
    &clEnqueueFillImage_disp,
    &clEnqueueMigrateMemObjects_disp,
    &clEnqueueMarkerWithWaitList_disp,
    &clEnqueueBarrierWithWaitList_disp,
    &clGetExtensionFunctionAddressForPlatform_disp,
    &clCreateFromGLTexture_disp,

  /* cl_khr_d3d11_sharing */
#if defined(_WIN32)
    &clGetDeviceIDsFromD3D11KHR_disp,
    &clCreateFromD3D11BufferKHR_disp,
    &clCreateFromD3D11Texture2DKHR_disp,
    &clCreateFromD3D11Texture3DKHR_disp,
    &clCreateFromDX9MediaSurfaceKHR_disp,
    &clEnqueueAcquireD3D11ObjectsKHR_disp,
    &clEnqueueReleaseD3D11ObjectsKHR_disp,
#else
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#endif

  /* cl_khr_dx9_media_sharing */
#if defined(_WIN32)
    &clGetDeviceIDsFromDX9MediaAdapterKHR_disp,
    &clEnqueueAcquireDX9MediaSurfacesKHR_disp,
    &clEnqueueReleaseDX9MediaSurfacesKHR_disp,
#else
    NULL,
    NULL,
    NULL,
#endif

  /* cl_khr_egl_image */
    &clCreateFromEGLImageKHR_disp,
    &clEnqueueAcquireEGLObjectsKHR_disp,
    &clEnqueueReleaseEGLObjectsKHR_disp,

  /* cl_khr_egl_event */
    &clCreateEventFromEGLSyncKHR_disp,

  /* OpenCL 2.0 */
    &clCreateCommandQueueWithProperties_disp,
    &clCreatePipe_disp,
    &clGetPipeInfo_disp,
    &clSVMAlloc_disp,
    &clSVMFree_disp,
    &clEnqueueSVMFree_disp,
    &clEnqueueSVMMemcpy_disp,
    &clEnqueueSVMMemFill_disp,
    &clEnqueueSVMMap_disp,
    &clEnqueueSVMUnmap_disp,
    &clCreateSamplerWithProperties_disp,
    &clSetKernelArgSVMPointer_disp,
    &clSetKernelExecInfo_disp,

  /* cl_khr_sub_groups */
    &clGetKernelSubGroupInfoKHR_disp,

  /* OpenCL 2.1 */
    &clCloneKernel_disp,
    &clCreateProgramWithIL_disp,
    &clEnqueueSVMMigrateMem_disp,
    &clGetDeviceAndHostTimer_disp,
    &clGetHostTimer_disp,
    &clGetKernelSubGroupInfo_disp,
    &clSetDefaultDeviceCommandQueue_disp,

  /* OpenCL 2.2 */
    &clSetProgramReleaseCallback_disp,
    &clSetProgramSpecializationConstant_disp,

  /* OpenCL 3.0 */
    &clCreateBufferWithProperties_disp,
    &clCreateImageWithProperties_disp,
    &clSetContextDestructorCallback_disp
};
#endif // defined(CL_ENABLE_LAYERS)
#ifdef __cplusplus
}
#endif
