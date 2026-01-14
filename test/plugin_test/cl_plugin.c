#include <CL/cl.h>
#include <stdlib.h>
#include <stdio.h>
#include "cl_plugin.h"

#define CL_ERR_CHECK(x)                                             \
  do {                                                              \
    cl_int err = x;                                                 \
    if (CL_SUCCESS != err) {                                        \
      fprintf(stderr, "%s: failed with error code: %d\n", #x, err); \
      return PLUGIN_ERROR;                                          \
    }                                                               \
  } while (0)

plugin_init_fn PLUGIN_INIT;
extern int PLUGIN_INIT(void) {
  cl_uint num_platforms = 0;
  cl_platform_id* platforms = NULL;
  CL_ERR_CHECK(clGetPlatformIDs(0, NULL, &num_platforms));
  if (!num_platforms) {
    fprintf(stderr, "No platform found\n");
    return PLUGIN_ERROR;
  }
  platforms = (cl_platform_id*) malloc(num_platforms * sizeof(cl_platform_id));
  if (!platforms) {
    fprintf(stderr, "malloc failed to allocate %zu bytes\n",
            num_platforms * sizeof(cl_platform_id));
    return PLUGIN_ERROR;
  }
  CL_ERR_CHECK(clGetPlatformIDs(num_platforms, platforms, NULL));
  free(platforms);
  return PLUGIN_SUCCESS;
}
