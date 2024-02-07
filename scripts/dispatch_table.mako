{
    ICD_ANON_UNION_INIT_MEMBER(&clGetPlatformIDs_${suffix}),
    &clGetPlatformInfo_${suffix},
    &clGetDeviceIDs_${suffix},
    &clGetDeviceInfo_${suffix},
    &clCreateContext_${suffix},
    &clCreateContextFromType_${suffix},
    &clRetainContext_${suffix},
    &clReleaseContext_${suffix},
    &clGetContextInfo_${suffix},
    &clCreateCommandQueue_${suffix},
    &clRetainCommandQueue_${suffix},
    &clReleaseCommandQueue_${suffix},
    &clGetCommandQueueInfo_${suffix},
    &clSetCommandQueueProperty_${suffix},
    &clCreateBuffer_${suffix},
    &clCreateImage2D_${suffix},
    &clCreateImage3D_${suffix},
    &clRetainMemObject_${suffix},
    &clReleaseMemObject_${suffix},
    &clGetSupportedImageFormats_${suffix},
    &clGetMemObjectInfo_${suffix},
    &clGetImageInfo_${suffix},
    &clCreateSampler_${suffix},
    &clRetainSampler_${suffix},
    &clReleaseSampler_${suffix},
    &clGetSamplerInfo_${suffix},
    &clCreateProgramWithSource_${suffix},
    &clCreateProgramWithBinary_${suffix},
    &clRetainProgram_${suffix},
    &clReleaseProgram_${suffix},
    &clBuildProgram_${suffix},
    ICD_ANON_UNION_INIT_MEMBER(&clUnloadCompiler_${suffix}),
    &clGetProgramInfo_${suffix},
    &clGetProgramBuildInfo_${suffix},
    &clCreateKernel_${suffix},
    &clCreateKernelsInProgram_${suffix},
    &clRetainKernel_${suffix},
    &clReleaseKernel_${suffix},
    &clSetKernelArg_${suffix},
    &clGetKernelInfo_${suffix},
    &clGetKernelWorkGroupInfo_${suffix},
    &clWaitForEvents_${suffix},
    &clGetEventInfo_${suffix},
    &clRetainEvent_${suffix},
    &clReleaseEvent_${suffix},
    &clGetEventProfilingInfo_${suffix},
    &clFlush_${suffix},
    &clFinish_${suffix},
    &clEnqueueReadBuffer_${suffix},
    &clEnqueueWriteBuffer_${suffix},
    &clEnqueueCopyBuffer_${suffix},
    &clEnqueueReadImage_${suffix},
    &clEnqueueWriteImage_${suffix},
    &clEnqueueCopyImage_${suffix},
    &clEnqueueCopyImageToBuffer_${suffix},
    &clEnqueueCopyBufferToImage_${suffix},
    &clEnqueueMapBuffer_${suffix},
    &clEnqueueMapImage_${suffix},
    &clEnqueueUnmapMemObject_${suffix},
    &clEnqueueNDRangeKernel_${suffix},
    &clEnqueueTask_${suffix},
    &clEnqueueNativeKernel_${suffix},
    &clEnqueueMarker_${suffix},
    &clEnqueueWaitForEvents_${suffix},
    &clEnqueueBarrier_${suffix},
    &clGetExtensionFunctionAddress_${suffix},
    &clCreateFromGLBuffer_${suffix},
    &clCreateFromGLTexture2D_${suffix},
    &clCreateFromGLTexture3D_${suffix},
    &clCreateFromGLRenderbuffer_${suffix},
    &clGetGLObjectInfo_${suffix},
    &clGetGLTextureInfo_${suffix},
    &clEnqueueAcquireGLObjects_${suffix},
    &clEnqueueReleaseGLObjects_${suffix},
    &clGetGLContextInfoKHR_${suffix},

  /* cl_khr_d3d10_sharing */
#if defined(_WIN32)
    &clGetDeviceIDsFromD3D10KHR_${suffix},
    &clCreateFromD3D10BufferKHR_${suffix},
    &clCreateFromD3D10Texture2DKHR_${suffix},
    &clCreateFromD3D10Texture3DKHR_${suffix},
    &clEnqueueAcquireD3D10ObjectsKHR_${suffix},
    &clEnqueueReleaseD3D10ObjectsKHR_${suffix},
#else
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#endif

  /* OpenCL 1.1 */
    &clSetEventCallback_${suffix},
    &clCreateSubBuffer_${suffix},
    &clSetMemObjectDestructorCallback_${suffix},
    &clCreateUserEvent_${suffix},
    &clSetUserEventStatus_${suffix},
    &clEnqueueReadBufferRect_${suffix},
    &clEnqueueWriteBufferRect_${suffix},
    &clEnqueueCopyBufferRect_${suffix},

  /* cl_ext_device_fission */
    &clCreateSubDevicesEXT_${suffix},
    &clRetainDeviceEXT_${suffix},
    &clReleaseDeviceEXT_${suffix},

  /* cl_khr_gl_event */
    &clCreateEventFromGLsyncKHR_${suffix},

  /* OpenCL 1.2 */
    &clCreateSubDevices_${suffix},
    &clRetainDevice_${suffix},
    &clReleaseDevice_${suffix},
    &clCreateImage_${suffix},
    &clCreateProgramWithBuiltInKernels_${suffix},
    &clCompileProgram_${suffix},
    &clLinkProgram_${suffix},
    &clUnloadPlatformCompiler_${suffix},
    &clGetKernelArgInfo_${suffix},
    &clEnqueueFillBuffer_${suffix},
    &clEnqueueFillImage_${suffix},
    &clEnqueueMigrateMemObjects_${suffix},
    &clEnqueueMarkerWithWaitList_${suffix},
    &clEnqueueBarrierWithWaitList_${suffix},
    &clGetExtensionFunctionAddressForPlatform_${suffix},
    &clCreateFromGLTexture_${suffix},

  /* cl_khr_d3d11_sharing */
#if defined(_WIN32)
    &clGetDeviceIDsFromD3D11KHR_${suffix},
    &clCreateFromD3D11BufferKHR_${suffix},
    &clCreateFromD3D11Texture2DKHR_${suffix},
    &clCreateFromD3D11Texture3DKHR_${suffix},
    &clCreateFromDX9MediaSurfaceKHR_${suffix},
    &clEnqueueAcquireD3D11ObjectsKHR_${suffix},
    &clEnqueueReleaseD3D11ObjectsKHR_${suffix},
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
    &clGetDeviceIDsFromDX9MediaAdapterKHR_${suffix},
    &clEnqueueAcquireDX9MediaSurfacesKHR_${suffix},
    &clEnqueueReleaseDX9MediaSurfacesKHR_${suffix},
#else
    NULL,
    NULL,
    NULL,
#endif

  /* cl_khr_egl_image */
    &clCreateFromEGLImageKHR_${suffix},
    &clEnqueueAcquireEGLObjectsKHR_${suffix},
    &clEnqueueReleaseEGLObjectsKHR_${suffix},

  /* cl_khr_egl_event */
    &clCreateEventFromEGLSyncKHR_${suffix},

  /* OpenCL 2.0 */
    &clCreateCommandQueueWithProperties_${suffix},
    &clCreatePipe_${suffix},
    &clGetPipeInfo_${suffix},
    &clSVMAlloc_${suffix},
    &clSVMFree_${suffix},
    &clEnqueueSVMFree_${suffix},
    &clEnqueueSVMMemcpy_${suffix},
    &clEnqueueSVMMemFill_${suffix},
    &clEnqueueSVMMap_${suffix},
    &clEnqueueSVMUnmap_${suffix},
    &clCreateSamplerWithProperties_${suffix},
    &clSetKernelArgSVMPointer_${suffix},
    &clSetKernelExecInfo_${suffix},

  /* cl_khr_sub_groups */
    &clGetKernelSubGroupInfoKHR_${suffix},

  /* OpenCL 2.1 */
    &clCloneKernel_${suffix},
    &clCreateProgramWithIL_${suffix},
    &clEnqueueSVMMigrateMem_${suffix},
    &clGetDeviceAndHostTimer_${suffix},
    &clGetHostTimer_${suffix},
    &clGetKernelSubGroupInfo_${suffix},
    &clSetDefaultDeviceCommandQueue_${suffix},

  /* OpenCL 2.2 */
    &clSetProgramReleaseCallback_${suffix},
    &clSetProgramSpecializationConstant_${suffix},

  /* OpenCL 3.0 */
    &clCreateBufferWithProperties_${suffix},
    &clCreateImageWithProperties_${suffix},
    &clSetContextDestructorCallback_${suffix}
}
