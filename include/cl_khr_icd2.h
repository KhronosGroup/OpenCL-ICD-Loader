#if !defined(CL_PLATFORM_UNLOADABLE)
#define CL_PLATFORM_UNLOADABLE_KHR 0x0921
#endif

#if defined(CL_ENABLE_LAYERS) && !defined(CL_LAYER_API_VERSION_200)
#define CL_LAYER_API_VERSION_200 200

typedef cl_int CL_API_CALL
clDeinitLayer_t(void);

typedef clDeinitLayer_t *pfn_clDeinitLayer;
#endif //defined(CL_ENABLE_LAYERS) && !defined(CL_LAYER_API_VERSION_200)

#if !defined(CL_ICD2_TAG_KHR)
#if INTPTR_MAX == INT32_MAX
#define CL_ICD2_TAG_KHR ((intptr_t)0x434C3331)
#else
#define CL_ICD2_TAG_KHR ((intptr_t)0x4F50454E434C3331)
#endif

typedef void * CL_API_CALL
clIcdGetFunctionAddressForPlatformKHR_t(
    cl_platform_id platform,
    const char* func_name);

typedef clIcdGetFunctionAddressForPlatformKHR_t *
clIcdGetFunctionAddressForPlatformKHR_fn;

typedef cl_int CL_API_CALL
clIcdSetPlatformDispatchDataKHR_t(
    cl_platform_id platform,
    void *disp_data);

typedef clIcdSetPlatformDispatchDataKHR_t *
clIcdSetPlatformDispatchDataKHR_fn;
#endif // !defined(CL_ICD2_TAG_KHR)
