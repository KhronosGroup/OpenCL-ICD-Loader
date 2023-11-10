#include <string.h>

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#include "CL/cl.h"
#include "CL/cl_ext.h"
#include "cl_khr_icd2.h"

#if defined(CL_ENABLE_ICD2)
CL_API_ENTRY clIcdGetFunctionAddressForPlatformKHR_t clIcdGetFunctionAddressForPlatformKHR;
CL_API_ENTRY clIcdSetPlatformDispatchDataKHR_t clIcdSetPlatformDispatchDataKHR;
#endif

struct driverStubextFunc_st 
{
    const char *name;
    void *func;
};

#define EXT_FUNC(name) { #name, (void*)(intptr_t)(name) }

static struct driverStubextFunc_st clExtensions[] = 
{
    EXT_FUNC(clIcdGetPlatformIDsKHR),
#ifdef CL_ENABLE_ICD2
    EXT_FUNC(clIcdGetFunctionAddressForPlatformKHR),
    EXT_FUNC(clIcdSetPlatformDispatchDataKHR),
#endif //CL_ENABLE_ICD2
};

static const int clExtensionCount = sizeof(clExtensions) / sizeof(clExtensions[0]);

CL_API_ENTRY void * CL_API_CALL
clGetExtensionFunctionAddress(const char *name)
{
    int ii;
    
    for (ii = 0; ii < clExtensionCount; ii++) {
        if (!strcmp(name, clExtensions[ii].name)) {
            return clExtensions[ii].func;
        }
    }

    return NULL;
}

