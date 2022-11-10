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

///////////////////////////////////////////////////////////////////////////////
// Core APIs:
static cl_int CL_API_CALL clGetPlatformIDs_wrap(
    cl_uint num_entries,
    cl_platform_id* platforms,
    cl_uint* num_platforms) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetPlatformIDs\n");
return tdispatch->clGetPlatformIDs(
            num_entries,
            platforms,
            num_platforms);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetPlatformInfo_wrap(
    cl_platform_id platform,
    cl_platform_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetPlatformInfo\n");
return tdispatch->clGetPlatformInfo(
            platform,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetDeviceIDs_wrap(
    cl_platform_id platform,
    cl_device_type device_type,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetDeviceIDs\n");
return tdispatch->clGetDeviceIDs(
            platform,
            device_type,
            num_entries,
            devices,
            num_devices);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetDeviceInfo_wrap(
    cl_device_id device,
    cl_device_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetDeviceInfo\n");
return tdispatch->clGetDeviceInfo(
            device,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_context CL_API_CALL clCreateContext_wrap(
    const cl_context_properties* properties,
    cl_uint num_devices,
    const cl_device_id* devices,
    void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data),
    void* user_data,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateContext\n");
return tdispatch->clCreateContext(
            properties,
            num_devices,
            devices,
            pfn_notify,
            user_data,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_context CL_API_CALL clCreateContextFromType_wrap(
    const cl_context_properties* properties,
    cl_device_type device_type,
    void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data),
    void* user_data,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateContextFromType\n");
return tdispatch->clCreateContextFromType(
            properties,
            device_type,
            pfn_notify,
            user_data,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clRetainContext_wrap(
    cl_context context) CL_API_SUFFIX__VERSION_1_0
{
printf("clRetainContext\n");
return tdispatch->clRetainContext(
            context);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clReleaseContext_wrap(
    cl_context context) CL_API_SUFFIX__VERSION_1_0
{
printf("clReleaseContext\n");
return tdispatch->clReleaseContext(
            context);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetContextInfo_wrap(
    cl_context context,
    cl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetContextInfo\n");
return tdispatch->clGetContextInfo(
            context,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clRetainCommandQueue_wrap(
    cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_0
{
printf("clRetainCommandQueue\n");
return tdispatch->clRetainCommandQueue(
            command_queue);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clReleaseCommandQueue_wrap(
    cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_0
{
printf("clReleaseCommandQueue\n");
return tdispatch->clReleaseCommandQueue(
            command_queue);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetCommandQueueInfo_wrap(
    cl_command_queue command_queue,
    cl_command_queue_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetCommandQueueInfo\n");
return tdispatch->clGetCommandQueueInfo(
            command_queue,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_mem CL_API_CALL clCreateBuffer_wrap(
    cl_context context,
    cl_mem_flags flags,
    size_t size,
    void* host_ptr,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateBuffer\n");
return tdispatch->clCreateBuffer(
            context,
            flags,
            size,
            host_ptr,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clRetainMemObject_wrap(
    cl_mem memobj) CL_API_SUFFIX__VERSION_1_0
{
printf("clRetainMemObject\n");
return tdispatch->clRetainMemObject(
            memobj);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clReleaseMemObject_wrap(
    cl_mem memobj) CL_API_SUFFIX__VERSION_1_0
{
printf("clReleaseMemObject\n");
return tdispatch->clReleaseMemObject(
            memobj);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetSupportedImageFormats_wrap(
    cl_context context,
    cl_mem_flags flags,
    cl_mem_object_type image_type,
    cl_uint num_entries,
    cl_image_format* image_formats,
    cl_uint* num_image_formats) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetSupportedImageFormats\n");
return tdispatch->clGetSupportedImageFormats(
            context,
            flags,
            image_type,
            num_entries,
            image_formats,
            num_image_formats);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetMemObjectInfo_wrap(
    cl_mem memobj,
    cl_mem_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetMemObjectInfo\n");
return tdispatch->clGetMemObjectInfo(
            memobj,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetImageInfo_wrap(
    cl_mem image,
    cl_image_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetImageInfo\n");
return tdispatch->clGetImageInfo(
            image,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clRetainSampler_wrap(
    cl_sampler sampler) CL_API_SUFFIX__VERSION_1_0
{
printf("clRetainSampler\n");
return tdispatch->clRetainSampler(
            sampler);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clReleaseSampler_wrap(
    cl_sampler sampler) CL_API_SUFFIX__VERSION_1_0
{
printf("clReleaseSampler\n");
return tdispatch->clReleaseSampler(
            sampler);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetSamplerInfo_wrap(
    cl_sampler sampler,
    cl_sampler_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetSamplerInfo\n");
return tdispatch->clGetSamplerInfo(
            sampler,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_program CL_API_CALL clCreateProgramWithSource_wrap(
    cl_context context,
    cl_uint count,
    const char** strings,
    const size_t* lengths,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateProgramWithSource\n");
return tdispatch->clCreateProgramWithSource(
            context,
            count,
            strings,
            lengths,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_program CL_API_CALL clCreateProgramWithBinary_wrap(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const size_t* lengths,
    const unsigned char** binaries,
    cl_int* binary_status,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateProgramWithBinary\n");
return tdispatch->clCreateProgramWithBinary(
            context,
            num_devices,
            device_list,
            lengths,
            binaries,
            binary_status,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clRetainProgram_wrap(
    cl_program program) CL_API_SUFFIX__VERSION_1_0
{
printf("clRetainProgram\n");
return tdispatch->clRetainProgram(
            program);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clReleaseProgram_wrap(
    cl_program program) CL_API_SUFFIX__VERSION_1_0
{
printf("clReleaseProgram\n");
return tdispatch->clReleaseProgram(
            program);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clBuildProgram_wrap(
    cl_program program,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data) CL_API_SUFFIX__VERSION_1_0
{
printf("clBuildProgram\n");
return tdispatch->clBuildProgram(
            program,
            num_devices,
            device_list,
            options,
            pfn_notify,
            user_data);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetProgramInfo_wrap(
    cl_program program,
    cl_program_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetProgramInfo\n");
return tdispatch->clGetProgramInfo(
            program,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetProgramBuildInfo_wrap(
    cl_program program,
    cl_device_id device,
    cl_program_build_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetProgramBuildInfo\n");
return tdispatch->clGetProgramBuildInfo(
            program,
            device,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_kernel CL_API_CALL clCreateKernel_wrap(
    cl_program program,
    const char* kernel_name,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateKernel\n");
return tdispatch->clCreateKernel(
            program,
            kernel_name,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clCreateKernelsInProgram_wrap(
    cl_program program,
    cl_uint num_kernels,
    cl_kernel* kernels,
    cl_uint* num_kernels_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateKernelsInProgram\n");
return tdispatch->clCreateKernelsInProgram(
            program,
            num_kernels,
            kernels,
            num_kernels_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clRetainKernel_wrap(
    cl_kernel kernel) CL_API_SUFFIX__VERSION_1_0
{
printf("clRetainKernel\n");
return tdispatch->clRetainKernel(
            kernel);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clReleaseKernel_wrap(
    cl_kernel kernel) CL_API_SUFFIX__VERSION_1_0
{
printf("clReleaseKernel\n");
return tdispatch->clReleaseKernel(
            kernel);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clSetKernelArg_wrap(
    cl_kernel kernel,
    cl_uint arg_index,
    size_t arg_size,
    const void* arg_value) CL_API_SUFFIX__VERSION_1_0
{
printf("clSetKernelArg\n");
return tdispatch->clSetKernelArg(
            kernel,
            arg_index,
            arg_size,
            arg_value);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetKernelInfo_wrap(
    cl_kernel kernel,
    cl_kernel_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetKernelInfo\n");
return tdispatch->clGetKernelInfo(
            kernel,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetKernelWorkGroupInfo_wrap(
    cl_kernel kernel,
    cl_device_id device,
    cl_kernel_work_group_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetKernelWorkGroupInfo\n");
return tdispatch->clGetKernelWorkGroupInfo(
            kernel,
            device,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clWaitForEvents_wrap(
    cl_uint num_events,
    const cl_event* event_list) CL_API_SUFFIX__VERSION_1_0
{
printf("clWaitForEvents\n");
return tdispatch->clWaitForEvents(
            num_events,
            event_list);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetEventInfo_wrap(
    cl_event event,
    cl_event_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetEventInfo\n");
return tdispatch->clGetEventInfo(
            event,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clRetainEvent_wrap(
    cl_event event) CL_API_SUFFIX__VERSION_1_0
{
printf("clRetainEvent\n");
return tdispatch->clRetainEvent(
            event);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clReleaseEvent_wrap(
    cl_event event) CL_API_SUFFIX__VERSION_1_0
{
printf("clReleaseEvent\n");
return tdispatch->clReleaseEvent(
            event);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetEventProfilingInfo_wrap(
    cl_event event,
    cl_profiling_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetEventProfilingInfo\n");
return tdispatch->clGetEventProfilingInfo(
            event,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clFlush_wrap(
    cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_0
{
printf("clFlush\n");
return tdispatch->clFlush(
            command_queue);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clFinish_wrap(
    cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_0
{
printf("clFinish\n");
return tdispatch->clFinish(
            command_queue);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueReadBuffer_wrap(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_read,
    size_t offset,
    size_t size,
    void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueReadBuffer\n");
return tdispatch->clEnqueueReadBuffer(
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
static cl_int CL_API_CALL clEnqueueWriteBuffer_wrap(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_write,
    size_t offset,
    size_t size,
    const void* ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueWriteBuffer\n");
return tdispatch->clEnqueueWriteBuffer(
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
static cl_int CL_API_CALL clEnqueueCopyBuffer_wrap(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_buffer,
    size_t src_offset,
    size_t dst_offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueCopyBuffer\n");
return tdispatch->clEnqueueCopyBuffer(
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
static cl_int CL_API_CALL clEnqueueReadImage_wrap(
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
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueReadImage\n");
return tdispatch->clEnqueueReadImage(
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
static cl_int CL_API_CALL clEnqueueWriteImage_wrap(
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
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueWriteImage\n");
return tdispatch->clEnqueueWriteImage(
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
static cl_int CL_API_CALL clEnqueueCopyImage_wrap(
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_image,
    const size_t* src_origin,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueCopyImage\n");
return tdispatch->clEnqueueCopyImage(
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
static cl_int CL_API_CALL clEnqueueCopyImageToBuffer_wrap(
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_buffer,
    const size_t* src_origin,
    const size_t* region,
    size_t dst_offset,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueCopyImageToBuffer\n");
return tdispatch->clEnqueueCopyImageToBuffer(
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
static cl_int CL_API_CALL clEnqueueCopyBufferToImage_wrap(
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_image,
    size_t src_offset,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueCopyBufferToImage\n");
return tdispatch->clEnqueueCopyBufferToImage(
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
static void* CL_API_CALL clEnqueueMapBuffer_wrap(
    cl_command_queue command_queue,
    cl_mem buffer,
    cl_bool blocking_map,
    cl_map_flags map_flags,
    size_t offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueMapBuffer\n");
return tdispatch->clEnqueueMapBuffer(
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
static void* CL_API_CALL clEnqueueMapImage_wrap(
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
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueMapImage\n");
return tdispatch->clEnqueueMapImage(
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
static cl_int CL_API_CALL clEnqueueUnmapMemObject_wrap(
    cl_command_queue command_queue,
    cl_mem memobj,
    void* mapped_ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueUnmapMemObject\n");
return tdispatch->clEnqueueUnmapMemObject(
            command_queue,
            memobj,
            mapped_ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueNDRangeKernel_wrap(
    cl_command_queue command_queue,
    cl_kernel kernel,
    cl_uint work_dim,
    const size_t* global_work_offset,
    const size_t* global_work_size,
    const size_t* local_work_size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueNDRangeKernel\n");
return tdispatch->clEnqueueNDRangeKernel(
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
static cl_int CL_API_CALL clEnqueueNativeKernel_wrap(
    cl_command_queue command_queue,
    void (CL_CALLBACK* user_func)(void*),
    void* args,
    size_t cb_args,
    cl_uint num_mem_objects,
    const cl_mem* mem_list,
    const void** args_mem_loc,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueNativeKernel\n");
return tdispatch->clEnqueueNativeKernel(
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
static cl_int CL_API_CALL clSetCommandQueueProperty_wrap(
    cl_command_queue command_queue,
    cl_command_queue_properties properties,
    cl_bool enable,
    cl_command_queue_properties* old_properties) CL_API_SUFFIX__VERSION_1_0_DEPRECATED
{
printf("clSetCommandQueueProperty\n");
return tdispatch->clSetCommandQueueProperty(
            command_queue,
            properties,
            enable,
            old_properties);
}

///////////////////////////////////////////////////////////////////////////////
static cl_mem CL_API_CALL clCreateImage2D_wrap(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    size_t image_width,
    size_t image_height,
    size_t image_row_pitch,
    void* host_ptr,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1_DEPRECATED
{
printf("clCreateImage2D\n");
return tdispatch->clCreateImage2D(
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
static cl_mem CL_API_CALL clCreateImage3D_wrap(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    size_t image_width,
    size_t image_height,
    size_t image_depth,
    size_t image_row_pitch,
    size_t image_slice_pitch,
    void* host_ptr,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1_DEPRECATED
{
printf("clCreateImage3D\n");
return tdispatch->clCreateImage3D(
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
static cl_int CL_API_CALL clEnqueueMarker_wrap(
    cl_command_queue command_queue,
    cl_event* event) CL_API_SUFFIX__VERSION_1_1_DEPRECATED
{
printf("clEnqueueMarker\n");
return tdispatch->clEnqueueMarker(
            command_queue,
            event);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueWaitForEvents_wrap(
    cl_command_queue command_queue,
    cl_uint num_events,
    const cl_event* event_list) CL_API_SUFFIX__VERSION_1_1_DEPRECATED
{
printf("clEnqueueWaitForEvents\n");
return tdispatch->clEnqueueWaitForEvents(
            command_queue,
            num_events,
            event_list);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueBarrier_wrap(
    cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_1_DEPRECATED
{
printf("clEnqueueBarrier\n");
return tdispatch->clEnqueueBarrier(
            command_queue);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clUnloadCompiler_wrap(
    void ) CL_API_SUFFIX__VERSION_1_1_DEPRECATED
{
printf("clUnloadCompiler\n");
return tdispatch->clUnloadCompiler(
            );
}

///////////////////////////////////////////////////////////////////////////////
static void* CL_API_CALL clGetExtensionFunctionAddress_wrap(
    const char* func_name) CL_API_SUFFIX__VERSION_1_1_DEPRECATED
{
printf("clGetExtensionFunctionAddress\n");
return tdispatch->clGetExtensionFunctionAddress(
            func_name);
}

///////////////////////////////////////////////////////////////////////////////
static cl_command_queue CL_API_CALL clCreateCommandQueue_wrap(
    cl_context context,
    cl_device_id device,
    cl_command_queue_properties properties,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2_DEPRECATED
{
printf("clCreateCommandQueue\n");
return tdispatch->clCreateCommandQueue(
            context,
            device,
            properties,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_sampler CL_API_CALL clCreateSampler_wrap(
    cl_context context,
    cl_bool normalized_coords,
    cl_addressing_mode addressing_mode,
    cl_filter_mode filter_mode,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2_DEPRECATED
{
printf("clCreateSampler\n");
return tdispatch->clCreateSampler(
            context,
            normalized_coords,
            addressing_mode,
            filter_mode,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueTask_wrap(
    cl_command_queue command_queue,
    cl_kernel kernel,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2_DEPRECATED
{
printf("clEnqueueTask\n");
return tdispatch->clEnqueueTask(
            command_queue,
            kernel,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

///////////////////////////////////////////////////////////////////////////////
static cl_mem CL_API_CALL clCreateSubBuffer_wrap(
    cl_mem buffer,
    cl_mem_flags flags,
    cl_buffer_create_type buffer_create_type,
    const void* buffer_create_info,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1
{
printf("clCreateSubBuffer\n");
return tdispatch->clCreateSubBuffer(
            buffer,
            flags,
            buffer_create_type,
            buffer_create_info,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clSetMemObjectDestructorCallback_wrap(
    cl_mem memobj,
    void (CL_CALLBACK* pfn_notify)(cl_mem memobj, void* user_data),
    void* user_data) CL_API_SUFFIX__VERSION_1_1
{
printf("clSetMemObjectDestructorCallback\n");
return tdispatch->clSetMemObjectDestructorCallback(
            memobj,
            pfn_notify,
            user_data);
}

///////////////////////////////////////////////////////////////////////////////
static cl_event CL_API_CALL clCreateUserEvent_wrap(
    cl_context context,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1
{
printf("clCreateUserEvent\n");
return tdispatch->clCreateUserEvent(
            context,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clSetUserEventStatus_wrap(
    cl_event event,
    cl_int execution_status) CL_API_SUFFIX__VERSION_1_1
{
printf("clSetUserEventStatus\n");
return tdispatch->clSetUserEventStatus(
            event,
            execution_status);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clSetEventCallback_wrap(
    cl_event event,
    cl_int command_exec_callback_type,
    void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data),
    void* user_data) CL_API_SUFFIX__VERSION_1_1
{
printf("clSetEventCallback\n");
return tdispatch->clSetEventCallback(
            event,
            command_exec_callback_type,
            pfn_notify,
            user_data);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueReadBufferRect_wrap(
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
    cl_event* event) CL_API_SUFFIX__VERSION_1_1
{
printf("clEnqueueReadBufferRect\n");
return tdispatch->clEnqueueReadBufferRect(
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
static cl_int CL_API_CALL clEnqueueWriteBufferRect_wrap(
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
    cl_event* event) CL_API_SUFFIX__VERSION_1_1
{
printf("clEnqueueWriteBufferRect\n");
return tdispatch->clEnqueueWriteBufferRect(
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
static cl_int CL_API_CALL clEnqueueCopyBufferRect_wrap(
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
    cl_event* event) CL_API_SUFFIX__VERSION_1_1
{
printf("clEnqueueCopyBufferRect\n");
return tdispatch->clEnqueueCopyBufferRect(
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
static cl_int CL_API_CALL clCreateSubDevices_wrap(
    cl_device_id in_device,
    const cl_device_partition_property* properties,
    cl_uint num_devices,
    cl_device_id* out_devices,
    cl_uint* num_devices_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clCreateSubDevices\n");
return tdispatch->clCreateSubDevices(
            in_device,
            properties,
            num_devices,
            out_devices,
            num_devices_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clRetainDevice_wrap(
    cl_device_id device) CL_API_SUFFIX__VERSION_1_2
{
printf("clRetainDevice\n");
return tdispatch->clRetainDevice(
            device);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clReleaseDevice_wrap(
    cl_device_id device) CL_API_SUFFIX__VERSION_1_2
{
printf("clReleaseDevice\n");
return tdispatch->clReleaseDevice(
            device);
}

///////////////////////////////////////////////////////////////////////////////
static cl_mem CL_API_CALL clCreateImage_wrap(
    cl_context context,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    const cl_image_desc* image_desc,
    void* host_ptr,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clCreateImage\n");
return tdispatch->clCreateImage(
            context,
            flags,
            image_format,
            image_desc,
            host_ptr,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_program CL_API_CALL clCreateProgramWithBuiltInKernels_wrap(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* kernel_names,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clCreateProgramWithBuiltInKernels\n");
return tdispatch->clCreateProgramWithBuiltInKernels(
            context,
            num_devices,
            device_list,
            kernel_names,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clCompileProgram_wrap(
    cl_program program,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    cl_uint num_input_headers,
    const cl_program* input_headers,
    const char** header_include_names,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data) CL_API_SUFFIX__VERSION_1_2
{
printf("clCompileProgram\n");
return tdispatch->clCompileProgram(
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
static cl_program CL_API_CALL clLinkProgram_wrap(
    cl_context context,
    cl_uint num_devices,
    const cl_device_id* device_list,
    const char* options,
    cl_uint num_input_programs,
    const cl_program* input_programs,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clLinkProgram\n");
return tdispatch->clLinkProgram(
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
static cl_int CL_API_CALL clUnloadPlatformCompiler_wrap(
    cl_platform_id platform) CL_API_SUFFIX__VERSION_1_2
{
printf("clUnloadPlatformCompiler\n");
return tdispatch->clUnloadPlatformCompiler(
            platform);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetKernelArgInfo_wrap(
    cl_kernel kernel,
    cl_uint arg_index,
    cl_kernel_arg_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clGetKernelArgInfo\n");
return tdispatch->clGetKernelArgInfo(
            kernel,
            arg_index,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueFillBuffer_wrap(
    cl_command_queue command_queue,
    cl_mem buffer,
    const void* pattern,
    size_t pattern_size,
    size_t offset,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
printf("clEnqueueFillBuffer\n");
return tdispatch->clEnqueueFillBuffer(
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
static cl_int CL_API_CALL clEnqueueFillImage_wrap(
    cl_command_queue command_queue,
    cl_mem image,
    const void* fill_color,
    const size_t* origin,
    const size_t* region,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
printf("clEnqueueFillImage\n");
return tdispatch->clEnqueueFillImage(
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
static cl_int CL_API_CALL clEnqueueMigrateMemObjects_wrap(
    cl_command_queue command_queue,
    cl_uint num_mem_objects,
    const cl_mem* mem_objects,
    cl_mem_migration_flags flags,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
printf("clEnqueueMigrateMemObjects\n");
return tdispatch->clEnqueueMigrateMemObjects(
            command_queue,
            num_mem_objects,
            mem_objects,
            flags,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueMarkerWithWaitList_wrap(
    cl_command_queue command_queue,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
printf("clEnqueueMarkerWithWaitList\n");
return tdispatch->clEnqueueMarkerWithWaitList(
            command_queue,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueBarrierWithWaitList_wrap(
    cl_command_queue command_queue,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
printf("clEnqueueBarrierWithWaitList\n");
return tdispatch->clEnqueueBarrierWithWaitList(
            command_queue,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

///////////////////////////////////////////////////////////////////////////////
static void* CL_API_CALL clGetExtensionFunctionAddressForPlatform_wrap(
    cl_platform_id platform,
    const char* func_name) CL_API_SUFFIX__VERSION_1_2
{
printf("clGetExtensionFunctionAddressForPlatform\n");
return tdispatch->clGetExtensionFunctionAddressForPlatform(
            platform,
            func_name);
}

///////////////////////////////////////////////////////////////////////////////
static cl_command_queue CL_API_CALL clCreateCommandQueueWithProperties_wrap(
    cl_context context,
    cl_device_id device,
    const cl_queue_properties* properties,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_2_0
{
printf("clCreateCommandQueueWithProperties\n");
return tdispatch->clCreateCommandQueueWithProperties(
            context,
            device,
            properties,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_mem CL_API_CALL clCreatePipe_wrap(
    cl_context context,
    cl_mem_flags flags,
    cl_uint pipe_packet_size,
    cl_uint pipe_max_packets,
    const cl_pipe_properties* properties,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_2_0
{
printf("clCreatePipe\n");
return tdispatch->clCreatePipe(
            context,
            flags,
            pipe_packet_size,
            pipe_max_packets,
            properties,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetPipeInfo_wrap(
    cl_mem pipe,
    cl_pipe_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_2_0
{
printf("clGetPipeInfo\n");
return tdispatch->clGetPipeInfo(
            pipe,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////
static void* CL_API_CALL clSVMAlloc_wrap(
    cl_context context,
    cl_svm_mem_flags flags,
    size_t size,
    cl_uint alignment) CL_API_SUFFIX__VERSION_2_0
{
printf("clSVMAlloc\n");
return tdispatch->clSVMAlloc(
            context,
            flags,
            size,
            alignment);
}

///////////////////////////////////////////////////////////////////////////////
static void CL_API_CALL clSVMFree_wrap(
    cl_context context,
    void* svm_pointer) CL_API_SUFFIX__VERSION_2_0
{
printf("clSVMFree\n");
tdispatch->clSVMFree(
            context,
            svm_pointer);
}

///////////////////////////////////////////////////////////////////////////////
static cl_sampler CL_API_CALL clCreateSamplerWithProperties_wrap(
    cl_context context,
    const cl_sampler_properties* sampler_properties,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_2_0
{
printf("clCreateSamplerWithProperties\n");
return tdispatch->clCreateSamplerWithProperties(
            context,
            sampler_properties,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clSetKernelArgSVMPointer_wrap(
    cl_kernel kernel,
    cl_uint arg_index,
    const void* arg_value) CL_API_SUFFIX__VERSION_2_0
{
printf("clSetKernelArgSVMPointer\n");
return tdispatch->clSetKernelArgSVMPointer(
            kernel,
            arg_index,
            arg_value);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clSetKernelExecInfo_wrap(
    cl_kernel kernel,
    cl_kernel_exec_info param_name,
    size_t param_value_size,
    const void* param_value) CL_API_SUFFIX__VERSION_2_0
{
printf("clSetKernelExecInfo\n");
return tdispatch->clSetKernelExecInfo(
            kernel,
            param_name,
            param_value_size,
            param_value);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clEnqueueSVMFree_wrap(
    cl_command_queue command_queue,
    cl_uint num_svm_pointers,
    void* svm_pointers[],
    void (CL_CALLBACK* pfn_free_func)(cl_command_queue queue, cl_uint num_svm_pointers, void* svm_pointers[], void* user_data),
    void* user_data,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_2_0
{
printf("clEnqueueSVMFree\n");
return tdispatch->clEnqueueSVMFree(
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
static cl_int CL_API_CALL clEnqueueSVMMemcpy_wrap(
    cl_command_queue command_queue,
    cl_bool blocking_copy,
    void* dst_ptr,
    const void* src_ptr,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_2_0
{
printf("clEnqueueSVMMemcpy\n");
return tdispatch->clEnqueueSVMMemcpy(
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
static cl_int CL_API_CALL clEnqueueSVMMemFill_wrap(
    cl_command_queue command_queue,
    void* svm_ptr,
    const void* pattern,
    size_t pattern_size,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_2_0
{
printf("clEnqueueSVMMemFill\n");
return tdispatch->clEnqueueSVMMemFill(
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
static cl_int CL_API_CALL clEnqueueSVMMap_wrap(
    cl_command_queue command_queue,
    cl_bool blocking_map,
    cl_map_flags flags,
    void* svm_ptr,
    size_t size,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_2_0
{
printf("clEnqueueSVMMap\n");
return tdispatch->clEnqueueSVMMap(
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
static cl_int CL_API_CALL clEnqueueSVMUnmap_wrap(
    cl_command_queue command_queue,
    void* svm_ptr,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_2_0
{
printf("clEnqueueSVMUnmap\n");
return tdispatch->clEnqueueSVMUnmap(
            command_queue,
            svm_ptr,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clSetDefaultDeviceCommandQueue_wrap(
    cl_context context,
    cl_device_id device,
    cl_command_queue command_queue) CL_API_SUFFIX__VERSION_2_1
{
printf("clSetDefaultDeviceCommandQueue\n");
return tdispatch->clSetDefaultDeviceCommandQueue(
            context,
            device,
            command_queue);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetDeviceAndHostTimer_wrap(
    cl_device_id device,
    cl_ulong* device_timestamp,
    cl_ulong* host_timestamp) CL_API_SUFFIX__VERSION_2_1
{
printf("clGetDeviceAndHostTimer\n");
return tdispatch->clGetDeviceAndHostTimer(
            device,
            device_timestamp,
            host_timestamp);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetHostTimer_wrap(
    cl_device_id device,
    cl_ulong* host_timestamp) CL_API_SUFFIX__VERSION_2_1
{
printf("clGetHostTimer\n");
return tdispatch->clGetHostTimer(
            device,
            host_timestamp);
}

///////////////////////////////////////////////////////////////////////////////
static cl_program CL_API_CALL clCreateProgramWithIL_wrap(
    cl_context context,
    const void* il,
    size_t length,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_2_1
{
printf("clCreateProgramWithIL\n");
return tdispatch->clCreateProgramWithIL(
            context,
            il,
            length,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_kernel CL_API_CALL clCloneKernel_wrap(
    cl_kernel source_kernel,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_2_1
{
printf("clCloneKernel\n");
return tdispatch->clCloneKernel(
            source_kernel,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clGetKernelSubGroupInfo_wrap(
    cl_kernel kernel,
    cl_device_id device,
    cl_kernel_sub_group_info param_name,
    size_t input_value_size,
    const void* input_value,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_2_1
{
printf("clGetKernelSubGroupInfo\n");
return tdispatch->clGetKernelSubGroupInfo(
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
static cl_int CL_API_CALL clEnqueueSVMMigrateMem_wrap(
    cl_command_queue command_queue,
    cl_uint num_svm_pointers,
    const void** svm_pointers,
    const size_t* sizes,
    cl_mem_migration_flags flags,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_2_1
{
printf("clEnqueueSVMMigrateMem\n");
return tdispatch->clEnqueueSVMMigrateMem(
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
static cl_int CL_API_CALL clSetProgramSpecializationConstant_wrap(
    cl_program program,
    cl_uint spec_id,
    size_t spec_size,
    const void* spec_value) CL_API_SUFFIX__VERSION_2_2
{
printf("clSetProgramSpecializationConstant\n");
return tdispatch->clSetProgramSpecializationConstant(
            program,
            spec_id,
            spec_size,
            spec_value);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clSetProgramReleaseCallback_wrap(
    cl_program program,
    void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data),
    void* user_data) CL_API_SUFFIX__VERSION_2_2_DEPRECATED
{
printf("clSetProgramReleaseCallback\n");
return tdispatch->clSetProgramReleaseCallback(
            program,
            pfn_notify,
            user_data);
}

///////////////////////////////////////////////////////////////////////////////
static cl_int CL_API_CALL clSetContextDestructorCallback_wrap(
    cl_context context,
    void (CL_CALLBACK* pfn_notify)(cl_context context, void* user_data),
    void* user_data) CL_API_SUFFIX__VERSION_3_0
{
printf("clSetContextDestructorCallback\n");
return tdispatch->clSetContextDestructorCallback(
            context,
            pfn_notify,
            user_data);
}

///////////////////////////////////////////////////////////////////////////////
static cl_mem CL_API_CALL clCreateBufferWithProperties_wrap(
    cl_context context,
    const cl_mem_properties* properties,
    cl_mem_flags flags,
    size_t size,
    void* host_ptr,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_3_0
{
printf("clCreateBufferWithProperties\n");
return tdispatch->clCreateBufferWithProperties(
            context,
            properties,
            flags,
            size,
            host_ptr,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////
static cl_mem CL_API_CALL clCreateImageWithProperties_wrap(
    cl_context context,
    const cl_mem_properties* properties,
    cl_mem_flags flags,
    const cl_image_format* image_format,
    const cl_image_desc* image_desc,
    void* host_ptr,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_3_0
{
printf("clCreateImageWithProperties\n");
return tdispatch->clCreateImageWithProperties(
            context,
            properties,
            flags,
            image_format,
            image_desc,
            host_ptr,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////

// cl_ext_device_fission
static cl_int CL_API_CALL clReleaseDeviceEXT_wrap(
    cl_device_id device) CL_API_SUFFIX__VERSION_1_1
{
printf("clReleaseDeviceEXT\n");
return tdispatch->clReleaseDeviceEXT(
            device);
}
static cl_int CL_API_CALL clRetainDeviceEXT_wrap(
    cl_device_id device) CL_API_SUFFIX__VERSION_1_1
{
printf("clRetainDeviceEXT\n");
return tdispatch->clRetainDeviceEXT(
            device);
}
static cl_int CL_API_CALL clCreateSubDevicesEXT_wrap(
    cl_device_id in_device,
    const cl_device_partition_property_ext* properties,
    cl_uint num_entries,
    cl_device_id* out_devices,
    cl_uint* num_devices) CL_API_SUFFIX__VERSION_1_1
{
printf("clCreateSubDevicesEXT\n");
return tdispatch->clCreateSubDevicesEXT(
            in_device,
            properties,
            num_entries,
            out_devices,
            num_devices);
}

///////////////////////////////////////////////////////////////////////////////

// cl_khr_d3d10_sharing

#if defined(_WIN32)
static cl_int CL_API_CALL clGetDeviceIDsFromD3D10KHR_wrap(
    cl_platform_id platform,
    cl_d3d10_device_source_khr d3d_device_source,
    void* d3d_object,
    cl_d3d10_device_set_khr d3d_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetDeviceIDsFromD3D10KHR\n");
return tdispatch->clGetDeviceIDsFromD3D10KHR(
            platform,
            d3d_device_source,
            d3d_object,
            d3d_device_set,
            num_entries,
            devices,
            num_devices);
}
static cl_mem CL_API_CALL clCreateFromD3D10BufferKHR_wrap(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Buffer* resource,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateFromD3D10BufferKHR\n");
return tdispatch->clCreateFromD3D10BufferKHR(
            context,
            flags,
            resource,
            errcode_ret);
}
static cl_mem CL_API_CALL clCreateFromD3D10Texture2DKHR_wrap(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Texture2D* resource,
    UINT subresource,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateFromD3D10Texture2DKHR\n");
return tdispatch->clCreateFromD3D10Texture2DKHR(
            context,
            flags,
            resource,
            subresource,
            errcode_ret);
}
static cl_mem CL_API_CALL clCreateFromD3D10Texture3DKHR_wrap(
    cl_context context,
    cl_mem_flags flags,
    ID3D10Texture3D* resource,
    UINT subresource,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateFromD3D10Texture3DKHR\n");
return tdispatch->clCreateFromD3D10Texture3DKHR(
            context,
            flags,
            resource,
            subresource,
            errcode_ret);
}
static cl_int CL_API_CALL clEnqueueAcquireD3D10ObjectsKHR_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueAcquireD3D10ObjectsKHR\n");
return tdispatch->clEnqueueAcquireD3D10ObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}
static cl_int CL_API_CALL clEnqueueReleaseD3D10ObjectsKHR_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueReleaseD3D10ObjectsKHR\n");
return tdispatch->clEnqueueReleaseD3D10ObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

#endif // defined(_WIN32)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_d3d11_sharing

#if defined(_WIN32)
static cl_int CL_API_CALL clGetDeviceIDsFromD3D11KHR_wrap(
    cl_platform_id platform,
    cl_d3d11_device_source_khr d3d_device_source,
    void* d3d_object,
    cl_d3d11_device_set_khr d3d_device_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices) CL_API_SUFFIX__VERSION_1_2
{
printf("clGetDeviceIDsFromD3D11KHR\n");
return tdispatch->clGetDeviceIDsFromD3D11KHR(
            platform,
            d3d_device_source,
            d3d_object,
            d3d_device_set,
            num_entries,
            devices,
            num_devices);
}
static cl_mem CL_API_CALL clCreateFromD3D11BufferKHR_wrap(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Buffer* resource,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clCreateFromD3D11BufferKHR\n");
return tdispatch->clCreateFromD3D11BufferKHR(
            context,
            flags,
            resource,
            errcode_ret);
}
static cl_mem CL_API_CALL clCreateFromD3D11Texture2DKHR_wrap(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Texture2D* resource,
    UINT subresource,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clCreateFromD3D11Texture2DKHR\n");
return tdispatch->clCreateFromD3D11Texture2DKHR(
            context,
            flags,
            resource,
            subresource,
            errcode_ret);
}
static cl_mem CL_API_CALL clCreateFromD3D11Texture3DKHR_wrap(
    cl_context context,
    cl_mem_flags flags,
    ID3D11Texture3D* resource,
    UINT subresource,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clCreateFromD3D11Texture3DKHR\n");
return tdispatch->clCreateFromD3D11Texture3DKHR(
            context,
            flags,
            resource,
            subresource,
            errcode_ret);
}
static cl_int CL_API_CALL clEnqueueAcquireD3D11ObjectsKHR_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
printf("clEnqueueAcquireD3D11ObjectsKHR\n");
return tdispatch->clEnqueueAcquireD3D11ObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}
static cl_int CL_API_CALL clEnqueueReleaseD3D11ObjectsKHR_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
printf("clEnqueueReleaseD3D11ObjectsKHR\n");
return tdispatch->clEnqueueReleaseD3D11ObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

#endif // defined(_WIN32)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_dx9_media_sharing

#if defined(_WIN32)
static cl_int CL_API_CALL clGetDeviceIDsFromDX9MediaAdapterKHR_wrap(
    cl_platform_id platform,
    cl_uint num_media_adapters,
    cl_dx9_media_adapter_type_khr* media_adapter_type,
    void* media_adapters,
    cl_dx9_media_adapter_set_khr media_adapter_set,
    cl_uint num_entries,
    cl_device_id* devices,
    cl_uint* num_devices) CL_API_SUFFIX__VERSION_1_2
{
printf("clGetDeviceIDsFromDX9MediaAdapterKHR\n");
return tdispatch->clGetDeviceIDsFromDX9MediaAdapterKHR(
            platform,
            num_media_adapters,
            media_adapter_type,
            media_adapters,
            media_adapter_set,
            num_entries,
            devices,
            num_devices);
}
static cl_mem CL_API_CALL clCreateFromDX9MediaSurfaceKHR_wrap(
    cl_context context,
    cl_mem_flags flags,
    cl_dx9_media_adapter_type_khr adapter_type,
    void* surface_info,
    cl_uint plane,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clCreateFromDX9MediaSurfaceKHR\n");
return tdispatch->clCreateFromDX9MediaSurfaceKHR(
            context,
            flags,
            adapter_type,
            surface_info,
            plane,
            errcode_ret);
}
static cl_int CL_API_CALL clEnqueueAcquireDX9MediaSurfacesKHR_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
printf("clEnqueueAcquireDX9MediaSurfacesKHR\n");
return tdispatch->clEnqueueAcquireDX9MediaSurfacesKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}
static cl_int CL_API_CALL clEnqueueReleaseDX9MediaSurfacesKHR_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_2
{
printf("clEnqueueReleaseDX9MediaSurfacesKHR\n");
return tdispatch->clEnqueueReleaseDX9MediaSurfacesKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

#endif // defined(_WIN32)

///////////////////////////////////////////////////////////////////////////////

// cl_khr_egl_event
static cl_event CL_API_CALL clCreateEventFromEGLSyncKHR_wrap(
    cl_context context,
    CLeglSyncKHR sync,
    CLeglDisplayKHR display,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateEventFromEGLSyncKHR\n");
return tdispatch->clCreateEventFromEGLSyncKHR(
            context,
            sync,
            display,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////

// cl_khr_egl_image
static cl_mem CL_API_CALL clCreateFromEGLImageKHR_wrap(
    cl_context context,
    CLeglDisplayKHR egldisplay,
    CLeglImageKHR eglimage,
    cl_mem_flags flags,
    const cl_egl_image_properties_khr* properties,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateFromEGLImageKHR\n");
return tdispatch->clCreateFromEGLImageKHR(
            context,
            egldisplay,
            eglimage,
            flags,
            properties,
            errcode_ret);
}
static cl_int CL_API_CALL clEnqueueAcquireEGLObjectsKHR_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueAcquireEGLObjectsKHR\n");
return tdispatch->clEnqueueAcquireEGLObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}
static cl_int CL_API_CALL clEnqueueReleaseEGLObjectsKHR_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueReleaseEGLObjectsKHR\n");
return tdispatch->clEnqueueReleaseEGLObjectsKHR(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}

///////////////////////////////////////////////////////////////////////////////

// cl_khr_gl_event
static cl_event CL_API_CALL clCreateEventFromGLsyncKHR_wrap(
    cl_context context,
    cl_GLsync sync,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1
{
printf("clCreateEventFromGLsyncKHR\n");
return tdispatch->clCreateEventFromGLsyncKHR(
            context,
            sync,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////

// cl_khr_gl_sharing
static cl_int CL_API_CALL clGetGLContextInfoKHR_wrap(
    const cl_context_properties* properties,
    cl_gl_context_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetGLContextInfoKHR\n");
return tdispatch->clGetGLContextInfoKHR(
            properties,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}
static cl_mem CL_API_CALL clCreateFromGLBuffer_wrap(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint bufobj,
    int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateFromGLBuffer\n");
return tdispatch->clCreateFromGLBuffer(
            context,
            flags,
            bufobj,
            errcode_ret);
}
static cl_mem CL_API_CALL clCreateFromGLTexture_wrap(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_2
{
printf("clCreateFromGLTexture\n");
return tdispatch->clCreateFromGLTexture(
            context,
            flags,
            target,
            miplevel,
            texture,
            errcode_ret);
}
static cl_mem CL_API_CALL clCreateFromGLRenderbuffer_wrap(
    cl_context context,
    cl_mem_flags flags,
    cl_GLuint renderbuffer,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clCreateFromGLRenderbuffer\n");
return tdispatch->clCreateFromGLRenderbuffer(
            context,
            flags,
            renderbuffer,
            errcode_ret);
}
static cl_int CL_API_CALL clGetGLObjectInfo_wrap(
    cl_mem memobj,
    cl_gl_object_type* gl_object_type,
    cl_GLuint* gl_object_name) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetGLObjectInfo\n");
return tdispatch->clGetGLObjectInfo(
            memobj,
            gl_object_type,
            gl_object_name);
}
static cl_int CL_API_CALL clGetGLTextureInfo_wrap(
    cl_mem memobj,
    cl_gl_texture_info param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_1_0
{
printf("clGetGLTextureInfo\n");
return tdispatch->clGetGLTextureInfo(
            memobj,
            param_name,
            param_value_size,
            param_value,
            param_value_size_ret);
}
static cl_int CL_API_CALL clEnqueueAcquireGLObjects_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueAcquireGLObjects\n");
return tdispatch->clEnqueueAcquireGLObjects(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}
static cl_int CL_API_CALL clEnqueueReleaseGLObjects_wrap(
    cl_command_queue command_queue,
    cl_uint num_objects,
    const cl_mem* mem_objects,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event) CL_API_SUFFIX__VERSION_1_0
{
printf("clEnqueueReleaseGLObjects\n");
return tdispatch->clEnqueueReleaseGLObjects(
            command_queue,
            num_objects,
            mem_objects,
            num_events_in_wait_list,
            event_wait_list,
            event);
}
static cl_mem CL_API_CALL clCreateFromGLTexture2D_wrap(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1_DEPRECATED
{
printf("clCreateFromGLTexture2D\n");
return tdispatch->clCreateFromGLTexture2D(
            context,
            flags,
            target,
            miplevel,
            texture,
            errcode_ret);
}
static cl_mem CL_API_CALL clCreateFromGLTexture3D_wrap(
    cl_context context,
    cl_mem_flags flags,
    cl_GLenum target,
    cl_GLint miplevel,
    cl_GLuint texture,
    cl_int* errcode_ret) CL_API_SUFFIX__VERSION_1_1_DEPRECATED
{
printf("clCreateFromGLTexture3D\n");
return tdispatch->clCreateFromGLTexture3D(
            context,
            flags,
            target,
            miplevel,
            texture,
            errcode_ret);
}

///////////////////////////////////////////////////////////////////////////////

// cl_khr_subgroups
static cl_int CL_API_CALL clGetKernelSubGroupInfoKHR_wrap(
    cl_kernel in_kernel,
    cl_device_id in_device,
    cl_kernel_sub_group_info param_name,
    size_t input_value_size,
    const void* input_value,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret) CL_API_SUFFIX__VERSION_2_0_DEPRECATED
{
printf("clGetKernelSubGroupInfoKHR\n");
return tdispatch->clGetKernelSubGroupInfoKHR(
            in_kernel,
            in_device,
            param_name,
            input_value_size,
            input_value,
            param_value_size,
            param_value,
            param_value_size_ret);
}

///////////////////////////////////////////////////////////////////////////////

void _init_dispatch(void) {
    dispatch.clGetPlatformIDs = &clGetPlatformIDs_wrap;
    dispatch.clGetPlatformInfo = &clGetPlatformInfo_wrap;
    dispatch.clGetDeviceIDs = &clGetDeviceIDs_wrap;
    dispatch.clGetDeviceInfo = &clGetDeviceInfo_wrap;
    dispatch.clCreateContext = &clCreateContext_wrap;
    dispatch.clCreateContextFromType = &clCreateContextFromType_wrap;
    dispatch.clRetainContext = &clRetainContext_wrap;
    dispatch.clReleaseContext = &clReleaseContext_wrap;
    dispatch.clGetContextInfo = &clGetContextInfo_wrap;
    dispatch.clCreateCommandQueue = &clCreateCommandQueue_wrap;
    dispatch.clRetainCommandQueue = &clRetainCommandQueue_wrap;
    dispatch.clReleaseCommandQueue = &clReleaseCommandQueue_wrap;
    dispatch.clGetCommandQueueInfo = &clGetCommandQueueInfo_wrap;
    dispatch.clSetCommandQueueProperty = &clSetCommandQueueProperty_wrap;
    dispatch.clCreateBuffer = &clCreateBuffer_wrap;
    dispatch.clCreateImage2D = &clCreateImage2D_wrap;
    dispatch.clCreateImage3D = &clCreateImage3D_wrap;
    dispatch.clRetainMemObject = &clRetainMemObject_wrap;
    dispatch.clReleaseMemObject = &clReleaseMemObject_wrap;
    dispatch.clGetSupportedImageFormats = &clGetSupportedImageFormats_wrap;
    dispatch.clGetMemObjectInfo = &clGetMemObjectInfo_wrap;
    dispatch.clGetImageInfo = &clGetImageInfo_wrap;
    dispatch.clCreateSampler = &clCreateSampler_wrap;
    dispatch.clRetainSampler = &clRetainSampler_wrap;
    dispatch.clReleaseSampler = &clReleaseSampler_wrap;
    dispatch.clGetSamplerInfo = &clGetSamplerInfo_wrap;
    dispatch.clCreateProgramWithSource = &clCreateProgramWithSource_wrap;
    dispatch.clCreateProgramWithBinary = &clCreateProgramWithBinary_wrap;
    dispatch.clRetainProgram = &clRetainProgram_wrap;
    dispatch.clReleaseProgram = &clReleaseProgram_wrap;
    dispatch.clBuildProgram = &clBuildProgram_wrap;
    dispatch.clUnloadCompiler = &clUnloadCompiler_wrap;
    dispatch.clGetProgramInfo = &clGetProgramInfo_wrap;
    dispatch.clGetProgramBuildInfo = &clGetProgramBuildInfo_wrap;
    dispatch.clCreateKernel = &clCreateKernel_wrap;
    dispatch.clCreateKernelsInProgram = &clCreateKernelsInProgram_wrap;
    dispatch.clRetainKernel = &clRetainKernel_wrap;
    dispatch.clReleaseKernel = &clReleaseKernel_wrap;
    dispatch.clSetKernelArg = &clSetKernelArg_wrap;
    dispatch.clGetKernelInfo = &clGetKernelInfo_wrap;
    dispatch.clGetKernelWorkGroupInfo = &clGetKernelWorkGroupInfo_wrap;
    dispatch.clWaitForEvents = &clWaitForEvents_wrap;
    dispatch.clGetEventInfo = &clGetEventInfo_wrap;
    dispatch.clRetainEvent = &clRetainEvent_wrap;
    dispatch.clReleaseEvent = &clReleaseEvent_wrap;
    dispatch.clGetEventProfilingInfo = &clGetEventProfilingInfo_wrap;
    dispatch.clFlush = &clFlush_wrap;
    dispatch.clFinish = &clFinish_wrap;
    dispatch.clEnqueueReadBuffer = &clEnqueueReadBuffer_wrap;
    dispatch.clEnqueueWriteBuffer = &clEnqueueWriteBuffer_wrap;
    dispatch.clEnqueueCopyBuffer = &clEnqueueCopyBuffer_wrap;
    dispatch.clEnqueueReadImage = &clEnqueueReadImage_wrap;
    dispatch.clEnqueueWriteImage = &clEnqueueWriteImage_wrap;
    dispatch.clEnqueueCopyImage = &clEnqueueCopyImage_wrap;
    dispatch.clEnqueueCopyImageToBuffer = &clEnqueueCopyImageToBuffer_wrap;
    dispatch.clEnqueueCopyBufferToImage = &clEnqueueCopyBufferToImage_wrap;
    dispatch.clEnqueueMapBuffer = &clEnqueueMapBuffer_wrap;
    dispatch.clEnqueueMapImage = &clEnqueueMapImage_wrap;
    dispatch.clEnqueueUnmapMemObject = &clEnqueueUnmapMemObject_wrap;
    dispatch.clEnqueueNDRangeKernel = &clEnqueueNDRangeKernel_wrap;
    dispatch.clEnqueueTask = &clEnqueueTask_wrap;
    dispatch.clEnqueueNativeKernel = &clEnqueueNativeKernel_wrap;
    dispatch.clEnqueueMarker = &clEnqueueMarker_wrap;
    dispatch.clEnqueueWaitForEvents = &clEnqueueWaitForEvents_wrap;
    dispatch.clEnqueueBarrier = &clEnqueueBarrier_wrap;
    dispatch.clGetExtensionFunctionAddress = &clGetExtensionFunctionAddress_wrap;
    dispatch.clCreateFromGLBuffer = &clCreateFromGLBuffer_wrap;
    dispatch.clCreateFromGLTexture2D = &clCreateFromGLTexture2D_wrap;
    dispatch.clCreateFromGLTexture3D = &clCreateFromGLTexture3D_wrap;
    dispatch.clCreateFromGLRenderbuffer = &clCreateFromGLRenderbuffer_wrap;
    dispatch.clGetGLObjectInfo = &clGetGLObjectInfo_wrap;
    dispatch.clGetGLTextureInfo = &clGetGLTextureInfo_wrap;
    dispatch.clEnqueueAcquireGLObjects = &clEnqueueAcquireGLObjects_wrap;
    dispatch.clEnqueueReleaseGLObjects = &clEnqueueReleaseGLObjects_wrap;
    dispatch.clGetGLContextInfoKHR = &clGetGLContextInfoKHR_wrap;

  /* cl_khr_d3d10_sharing */
#if defined(_WIN32)
    dispatch.clGetDeviceIDsFromD3D10KHR = &clGetDeviceIDsFromD3D10KHR_wrap;
    dispatch.clCreateFromD3D10BufferKHR = &clCreateFromD3D10BufferKHR_wrap;
    dispatch.clCreateFromD3D10Texture2DKHR = &clCreateFromD3D10Texture2DKHR_wrap;
    dispatch.clCreateFromD3D10Texture3DKHR = &clCreateFromD3D10Texture3DKHR_wrap;
    dispatch.clEnqueueAcquireD3D10ObjectsKHR = &clEnqueueAcquireD3D10ObjectsKHR_wrap;
    dispatch.clEnqueueReleaseD3D10ObjectsKHR = &clEnqueueReleaseD3D10ObjectsKHR_wrap;
#else
    dispatch.clGetDeviceIDsFromD3D10KHR = NULL;
    dispatch.clCreateFromD3D10BufferKHR = NULL;
    dispatch.clCreateFromD3D10Texture2DKHR = NULL;
    dispatch.clCreateFromD3D10Texture3DKHR = NULL;
    dispatch.clEnqueueAcquireD3D10ObjectsKHR = NULL;
    dispatch.clEnqueueReleaseD3D10ObjectsKHR = NULL;
#endif

  /* OpenCL 1.1 */
    dispatch.clSetEventCallback = &clSetEventCallback_wrap;
    dispatch.clCreateSubBuffer = &clCreateSubBuffer_wrap;
    dispatch.clSetMemObjectDestructorCallback = &clSetMemObjectDestructorCallback_wrap;
    dispatch.clCreateUserEvent = &clCreateUserEvent_wrap;
    dispatch.clSetUserEventStatus = &clSetUserEventStatus_wrap;
    dispatch.clEnqueueReadBufferRect = &clEnqueueReadBufferRect_wrap;
    dispatch.clEnqueueWriteBufferRect = &clEnqueueWriteBufferRect_wrap;
    dispatch.clEnqueueCopyBufferRect = &clEnqueueCopyBufferRect_wrap;

  /* cl_ext_device_fission */
    dispatch.clCreateSubDevicesEXT = &clCreateSubDevicesEXT_wrap;
    dispatch.clRetainDeviceEXT = &clRetainDeviceEXT_wrap;
    dispatch.clReleaseDeviceEXT = &clReleaseDeviceEXT_wrap;

  /* cl_khr_gl_event */
    dispatch.clCreateEventFromGLsyncKHR = &clCreateEventFromGLsyncKHR_wrap;

  /* OpenCL 1.2 */
    dispatch.clCreateSubDevices = &clCreateSubDevices_wrap;
    dispatch.clRetainDevice = &clRetainDevice_wrap;
    dispatch.clReleaseDevice = &clReleaseDevice_wrap;
    dispatch.clCreateImage = &clCreateImage_wrap;
    dispatch.clCreateProgramWithBuiltInKernels = &clCreateProgramWithBuiltInKernels_wrap;
    dispatch.clCompileProgram = &clCompileProgram_wrap;
    dispatch.clLinkProgram = &clLinkProgram_wrap;
    dispatch.clUnloadPlatformCompiler = &clUnloadPlatformCompiler_wrap;
    dispatch.clGetKernelArgInfo = &clGetKernelArgInfo_wrap;
    dispatch.clEnqueueFillBuffer = &clEnqueueFillBuffer_wrap;
    dispatch.clEnqueueFillImage = &clEnqueueFillImage_wrap;
    dispatch.clEnqueueMigrateMemObjects = &clEnqueueMigrateMemObjects_wrap;
    dispatch.clEnqueueMarkerWithWaitList = &clEnqueueMarkerWithWaitList_wrap;
    dispatch.clEnqueueBarrierWithWaitList = &clEnqueueBarrierWithWaitList_wrap;
    dispatch.clGetExtensionFunctionAddressForPlatform = &clGetExtensionFunctionAddressForPlatform_wrap;
    dispatch.clCreateFromGLTexture = &clCreateFromGLTexture_wrap;

  /* cl_khr_d3d11_sharing */
#if defined(_WIN32)
    dispatch.clGetDeviceIDsFromD3D11KHR = &clGetDeviceIDsFromD3D11KHR_wrap;
    dispatch.clCreateFromD3D11BufferKHR = &clCreateFromD3D11BufferKHR_wrap;
    dispatch.clCreateFromD3D11Texture2DKHR = &clCreateFromD3D11Texture2DKHR_wrap;
    dispatch.clCreateFromD3D11Texture3DKHR = &clCreateFromD3D11Texture3DKHR_wrap;
    dispatch.clCreateFromDX9MediaSurfaceKHR = &clCreateFromDX9MediaSurfaceKHR_wrap;
    dispatch.clEnqueueAcquireD3D11ObjectsKHR = &clEnqueueAcquireD3D11ObjectsKHR_wrap;
    dispatch.clEnqueueReleaseD3D11ObjectsKHR = &clEnqueueReleaseD3D11ObjectsKHR_wrap;
#else
    dispatch.clGetDeviceIDsFromD3D11KHR = NULL;
    dispatch.clCreateFromD3D11BufferKHR = NULL;
    dispatch.clCreateFromD3D11Texture2DKHR = NULL;
    dispatch.clCreateFromD3D11Texture3DKHR = NULL;
    dispatch.clCreateFromDX9MediaSurfaceKHR = NULL;
    dispatch.clEnqueueAcquireD3D11ObjectsKHR = NULL;
    dispatch.clEnqueueReleaseD3D11ObjectsKHR = NULL;
#endif

  /* cl_khr_dx9_media_sharing */
#if defined(_WIN32)
    dispatch.clGetDeviceIDsFromDX9MediaAdapterKHR = &clGetDeviceIDsFromDX9MediaAdapterKHR_wrap;
    dispatch.clEnqueueAcquireDX9MediaSurfacesKHR = &clEnqueueAcquireDX9MediaSurfacesKHR_wrap;
    dispatch.clEnqueueReleaseDX9MediaSurfacesKHR = &clEnqueueReleaseDX9MediaSurfacesKHR_wrap;
#else
    dispatch.clGetDeviceIDsFromDX9MediaAdapterKHR = NULL;
    dispatch.clEnqueueAcquireDX9MediaSurfacesKHR = NULL;
    dispatch.clEnqueueReleaseDX9MediaSurfacesKHR = NULL;
#endif

  /* cl_khr_egl_image */
    dispatch.clCreateFromEGLImageKHR = &clCreateFromEGLImageKHR_wrap;
    dispatch.clEnqueueAcquireEGLObjectsKHR = &clEnqueueAcquireEGLObjectsKHR_wrap;
    dispatch.clEnqueueReleaseEGLObjectsKHR = &clEnqueueReleaseEGLObjectsKHR_wrap;

  /* cl_khr_egl_event */
    dispatch.clCreateEventFromEGLSyncKHR = &clCreateEventFromEGLSyncKHR_wrap;

  /* OpenCL 2.0 */
    dispatch.clCreateCommandQueueWithProperties = &clCreateCommandQueueWithProperties_wrap;
    dispatch.clCreatePipe = &clCreatePipe_wrap;
    dispatch.clGetPipeInfo = &clGetPipeInfo_wrap;
    dispatch.clSVMAlloc = &clSVMAlloc_wrap;
    dispatch.clSVMFree = &clSVMFree_wrap;
    dispatch.clEnqueueSVMFree = &clEnqueueSVMFree_wrap;
    dispatch.clEnqueueSVMMemcpy = &clEnqueueSVMMemcpy_wrap;
    dispatch.clEnqueueSVMMemFill = &clEnqueueSVMMemFill_wrap;
    dispatch.clEnqueueSVMMap = &clEnqueueSVMMap_wrap;
    dispatch.clEnqueueSVMUnmap = &clEnqueueSVMUnmap_wrap;
    dispatch.clCreateSamplerWithProperties = &clCreateSamplerWithProperties_wrap;
    dispatch.clSetKernelArgSVMPointer = &clSetKernelArgSVMPointer_wrap;
    dispatch.clSetKernelExecInfo = &clSetKernelExecInfo_wrap;

  /* cl_khr_sub_groups */
    dispatch.clGetKernelSubGroupInfoKHR = &clGetKernelSubGroupInfoKHR_wrap;

  /* OpenCL 2.1 */
    dispatch.clCloneKernel = &clCloneKernel_wrap;
    dispatch.clCreateProgramWithIL = &clCreateProgramWithIL_wrap;
    dispatch.clEnqueueSVMMigrateMem = &clEnqueueSVMMigrateMem_wrap;
    dispatch.clGetDeviceAndHostTimer = &clGetDeviceAndHostTimer_wrap;
    dispatch.clGetHostTimer = &clGetHostTimer_wrap;
    dispatch.clGetKernelSubGroupInfo = &clGetKernelSubGroupInfo_wrap;
    dispatch.clSetDefaultDeviceCommandQueue = &clSetDefaultDeviceCommandQueue_wrap;

  /* OpenCL 2.2 */
    dispatch.clSetProgramReleaseCallback = &clSetProgramReleaseCallback_wrap;
    dispatch.clSetProgramSpecializationConstant = &clSetProgramSpecializationConstant_wrap;

  /* OpenCL 3.0 */
    dispatch.clCreateBufferWithProperties = &clCreateBufferWithProperties_wrap;
    dispatch.clCreateImageWithProperties = &clCreateImageWithProperties_wrap;
    dispatch.clSetContextDestructorCallback = &clSetContextDestructorCallback_wrap;
}
