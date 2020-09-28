<%
# APIs to skip - they need to be done "manually":
apiskip = {
    'clGetPlatformIDs',                         # to query platforms
    'clGetExtensionFunctionAddress',            # to return ICD-aware extensions
    'clGetExtensionFunctionAddressForPlatform', # to return ICD-aware extensions
    'clCreateBufferWithProperties',             # only until OpenCL 3.0 is final
    'clCreateImageWithProperties',              # only until OpenCL 3.0 is final
    'clSetContextDestructorCallback',           # only until OpenCL 3.0 is final
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

#include "icd_dispatch.h"
#include "icd.h"

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
// Core APIs:
%for apis in coreapis.values():
%for api in apis:
%if not api.Name in apiskip:
<%
      handle = api.Params[0]
      if handle.Type in apihandles:
          invalid = apihandles[handle.Type]
      else:
          invalid = 'NULL'
%>
CL_API_ENTRY ${api.RetType} CL_API_CALL ${api.Name}(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd}) ${api.Suffix}
%  endif
%endfor
{
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
    khrIcdInitialize();
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
    if (${handle.Name} == NULL) return;
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

///////////////////////////////////////////////////////////////////////////////
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
%>// ${extension}
%if extension in win32extensions:

#if defined(_WIN32)
%endif
%for api in apis:
<%
      handle = api.Params[0]
      if handle.Type in apihandles:
          invalid = apihandles[handle.Type]
      else:
          invalid = 'NULL'
%>
CL_API_ENTRY ${api.RetType} CL_API_CALL ${api.Name}(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd}) ${api.Suffix}
%  endif
%endfor
{
%if api.RetType in apihandles or api.RetType == "void*":
%  if False:
    // api.Name == "clXXX":  # There are currently no API special cases here.
%  else:
    KHR_ICD_VALIDATE_HANDLE_RETURN_HANDLE(${handle.Name}, ${invalid});
% endif
%else:
%  if api.Name == "clGetGLContextInfoKHR":
    cl_platform_id platform = NULL;
    khrIcdInitialize();
    khrIcdContextPropertiesGetPlatform(properties, &platform);
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
%  else:
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(${handle.Name}, ${invalid});
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
%endfor

%if extension in win32extensions:
#endif // defined(_WIN32)

%endif
///////////////////////////////////////////////////////////////////////////////

%endfor
#ifdef __cplusplus
}
#endif
