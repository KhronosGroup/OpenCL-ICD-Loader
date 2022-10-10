#ifndef OPENCL_CL_ICDL_H
#define OPENCL_CL_ICDL_H

#include <CL/cl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _cl_icdl_info{
    CL_ICDL_OCL_VERSION = 1,
    CL_ICDL_VERSION     = 2,
    CL_ICDL_NAME        = 3,
    CL_ICDL_VENDOR      = 4,
} cl_icdl_info;

typedef cl_int
(CL_API_CALL * pfn_clGetICDLoaderInfoOCLICD)(cl_icdl_info param_name,
                                             size_t       param_value_size,
                                             void *       param_value,
                                             size_t *     param_value_size_ret);

#ifdef __cplusplus
}
#endif


#endif /* OPENCL_CL_ICDL_H */
