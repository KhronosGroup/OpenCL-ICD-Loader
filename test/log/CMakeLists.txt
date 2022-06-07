
add_library (IcdLog SHARED icd_test_log.c)

target_link_libraries (IcdLog OpenCL::Headers)
target_compile_definitions (IcdLog PRIVATE CL_TARGET_OPENCL_VERSION=300)
if (WIN32)
    target_compile_definitions (IcdLog PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
