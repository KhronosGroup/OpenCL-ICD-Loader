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
%for apis in coreapis.values():
%for api in apis:
static ${api.RetType} CL_API_CALL ${api.Name + "_wrap"}(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd}) ${api.Suffix}
%  endif
%endfor
{
printf("${api.Name}\n");
%  if api.Name == "clSVMFree":
tdispatch->${api.Name}(
%  else:
return tdispatch->${api.Name}(
%  endif
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
            ${param.Name},
%  else:
            ${param.Name});
%  endif
%endfor
}

///////////////////////////////////////////////////////////////////////////////
%endfor
%endfor
<%
icdextensions = [
    'cl_ext_device_fission',
    'cl_khr_d3d10_sharing',
    'cl_khr_d3d11_sharing',
    'cl_khr_dx9_media_sharing',
    'cl_khr_egl_event',
    'cl_khr_egl_image',
    'cl_khr_gl_event',
    'cl_khr_gl_sharing',
    'cl_khr_subgroups'
    ]
win32extensions = {
    'cl_khr_d3d10_sharing',
    'cl_khr_d3d11_sharing',
    'cl_khr_dx9_media_sharing',
    }
%>
%for extension in icdextensions:
<%
    apis = extapis[extension]
%>// ${extension}
%if extension in win32extensions:

#if defined(_WIN32)
%endif
%for api in apis:
static ${api.RetType} CL_API_CALL ${api.Name + "_wrap"}(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd}) ${api.Suffix}
%  endif
%endfor
{
printf("${api.Name}\n");
return tdispatch->${api.Name}(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
            ${param.Name},
%  else:
            ${param.Name});
%  endif
%endfor
}
%endfor

%if extension in win32extensions:
#endif // defined(_WIN32)

%endif
///////////////////////////////////////////////////////////////////////////////

%endfor
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
