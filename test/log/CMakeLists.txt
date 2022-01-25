
if (${OPENCL_ICD_LOADER_BUILD_SHARED_LIBS})
    add_library (IcdLog SHARED icd_test_log.c)
else()
    add_library (IcdLog STATIC icd_test_log.c)
endif()

target_link_libraries (IcdLog OpenCL::Headers)
target_compile_definitions (IcdLog PRIVATE CL_TARGET_OPENCL_VERSION=300)
if (WIN32)
    target_compile_definitions (IcdLog PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
