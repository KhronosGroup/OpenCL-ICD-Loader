cmake_minimum_required(VERSION 3.0)

project(PkgConfigTest
  LANGUAGES C
)

find_package(OpenCLHeaders
  REQUIRED
  CONFIG
)
find_package(OpenCLICDLoader
  REQUIRED
  CONFIG
)

add_executable(${PROJECT_NAME}
  ../pkgconfig.c
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    OpenCL::Headers
    OpenCL::OpenCL
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    CL_TARGET_OPENCL_VERSION=120
)

include(CTest)

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
)

set_tests_properties(${PROJECT_NAME}
  PROPERTIES
    ENVIRONMENT "OCL_ICD_FILENAMES=${DRIVER_STUB_PATH}"
)
