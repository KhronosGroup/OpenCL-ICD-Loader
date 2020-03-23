add_library (IcdLog
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_test_log.c
)

if (WIN32)
    target_compile_definitions (IcdLog PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

target_compile_definitions(IcdLog PRIVATE CL_TARGET_OPENCL_VERSION=220)
