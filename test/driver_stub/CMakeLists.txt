
set (OPENCL_DRIVER_STUB_SOURCES cl.c cl_ext.c cl_gl.c icd.c)

if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    list (APPEND OPENCL_DRIVER_STUB_SOURCES driver_stub.def)
endif ()

if (${OPENCL_ICD_LOADER_BUILD_SHARED_LIBS})
    add_library (OpenCLDriverStub SHARED ${OPENCL_DRIVER_STUB_SOURCES})
else()
    add_library (OpenCLDriverStub STATIC ${OPENCL_DRIVER_STUB_SOURCES})
endif()

target_link_libraries (OpenCLDriverStub IcdLog OpenCL::Headers)

target_compile_definitions (OpenCLDriverStub PRIVATE CL_TARGET_OPENCL_VERSION=300)
