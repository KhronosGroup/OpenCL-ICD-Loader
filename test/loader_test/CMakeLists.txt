add_executable (icd_loader_test
    ${CMAKE_SOURCE_DIR}/include/cl_khr_icd2.h
    test_kernel.c
    main.c
    test_platforms.c
    icd_test_match.c
    test_program_objects.c
    test_sampler_objects.c
    test_buffer_object.c
    test_cl_runtime.c
    callbacks.c
    test_create_calls.c
    test_clgl.c
    test_image_objects.c )

target_compile_definitions(icd_loader_test
    PRIVATE
        CL_TARGET_OPENCL_VERSION=300
)

target_link_libraries (icd_loader_test OpenCL IcdLog OpenCL::Headers)
