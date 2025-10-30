
set (OPENCL_DRIVER_STUB_SOURCES cl.c cl_ext.c cl_gl.c icd.c)

if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    list (APPEND OPENCL_DRIVER_STUB_SOURCES driver_stub.def)
endif ()

add_library (OpenCLDriverStub SHARED ${OPENCL_DRIVER_STUB_SOURCES})

target_link_libraries (OpenCLDriverStub IcdLog OpenCL::Headers)

target_compile_definitions (OpenCLDriverStub PRIVATE CL_TARGET_OPENCL_VERSION=300)

set (OPENCL_DRIVER_STUB_ICD2_SOURCES cl.c cl_ext.c cl_gl.c icd.c)

if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    list (APPEND OPENCL_DRIVER_STUB_ICD2_SOURCES driver_stub.def)
endif ()

add_library (OpenCLDriverStubICD2 SHARED ${OPENCL_DRIVER_STUB_ICD2_SOURCES})

target_link_libraries (OpenCLDriverStubICD2 IcdLog OpenCL::Headers)

target_compile_definitions (OpenCLDriverStubICD2 PRIVATE CL_TARGET_OPENCL_VERSION=300 CL_ENABLE_ICD2=1)
