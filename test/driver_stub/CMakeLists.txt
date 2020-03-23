set (OPENCL_DRIVER_STUB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/cl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_ext.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cl_gl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd.c
    )

if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    list (APPEND OPENCL_DRIVER_STUB_SOURCES driver_stub.def)
endif ()

add_library (OpenCLDriverStub ${OPENCL_DRIVER_STUB_SOURCES})

target_link_libraries (OpenCLDriverStub IcdLog)

target_compile_definitions(OpenCLDriverStub PRIVATE CL_TARGET_OPENCL_VERSION=220)
