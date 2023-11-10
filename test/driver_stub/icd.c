#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "icd_structs.h"

#define CL_USE_DEPRECATED_OPENCL_1_0_APIS
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#define CL_USE_DEPRECATED_OPENCL_2_1_APIS
#define CL_USE_DEPRECATED_OPENCL_2_2_APIS

// Need to rename all CL API functions to prevent ICD loader functions calling
// themselves via the dispatch table. Include this before cl headers.
#include "rename_api.h"

#include "CL/cl.h"
#include "CL/cl_gl.h"

#if defined(CL_ENABLE_ICD2)
#include "cl_khr_icd2.h"
CL_API_ENTRY clIcdGetFunctionAddressForPlatformKHR_t clIcdGetFunctionAddressForPlatformKHR;
CL_API_ENTRY clIcdSetPlatformDispatchDataKHR_t clIcdSetPlatformDispatchDataKHR;
#endif

/*
 * Prototypes for deprecated functions no longer present in cl.h
 */
extern CL_API_ENTRY cl_int CL_API_CALL
clSetCommandQueueProperty(cl_command_queue              /* command_queue */,
                          cl_command_queue_properties   /* properties */, 
                          cl_bool                       /* enable */,
                          cl_command_queue_properties * /* old_properties */);

#define ICD_DISPATCH_TABLE_ENTRY(fn) \
    assert(dispatchTable->entryCount < 256); \
    dispatchTable->entries[dispatchTable->entryCount++] = (void*)(intptr_t)(fn)

cl_int cliIcdDispatchTableCreate(CLIicdDispatchTable **outDispatchTable)
{
    CLIicdDispatchTable *dispatchTable = NULL;
    cl_int result = CL_SUCCESS;

    // allocate the public handle
    dispatchTable = (CLIicdDispatchTable *) malloc(sizeof(*dispatchTable));
    if (!dispatchTable) {
        result = CL_OUT_OF_HOST_MEMORY;
        goto Error;
    }
    memset(dispatchTable, 0, sizeof(*dispatchTable));

    // OpenCL 1.0
#ifdef CL_ENABLE_ICD2
    ICD_DISPATCH_TABLE_ENTRY ( CL_ICD2_TAG_KHR               );
#else
    ICD_DISPATCH_TABLE_ENTRY ( clGetPlatformIDs              );
#endif
    ICD_DISPATCH_TABLE_ENTRY ( clGetPlatformInfo             );
    ICD_DISPATCH_TABLE_ENTRY ( clGetDeviceIDs                );
    ICD_DISPATCH_TABLE_ENTRY ( clGetDeviceInfo               );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateContext               );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateContextFromType       );
    ICD_DISPATCH_TABLE_ENTRY ( clRetainContext               );
    ICD_DISPATCH_TABLE_ENTRY ( clReleaseContext              );
    ICD_DISPATCH_TABLE_ENTRY ( clGetContextInfo              );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateCommandQueue          );
    ICD_DISPATCH_TABLE_ENTRY ( clRetainCommandQueue          );
    ICD_DISPATCH_TABLE_ENTRY ( clReleaseCommandQueue         );
    ICD_DISPATCH_TABLE_ENTRY ( clGetCommandQueueInfo         );
    ICD_DISPATCH_TABLE_ENTRY ( clSetCommandQueueProperty     );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateBuffer                );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateImage2D               );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateImage3D               );
    ICD_DISPATCH_TABLE_ENTRY ( clRetainMemObject             );
    ICD_DISPATCH_TABLE_ENTRY ( clReleaseMemObject            );
    ICD_DISPATCH_TABLE_ENTRY ( clGetSupportedImageFormats    );
    ICD_DISPATCH_TABLE_ENTRY ( clGetMemObjectInfo            );
    ICD_DISPATCH_TABLE_ENTRY ( clGetImageInfo                );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateSampler               );
    ICD_DISPATCH_TABLE_ENTRY ( clRetainSampler               );
    ICD_DISPATCH_TABLE_ENTRY ( clReleaseSampler              );
    ICD_DISPATCH_TABLE_ENTRY ( clGetSamplerInfo              );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateProgramWithSource     );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateProgramWithBinary     );
    ICD_DISPATCH_TABLE_ENTRY ( clRetainProgram               );
    ICD_DISPATCH_TABLE_ENTRY ( clReleaseProgram              );
    ICD_DISPATCH_TABLE_ENTRY ( clBuildProgram                );
#ifdef CL_ENABLE_ICD2
    ICD_DISPATCH_TABLE_ENTRY ( CL_ICD2_TAG_KHR               );
#else
    ICD_DISPATCH_TABLE_ENTRY ( clUnloadCompiler              );
#endif
    ICD_DISPATCH_TABLE_ENTRY ( clGetProgramInfo              );
    ICD_DISPATCH_TABLE_ENTRY ( clGetProgramBuildInfo         );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateKernel                );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateKernelsInProgram      );
    ICD_DISPATCH_TABLE_ENTRY ( clRetainKernel                );
    ICD_DISPATCH_TABLE_ENTRY ( clReleaseKernel               );
    ICD_DISPATCH_TABLE_ENTRY ( clSetKernelArg                );
    ICD_DISPATCH_TABLE_ENTRY ( clGetKernelInfo               );
    ICD_DISPATCH_TABLE_ENTRY ( clGetKernelWorkGroupInfo      );
    ICD_DISPATCH_TABLE_ENTRY ( clWaitForEvents               );
    ICD_DISPATCH_TABLE_ENTRY ( clGetEventInfo                );
    ICD_DISPATCH_TABLE_ENTRY ( clRetainEvent                 );
    ICD_DISPATCH_TABLE_ENTRY ( clReleaseEvent                );
    ICD_DISPATCH_TABLE_ENTRY ( clGetEventProfilingInfo       );
    ICD_DISPATCH_TABLE_ENTRY ( clFlush                       );
    ICD_DISPATCH_TABLE_ENTRY ( clFinish                      );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueReadBuffer           );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueWriteBuffer          );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueCopyBuffer           );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueReadImage            );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueWriteImage           );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueCopyImage            );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueCopyImageToBuffer    );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueCopyBufferToImage    );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueMapBuffer            );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueMapImage             );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueUnmapMemObject       );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueNDRangeKernel        );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueTask                 );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueNativeKernel         );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueMarker               );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueWaitForEvents        );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueBarrier              );
    ICD_DISPATCH_TABLE_ENTRY ( clGetExtensionFunctionAddress );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateFromGLBuffer          );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateFromGLTexture2D       );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateFromGLTexture3D       );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateFromGLRenderbuffer    );
    ICD_DISPATCH_TABLE_ENTRY ( clGetGLObjectInfo             );
    ICD_DISPATCH_TABLE_ENTRY ( clGetGLTextureInfo            );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueAcquireGLObjects     );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueReleaseGLObjects     );

    // cl_khr_gl_sharing
    ICD_DISPATCH_TABLE_ENTRY ( clGetGLContextInfoKHR         );

    // cl_khr_d3d10_sharing (windows-only)
#if 0 && defined(_WIN32)
    ICD_DISPATCH_TABLE_ENTRY ( clGetDeviceIDsFromD3D10KHR      );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateFromD3D10BufferKHR      );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateFromD3D10Texture2DKHR   );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateFromD3D10Texture3DKHR   );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueAcquireD3D10ObjectsKHR );
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueReleaseD3D10ObjectsKHR );
#else
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
#endif

    // OpenCL 1.1
    ICD_DISPATCH_TABLE_ENTRY ( clSetEventCallback);
    ICD_DISPATCH_TABLE_ENTRY ( clCreateSubBuffer);
    ICD_DISPATCH_TABLE_ENTRY ( clSetMemObjectDestructorCallback);
    ICD_DISPATCH_TABLE_ENTRY ( clCreateUserEvent);
    ICD_DISPATCH_TABLE_ENTRY ( clSetUserEventStatus);
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueReadBufferRect);
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueWriteBufferRect);
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueCopyBufferRect);

    /* cl_ext_device_fission */
    ICD_DISPATCH_TABLE_ENTRY ( /*clCreateSubDevicesEXT*/NULL);
    ICD_DISPATCH_TABLE_ENTRY ( /*clRetainDeviceEXT*/ NULL);
    ICD_DISPATCH_TABLE_ENTRY ( /*clReleaseDevice*/NULL);

    /* cl_khr_gl_event */
    ICD_DISPATCH_TABLE_ENTRY ( clCreateEventFromGLsyncKHR); 

    /* OpenCL 1.2 */
    ICD_DISPATCH_TABLE_ENTRY ( clCreateSubDevices);
    ICD_DISPATCH_TABLE_ENTRY ( clRetainDevice);
    ICD_DISPATCH_TABLE_ENTRY ( clReleaseDevice);
    ICD_DISPATCH_TABLE_ENTRY ( clCreateImage);
    ICD_DISPATCH_TABLE_ENTRY ( clCreateProgramWithBuiltInKernels);
    ICD_DISPATCH_TABLE_ENTRY ( clCompileProgram);
    ICD_DISPATCH_TABLE_ENTRY ( clLinkProgram);
    ICD_DISPATCH_TABLE_ENTRY ( clUnloadPlatformCompiler);
    ICD_DISPATCH_TABLE_ENTRY ( clGetKernelArgInfo);
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueFillBuffer);
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueFillImage);
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueMigrateMemObjects);
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueMarkerWithWaitList);
    ICD_DISPATCH_TABLE_ENTRY ( clEnqueueBarrierWithWaitList);
    ICD_DISPATCH_TABLE_ENTRY ( clGetExtensionFunctionAddressForPlatform);
    ICD_DISPATCH_TABLE_ENTRY ( clCreateFromGLTexture);

    /* cl_khr_d3d11_sharing */
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );

    /* cl_khr_dx9_media_sharing */
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );

    /* cl_khr_egl_image */
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );

    /* cl_khr_egl_event */
    ICD_DISPATCH_TABLE_ENTRY( NULL );

    /* OpenCL 2.0 */
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );

    /* cl_khr_sub_groups */
    ICD_DISPATCH_TABLE_ENTRY( NULL );

    /* OpenCL 2.1 */
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );

    /* OpenCL 2.2 */
    ICD_DISPATCH_TABLE_ENTRY( NULL );
    ICD_DISPATCH_TABLE_ENTRY( NULL );

    /* OpenCL 3.0 */
    ICD_DISPATCH_TABLE_ENTRY ( clCreateBufferWithProperties );
    ICD_DISPATCH_TABLE_ENTRY ( clCreateImageWithProperties );
    ICD_DISPATCH_TABLE_ENTRY ( clSetContextDestructorCallback );

    // return success
    *outDispatchTable = dispatchTable;
    return CL_SUCCESS;

Error:
    return result;
}

void
cliIcdDispatchTableDestroy(CLIicdDispatchTable *dispatchTable)
{
    free(dispatchTable);
}

#ifdef CL_ENABLE_ICD2

#define ICD_GET_FUNCTION_ADDRESS(fn)                                           \
do                                                                             \
{                                                                              \
    if (!strcmp(#fn, func_name))                                               \
        return (void*)(intptr_t)(fn);                                          \
} while (0)

void * CL_API_CALL clIcdGetFunctionAddressForPlatformKHR(
    cl_platform_id platform,
    const char* func_name)
{
    (void)platform;
    ICD_GET_FUNCTION_ADDRESS ( clGetPlatformIDs              );
    ICD_GET_FUNCTION_ADDRESS ( clGetPlatformInfo             );
    ICD_GET_FUNCTION_ADDRESS ( clGetDeviceIDs                );
    ICD_GET_FUNCTION_ADDRESS ( clGetDeviceInfo               );
    ICD_GET_FUNCTION_ADDRESS ( clCreateContext               );
    ICD_GET_FUNCTION_ADDRESS ( clCreateContextFromType       );
    ICD_GET_FUNCTION_ADDRESS ( clRetainContext               );
    ICD_GET_FUNCTION_ADDRESS ( clReleaseContext              );
    ICD_GET_FUNCTION_ADDRESS ( clGetContextInfo              );
    ICD_GET_FUNCTION_ADDRESS ( clCreateCommandQueue          );
    ICD_GET_FUNCTION_ADDRESS ( clRetainCommandQueue          );
    ICD_GET_FUNCTION_ADDRESS ( clReleaseCommandQueue         );
    ICD_GET_FUNCTION_ADDRESS ( clGetCommandQueueInfo         );
    ICD_GET_FUNCTION_ADDRESS ( clSetCommandQueueProperty     );
    ICD_GET_FUNCTION_ADDRESS ( clCreateBuffer                );
    ICD_GET_FUNCTION_ADDRESS ( clCreateImage2D               );
    ICD_GET_FUNCTION_ADDRESS ( clCreateImage3D               );
    ICD_GET_FUNCTION_ADDRESS ( clRetainMemObject             );
    ICD_GET_FUNCTION_ADDRESS ( clReleaseMemObject            );
    ICD_GET_FUNCTION_ADDRESS ( clGetSupportedImageFormats    );
    ICD_GET_FUNCTION_ADDRESS ( clGetMemObjectInfo            );
    ICD_GET_FUNCTION_ADDRESS ( clGetImageInfo                );
    ICD_GET_FUNCTION_ADDRESS ( clCreateSampler               );
    ICD_GET_FUNCTION_ADDRESS ( clRetainSampler               );
    ICD_GET_FUNCTION_ADDRESS ( clReleaseSampler              );
    ICD_GET_FUNCTION_ADDRESS ( clGetSamplerInfo              );
    ICD_GET_FUNCTION_ADDRESS ( clCreateProgramWithSource     );
    ICD_GET_FUNCTION_ADDRESS ( clCreateProgramWithBinary     );
    ICD_GET_FUNCTION_ADDRESS ( clRetainProgram               );
    ICD_GET_FUNCTION_ADDRESS ( clReleaseProgram              );
    ICD_GET_FUNCTION_ADDRESS ( clBuildProgram                );
    ICD_GET_FUNCTION_ADDRESS ( clUnloadCompiler              );
    ICD_GET_FUNCTION_ADDRESS ( clGetProgramInfo              );
    ICD_GET_FUNCTION_ADDRESS ( clGetProgramBuildInfo         );
    ICD_GET_FUNCTION_ADDRESS ( clCreateKernel                );
    ICD_GET_FUNCTION_ADDRESS ( clCreateKernelsInProgram      );
    ICD_GET_FUNCTION_ADDRESS ( clRetainKernel                );
    ICD_GET_FUNCTION_ADDRESS ( clReleaseKernel               );
    ICD_GET_FUNCTION_ADDRESS ( clSetKernelArg                );
    ICD_GET_FUNCTION_ADDRESS ( clGetKernelInfo               );
    ICD_GET_FUNCTION_ADDRESS ( clGetKernelWorkGroupInfo      );
    ICD_GET_FUNCTION_ADDRESS ( clWaitForEvents               );
    ICD_GET_FUNCTION_ADDRESS ( clGetEventInfo                );
    ICD_GET_FUNCTION_ADDRESS ( clRetainEvent                 );
    ICD_GET_FUNCTION_ADDRESS ( clReleaseEvent                );
    ICD_GET_FUNCTION_ADDRESS ( clGetEventProfilingInfo       );
    ICD_GET_FUNCTION_ADDRESS ( clFlush                       );
    ICD_GET_FUNCTION_ADDRESS ( clFinish                      );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueReadBuffer           );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueWriteBuffer          );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueCopyBuffer           );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueReadImage            );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueWriteImage           );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueCopyImage            );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueCopyImageToBuffer    );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueCopyBufferToImage    );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueMapBuffer            );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueMapImage             );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueUnmapMemObject       );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueNDRangeKernel        );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueTask                 );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueNativeKernel         );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueMarker               );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueWaitForEvents        );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueBarrier              );
    ICD_GET_FUNCTION_ADDRESS ( clGetExtensionFunctionAddress );
    ICD_GET_FUNCTION_ADDRESS ( clCreateFromGLBuffer          );
    ICD_GET_FUNCTION_ADDRESS ( clCreateFromGLTexture2D       );
    ICD_GET_FUNCTION_ADDRESS ( clCreateFromGLTexture3D       );
    ICD_GET_FUNCTION_ADDRESS ( clCreateFromGLRenderbuffer    );
    ICD_GET_FUNCTION_ADDRESS ( clGetGLObjectInfo             );
    ICD_GET_FUNCTION_ADDRESS ( clGetGLTextureInfo            );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueAcquireGLObjects     );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueReleaseGLObjects     );

    // cl_khr_gl_sharing
    ICD_GET_FUNCTION_ADDRESS ( clGetGLContextInfoKHR         );

#if 0
    // cl_khr_d3d10_sharing (windows-only)
#if 0 && defined(_WIN32)
    ICD_GET_FUNCTION_ADDRESS ( clGetDeviceIDsFromD3D10KHR      );
    ICD_GET_FUNCTION_ADDRESS ( clCreateFromD3D10BufferKHR      );
    ICD_GET_FUNCTION_ADDRESS ( clCreateFromD3D10Texture2DKHR   );
    ICD_GET_FUNCTION_ADDRESS ( clCreateFromD3D10Texture3DKHR   );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueAcquireD3D10ObjectsKHR );
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueReleaseD3D10ObjectsKHR );
#else
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
#endif
#endif

    // OpenCL 1.1
    ICD_GET_FUNCTION_ADDRESS ( clSetEventCallback);
    ICD_GET_FUNCTION_ADDRESS ( clCreateSubBuffer);
    ICD_GET_FUNCTION_ADDRESS ( clSetMemObjectDestructorCallback);
    ICD_GET_FUNCTION_ADDRESS ( clCreateUserEvent);
    ICD_GET_FUNCTION_ADDRESS ( clSetUserEventStatus);
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueReadBufferRect);
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueWriteBufferRect);
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueCopyBufferRect);

#if 0
    /* cl_ext_device_fission */
    ICD_GET_FUNCTION_ADDRESS ( /*clCreateSubDevicesEXT*/NULL);
    ICD_GET_FUNCTION_ADDRESS ( /*clRetainDeviceEXT*/ NULL);
    ICD_GET_FUNCTION_ADDRESS ( /*clReleaseDevice*/NULL);
#endif

    /* cl_khr_gl_event */
    ICD_GET_FUNCTION_ADDRESS ( clCreateEventFromGLsyncKHR);

    /* OpenCL 1.2 */
    ICD_GET_FUNCTION_ADDRESS ( clCreateSubDevices);
    ICD_GET_FUNCTION_ADDRESS ( clRetainDevice);
    ICD_GET_FUNCTION_ADDRESS ( clReleaseDevice);
    ICD_GET_FUNCTION_ADDRESS ( clCreateImage);
    ICD_GET_FUNCTION_ADDRESS ( clCreateProgramWithBuiltInKernels);
    ICD_GET_FUNCTION_ADDRESS ( clCompileProgram);
    ICD_GET_FUNCTION_ADDRESS ( clLinkProgram);
    ICD_GET_FUNCTION_ADDRESS ( clUnloadPlatformCompiler);
    ICD_GET_FUNCTION_ADDRESS ( clGetKernelArgInfo);
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueFillBuffer);
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueFillImage);
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueMigrateMemObjects);
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueMarkerWithWaitList);
    ICD_GET_FUNCTION_ADDRESS ( clEnqueueBarrierWithWaitList);
    ICD_GET_FUNCTION_ADDRESS ( clGetExtensionFunctionAddressForPlatform);
    ICD_GET_FUNCTION_ADDRESS ( clCreateFromGLTexture);

#if 0
    /* cl_khr_d3d11_sharing */
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );

    /* cl_khr_dx9_media_sharing */
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );

    /* cl_khr_egl_image */
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );

    /* cl_khr_egl_event */
    ICD_GET_FUNCTION_ADDRESS( NULL );

    /* OpenCL 2.0 */
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );

    /* cl_khr_sub_groups */
    ICD_GET_FUNCTION_ADDRESS( NULL );

    /* OpenCL 2.1 */
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );

    /* OpenCL 2.2 */
    ICD_GET_FUNCTION_ADDRESS( NULL );
    ICD_GET_FUNCTION_ADDRESS( NULL );
#endif

    /* OpenCL 3.0 */
    ICD_GET_FUNCTION_ADDRESS ( clCreateBufferWithProperties );
    ICD_GET_FUNCTION_ADDRESS ( clCreateImageWithProperties );
    ICD_GET_FUNCTION_ADDRESS ( clSetContextDestructorCallback );

    return NULL;
}

cl_int CL_API_CALL
clIcdSetPlatformDispatchDataKHR(
    cl_platform_id platform,
    void *disp_data)
{
    ((struct CLIplatform_st *)platform)->dispData = disp_data;
    return CL_SUCCESS;
}
#endif //CL_ENABLE_ICD2
