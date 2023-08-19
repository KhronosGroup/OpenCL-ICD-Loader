<%
# APIs to skip - they need to be done "manually":
apiskip = {
    'clGetPlatformIDs',                         # to query platforms
    'clGetExtensionFunctionAddress',            # to return ICD-aware extensions
    'clGetExtensionFunctionAddressForPlatform', # to return ICD-aware extensions
    }

apiinit = {
    'clCreateContextFromType',
    'clGetGLContextInfoKHR',
    }
# Handles, and mappings to errors when handles are invalid:
apihandles = {
    'cl_command_queue'  : 'CL_INVALID_COMMAND_QUEUE',
    'cl_context'        : 'CL_INVALID_CONTEXT',
    'cl_device_id'      : 'CL_INVALID_DEVICE',
    'cl_event'          : 'CL_INVALID_EVENT',
    'cl_kernel'         : 'CL_INVALID_KERNEL',
    'cl_mem'            : 'CL_INVALID_MEM_OBJECT',
    'cl_platform_id'    : 'CL_INVALID_PLATFORM',
    'cl_program'        : 'CL_INVALID_PROGRAM',
    'cl_sampler'        : 'CL_INVALID_SAMPLER',
    }
%>/*
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

%for apis in coreapis.values():
%for api in apis:
///////////////////////////////////////////////////////////////////////////////
%if not api.Name in apiskip:
<%
      handle = api.Params[0]
      if handle.Type in apihandles:
          invalid = apihandles[handle.Type]
      else:
          invalid = 'NULL'
%>
%for disp in [0, 1]:
%  if disp == 1:
#if defined(CL_ENABLE_LAYERS)
%  endif
${("CL_API_ENTRY", "static")[disp]} ${api.RetType} CL_API_CALL ${api.Name + ("", "_disp")[disp]}(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd})
%  endif
%endfor
{
%if api.Name in apiinit:
    khrIcdInitialize();
%endif
%if disp == 0:
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
%  if api.Name == "clSVMFree":
    {
        khrFirstLayer->dispatch.${api.Name}(
%  else:
        return khrFirstLayer->dispatch.${api.Name}(
%  endif
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
            ${param.Name},
%  else:
            ${param.Name});
%  endif
%endfor
%  if api.Name == "clSVMFree":
    }
    else
%  endif
#endif // defined(CL_ENABLE_LAYERS)
%endif
%if api.RetType in apihandles or api.RetType == "void*":
## clCreateContext is a special case, since it calls through
## the dispatch table via the first "device":
%  if api.Name == "clCreateContext":
    if (${api.Params[1].Name} == 0 || ${api.Params[2].Name} == NULL) {
        KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(NULL, CL_INVALID_VALUE);
    }
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(${api.Params[2].Name}[0], CL_INVALID_DEVICE);
## clCreateContextFromType is a special case, since it calls
## through a platform passed via properties:
%  elif api.Name == "clCreateContextFromType":
    cl_platform_id platform = NULL;
    khrIcdContextPropertiesGetPlatform(properties, &platform);
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(platform, CL_INVALID_PLATFORM);
## These APIs are special cases because they return a void*, but
## do not nave an errcode_ret:
%  elif api.Name == "clSVMAlloc" or api.Name == "clGetExtensionFunctionAddressForPlatform":
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(${handle.Name}, NULL);
%  else:
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(${handle.Name}, ${invalid});
%  endif
%elif api.Name == "clSVMFree":
## clSVMFree has no return value or errcode_ret:
    if (${handle.Name} != NULL)
## clWaitForEvents is a special case, since it calls through
## the dispatch table via the first "event":
%elif api.Name == "clWaitForEvents":
    if (${api.Params[0].Name} == 0 || ${api.Params[1].Name} == NULL) {
        return CL_INVALID_VALUE;
    }
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(${api.Params[1].Name}[0], CL_INVALID_EVENT);
%elif api.Name == "clUnloadCompiler":
    // Nothing!
%else:
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(${handle.Name}, ${invalid});
%endif
%if api.Name == "clCreateContext":
    return ${api.Params[2].Name}[0]->dispatch->${api.Name}(
%elif api.Name == "clWaitForEvents":
    return ${api.Params[1].Name}[0]->dispatch->${api.Name}(
%elif api.Name == "clCreateContextFromType":
    return platform->dispatch->${api.Name}(
%elif api.Name == "clSVMFree":
    ${handle.Name}->dispatch->${api.Name}(
%elif api.Name == "clUnloadCompiler":
    return CL_SUCCESS;
%else:
    return ${handle.Name}->dispatch->${api.Name}(
%endif:
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
        ${param.Name},
%  elif param.Name: # for clUnloadCompiler
        ${param.Name});
%  endif
%endfor
}
%  if disp == 1:
#endif // defined(CL_ENABLE_LAYERS)
%  endif

%endfor
#if defined(CL_ENABLE_LAYERS)
static ${api.RetType} CL_API_CALL ${api.Name}_shutdown(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd})
%  endif
%endfor
{
%if api.Name == "clUnloadCompiler" or api.Name == "clSVMFree":
    // Nothing!
%elif api.Name == "clSVMAlloc" or api.Name == "clGetExtensionFunctionAddressForPlatform":
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(NULL, NULL);
%elif api.RetType in apihandles or api.RetType == "void*":
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(NULL, CL_INVALID_OPERATION);
%else:
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(NULL, CL_INVALID_OPERATION);
%endif
}
#endif // defined(CL_ENABLE_LAYERS)

%else:

#if defined(CL_ENABLE_LAYERS)
extern ${api.RetType} CL_API_CALL ${api.Name + "_disp"}(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd}) ${api.Suffix};
%  endif
%endfor
#endif // defined(CL_ENABLE_LAYERS)

%endif
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
%>
%if extension in win32extensions:
#if defined(_WIN32)

%endif
%for api in apis:
///////////////////////////////////////////////////////////////////////////////
// ${extension}
<%
      handle = api.Params[0]
      if handle.Type in apihandles:
          invalid = apihandles[handle.Type]
      else:
          invalid = 'NULL'
%>
%for disp in [0, 1]:
%  if disp == 1:

#if defined(CL_ENABLE_LAYERS)
%  endif
${("CL_API_ENTRY", "static")[disp]} ${api.RetType} CL_API_CALL ${api.Name + ("", "_disp")[disp]}(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd})
%  endif
%endfor
{
%if disp == 0:
#if defined(CL_ENABLE_LAYERS)
    if (khrFirstLayer)
        return khrFirstLayer->dispatch.${api.Name}(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
            ${param.Name},
%  else:
            ${param.Name});
%  endif
%endfor
#endif // defined(CL_ENABLE_LAYERS)
%endif
%if api.RetType in apihandles or api.RetType == "void*":
%  if False:
    // api.Name == "clXXX":  # There are currently no API special cases here.
%  else:
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(${handle.Name}, ${invalid});
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(${handle.Name}->dispatch->${api.Name});
% endif
%else:
%  if api.Name == "clGetGLContextInfoKHR":
    cl_platform_id platform = NULL;
    khrIcdContextPropertiesGetPlatform(properties, &platform);
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(platform->dispatch->${api.Name});
%  else:
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(${handle.Name}, ${invalid});
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(${handle.Name}->dispatch->${api.Name});
%  endif
%endif
%if api.Name == "clGetGLContextInfoKHR":
    return platform->dispatch->${api.Name}(
%else:
    return ${handle.Name}->dispatch->${api.Name}(
%endif
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
        ${param.Name},
%  elif param.Name: # for clUnloadCompiler
        ${param.Name});
%  endif
%endfor
}
%  if disp == 1:
#endif // defined(CL_ENABLE_LAYERS)

%  endif
%endfor
%endfor
%if extension in win32extensions:
#endif // defined(_WIN32)
%endif
%endfor
///////////////////////////////////////////////////////////////////////////////

#if defined(CL_ENABLE_LAYERS)

struct _cl_icd_dispatch khrActualDispatch = {
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
    &clSetContextDestructorCallback_disp,
};

struct _cl_icd_dispatch khrShutdownDispatch = {
    &clGetPlatformIDs_shutdown,
    &clGetPlatformInfo_shutdown,
    &clGetDeviceIDs_shutdown,
    &clGetDeviceInfo_shutdown,
    &clCreateContext_shutdown,
    &clCreateContextFromType_shutdown,
    &clRetainContext_shutdown,
    &clReleaseContext_shutdown,
    &clGetContextInfo_shutdown,
    &clCreateCommandQueue_shutdown,
    &clRetainCommandQueue_shutdown,
    &clReleaseCommandQueue_shutdown,
    &clGetCommandQueueInfo_shutdown,
    &clSetCommandQueueProperty_shutdown,
    &clCreateBuffer_shutdown,
    &clCreateImage2D_shutdown,
    &clCreateImage3D_shutdown,
    &clRetainMemObject_shutdown,
    &clReleaseMemObject_shutdown,
    &clGetSupportedImageFormats_shutdown,
    &clGetMemObjectInfo_shutdown,
    &clGetImageInfo_shutdown,
    &clCreateSampler_shutdown,
    &clRetainSampler_shutdown,
    &clReleaseSampler_shutdown,
    &clGetSamplerInfo_shutdown,
    &clCreateProgramWithSource_shutdown,
    &clCreateProgramWithBinary_shutdown,
    &clRetainProgram_shutdown,
    &clReleaseProgram_shutdown,
    &clBuildProgram_shutdown,
    &clUnloadCompiler_shutdown,
    &clGetProgramInfo_shutdown,
    &clGetProgramBuildInfo_shutdown,
    &clCreateKernel_shutdown,
    &clCreateKernelsInProgram_shutdown,
    &clRetainKernel_shutdown,
    &clReleaseKernel_shutdown,
    &clSetKernelArg_shutdown,
    &clGetKernelInfo_shutdown,
    &clGetKernelWorkGroupInfo_shutdown,
    &clWaitForEvents_shutdown,
    &clGetEventInfo_shutdown,
    &clRetainEvent_shutdown,
    &clReleaseEvent_shutdown,
    &clGetEventProfilingInfo_shutdown,
    &clFlush_shutdown,
    &clFinish_shutdown,
    &clEnqueueReadBuffer_shutdown,
    &clEnqueueWriteBuffer_shutdown,
    &clEnqueueCopyBuffer_shutdown,
    &clEnqueueReadImage_shutdown,
    &clEnqueueWriteImage_shutdown,
    &clEnqueueCopyImage_shutdown,
    &clEnqueueCopyImageToBuffer_shutdown,
    &clEnqueueCopyBufferToImage_shutdown,
    &clEnqueueMapBuffer_shutdown,
    &clEnqueueMapImage_shutdown,
    &clEnqueueUnmapMemObject_shutdown,
    &clEnqueueNDRangeKernel_shutdown,
    &clEnqueueTask_shutdown,
    &clEnqueueNativeKernel_shutdown,
    &clEnqueueMarker_shutdown,
    &clEnqueueWaitForEvents_shutdown,
    &clEnqueueBarrier_shutdown,
    &clGetExtensionFunctionAddress_shutdown,
    &clCreateFromGLBuffer_shutdown,
    &clCreateFromGLTexture2D_shutdown,
    &clCreateFromGLTexture3D_shutdown,
    &clCreateFromGLRenderbuffer_shutdown,
    &clGetGLObjectInfo_shutdown,
    &clGetGLTextureInfo_shutdown,
    &clEnqueueAcquireGLObjects_shutdown,
    &clEnqueueReleaseGLObjects_shutdown,
    &clGetGLContextInfoKHR_shutdown,

    /* cl_khr_d3d10_sharing */
#if defined(_WIN32)
    &clGetDeviceIDsFromD3D10KHR_shutdown,
    &clCreateFromD3D10BufferKHR_shutdown,
    &clCreateFromD3D10Texture2DKHR_shutdown,
    &clCreateFromD3D10Texture3DKHR_shutdown,
    &clEnqueueAcquireD3D10ObjectsKHR_shutdown,
    &clEnqueueReleaseD3D10ObjectsKHR_shutdown,
#else
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#endif

    /* OpenCL 1.1 */
    &clSetEventCallback_shutdown,
    &clCreateSubBuffer_shutdown,
    &clSetMemObjectDestructorCallback_shutdown,
    &clCreateUserEvent_shutdown,
    &clSetUserEventStatus_shutdown,
    &clEnqueueReadBufferRect_shutdown,
    &clEnqueueWriteBufferRect_shutdown,
    &clEnqueueCopyBufferRect_shutdown,

    /* cl_ext_device_fission */
    &clCreateSubDevicesEXT_shutdown,
    &clRetainDeviceEXT_shutdown,
    &clReleaseDeviceEXT_shutdown,

    /* cl_khr_gl_event */
    &clCreateEventFromGLsyncKHR_shutdown,

    /* OpenCL 1.2 */
    &clCreateSubDevices_shutdown,
    &clRetainDevice_shutdown,
    &clReleaseDevice_shutdown,
    &clCreateImage_shutdown,
    &clCreateProgramWithBuiltInKernels_shutdown,
    &clCompileProgram_shutdown,
    &clLinkProgram_shutdown,
    &clUnloadPlatformCompiler_shutdown,
    &clGetKernelArgInfo_shutdown,
    &clEnqueueFillBuffer_shutdown,
    &clEnqueueFillImage_shutdown,
    &clEnqueueMigrateMemObjects_shutdown,
    &clEnqueueMarkerWithWaitList_shutdown,
    &clEnqueueBarrierWithWaitList_shutdown,
    &clGetExtensionFunctionAddressForPlatform_shutdown,
    &clCreateFromGLTexture_shutdown,

    /* cl_khr_d3d11_sharing */
#if defined(_WIN32)
    &clGetDeviceIDsFromD3D11KHR_shutdown,
    &clCreateFromD3D11BufferKHR_shutdown,
    &clCreateFromD3D11Texture2DKHR_shutdown,
    &clCreateFromD3D11Texture3DKHR_shutdown,
    &clCreateFromDX9MediaSurfaceKHR_shutdown,
    &clEnqueueAcquireD3D11ObjectsKHR_shutdown,
    &clEnqueueReleaseD3D11ObjectsKHR_shutdown,
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
    &clGetDeviceIDsFromDX9MediaAdapterKHR_shutdown,
    &clEnqueueAcquireDX9MediaSurfacesKHR_shutdown,
    &clEnqueueReleaseDX9MediaSurfacesKHR_shutdown,
#else
    NULL,
    NULL,
    NULL,
#endif

    /* cl_khr_egl_image */
    &clCreateFromEGLImageKHR_shutdown,
    &clEnqueueAcquireEGLObjectsKHR_shutdown,
    &clEnqueueReleaseEGLObjectsKHR_shutdown,

    /* cl_khr_egl_event */
    &clCreateEventFromEGLSyncKHR_shutdown,

    /* OpenCL 2.0 */
    &clCreateCommandQueueWithProperties_shutdown,
    &clCreatePipe_shutdown,
    &clGetPipeInfo_shutdown,
    &clSVMAlloc_shutdown,
    &clSVMFree_shutdown,
    &clEnqueueSVMFree_shutdown,
    &clEnqueueSVMMemcpy_shutdown,
    &clEnqueueSVMMemFill_shutdown,
    &clEnqueueSVMMap_shutdown,
    &clEnqueueSVMUnmap_shutdown,
    &clCreateSamplerWithProperties_shutdown,
    &clSetKernelArgSVMPointer_shutdown,
    &clSetKernelExecInfo_shutdown,

    /* cl_khr_sub_groups */
    &clGetKernelSubGroupInfoKHR_shutdown,

    /* OpenCL 2.1 */
    &clCloneKernel_shutdown,
    &clCreateProgramWithIL_shutdown,
    &clEnqueueSVMMigrateMem_shutdown,
    &clGetDeviceAndHostTimer_shutdown,
    &clGetHostTimer_shutdown,
    &clGetKernelSubGroupInfo_shutdown,
    &clSetDefaultDeviceCommandQueue_shutdown,

    /* OpenCL 2.2 */
    &clSetProgramReleaseCallback_shutdown,
    &clSetProgramSpecializationConstant_shutdown,

    /* OpenCL 3.0 */
    &clCreateBufferWithProperties_shutdown,
    &clCreateImageWithProperties_shutdown,
    &clSetContextDestructorCallback_shutdown,
};

#endif // defined(CL_ENABLE_LAYERS)

#ifdef __cplusplus
}
#endif
