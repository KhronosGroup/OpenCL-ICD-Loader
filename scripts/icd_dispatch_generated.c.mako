<%
from mako.template import Template
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

table_template = Template(filename='dispatch_table.mako')
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
    return KHR_ICD2_DISPATCH(${api.Params[2].Name}[0])->${api.Name}(
%elif api.Name == "clWaitForEvents":
    return KHR_ICD2_DISPATCH(${api.Params[1].Name}[0])->${api.Name}(
%elif api.Name == "clCreateContextFromType":
    return KHR_ICD2_DISPATCH(platform)->${api.Name}(
%elif api.Name == "clSVMFree":
    KHR_ICD2_DISPATCH(${handle.Name})->${api.Name}(
%elif api.Name == "clUnloadCompiler":
    return CL_SUCCESS;
%else:
    return KHR_ICD2_DISPATCH(${handle.Name})->${api.Name}(
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

///////////////////////////////////////////////////////////////////////////////
%endfor
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
    KHR_ICD_VALIDATE_POINTER_RETURN_HANDLE(KHR_ICD2_DISPATCH(${handle.Name})->${api.Name});
%  endif
%else:
%  if api.Name == "clGetGLContextInfoKHR":
    cl_platform_id platform = NULL;
    khrIcdContextPropertiesGetPlatform(properties, &platform);
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(platform, CL_INVALID_PLATFORM);
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(KHR_ICD2_DISPATCH(platform)->${api.Name});
%  else:
    KHR_ICD_VALIDATE_HANDLE_RETURN_ERROR(${handle.Name}, ${invalid});
    KHR_ICD_VALIDATE_POINTER_RETURN_ERROR(KHR_ICD2_DISPATCH(${handle.Name})->${api.Name});
%  endif
%endif
%if api.Name == "clGetGLContextInfoKHR":
    return KHR_ICD2_DISPATCH(platform)->${api.Name}(
%else:
    return KHR_ICD2_DISPATCH(${handle.Name})->${api.Name}(
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
///////////////////////////////////////////////////////////////////////////////

%endfor
#if defined(CL_ENABLE_LAYERS)
const struct _cl_icd_dispatch khrMainDispatch = ${table_template.render(suffix = 'disp')};
#endif // defined(CL_ENABLE_LAYERS)

#if defined(CL_ENABLE_LOADER_MANAGED_DISPATCH) || defined(CL_ENABLE_LAYERS)
///////////////////////////////////////////////////////////////////////////////
// Core APIs:
%for apis in coreapis.values():
%for api in apis:
static ${api.RetType} CL_API_CALL ${api.Name}_unsupp(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd})
%  endif
%endfor
{
%for param in api.Params:
%  if param.Name:
    (void)${param.Name};
%  endif
%endfor
%if api.Name == "clSVMAlloc" or api.Name == "clGetExtensionFunctionAddressForPlatform" or api.Name == "clGetExtensionFunctionAddress":
    KHR_ICD_ERROR_RETURN_ERROR(NULL);
%elif api.Name == "clSVMFree":
    return;
%elif api.RetType in apihandles or api.RetType == "void*":
    KHR_ICD_ERROR_RETURN_HANDLE(CL_INVALID_OPERATION);
%else:
    KHR_ICD_ERROR_RETURN_ERROR(CL_INVALID_OPERATION);
%endif
}
%endfor
%endfor

///////////////////////////////////////////////////////////////////////////////
%for extension in icdextensions:
<%
    apis = extapis[extension]
%>// ${extension}
%if extension in win32extensions:

#if defined(_WIN32)
%endif
%for api in apis:
static ${api.RetType} CL_API_CALL ${api.Name}_unsupp(
%for i, param in enumerate(api.Params):
%  if i < len(api.Params)-1:
    ${param.Type} ${param.Name}${param.TypeEnd},
%  else:
    ${param.Type} ${param.Name}${param.TypeEnd})
%  endif
%endfor
{
%for param in api.Params:
%  if param.Name:
    (void)${param.Name};
%  endif
%endfor
%if api.RetType in apihandles or api.RetType == "void*":
    KHR_ICD_ERROR_RETURN_HANDLE(CL_INVALID_OPERATION);
%else:
    KHR_ICD_ERROR_RETURN_ERROR(CL_INVALID_OPERATION);
%endif
}
%endfor
%if extension in win32extensions:
#endif // defined(_WIN32)

%endif
///////////////////////////////////////////////////////////////////////////////

%endfor
#endif // defined(CL_ENABLE_LOADER_MANAGED_DISPATCH) || defined(CL_ENABLE_LAYERS)

#if defined(CL_ENABLE_LAYERS)
const struct _cl_icd_dispatch khrDeinitDispatch = ${table_template.render(suffix = 'unsupp')};
#endif // defined(CL_ENABLE_LAYERS)

#if defined(CL_ENABLE_LOADER_MANAGED_DISPATCH)
void khrIcd2PopulateDispatchTable(
    cl_platform_id platform,
    clIcdGetFunctionAddressForPlatformKHR_fn p_clIcdGetFunctionAddressForPlatform,
    struct _cl_icd_dispatch* dispatch)
{
///////////////////////////////////////////////////////////////////////////////
// Core APIs:
%for apis in coreapis.values():
%for api in apis:
   dispatch->${api.Name} = (${api.Name}_t *)(size_t)p_clIcdGetFunctionAddressForPlatform(platform, "${api.Name}");
   if (!dispatch->${api.Name})
       dispatch->${api.Name} = &${api.Name}_unsupp;
%endfor
%endfor

///////////////////////////////////////////////////////////////////////////////
%for extension in icdextensions:
<%
    apis = extapis[extension]
%>// ${extension}
%if extension in win32extensions:

#if defined(_WIN32)
%endif
%for api in apis:
   dispatch->${api.Name} = (${api.Name}_t *)(size_t)p_clIcdGetFunctionAddressForPlatform(platform, "${api.Name}");
   if (!dispatch->${api.Name})
       dispatch->${api.Name} = &${api.Name}_unsupp;
%endfor
%if extension in win32extensions:
#endif // defined(_WIN32)

%endif
///////////////////////////////////////////////////////////////////////////////

%endfor
}
#endif // defined(CL_ENABLE_LOADER_MANAGED_DISPATCH)

#ifdef __cplusplus
}
#endif
