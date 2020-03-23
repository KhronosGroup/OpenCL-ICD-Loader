add_executable (icd_loader_test
    ${CMAKE_CURRENT_SOURCE_DIR}/test_kernel.c
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_platforms.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_test_match.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_program_objects.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_sampler_objects.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_buffer_object.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_cl_runtime.c
    ${CMAKE_CURRENT_SOURCE_DIR}/callbacks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_create_calls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_clgl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_image_objects.c
    )

target_link_libraries (icd_loader_test OpenCL IcdLog)

target_compile_definitions(icd_loader_test PRIVATE CL_TARGET_OPENCL_VERSION=220)
