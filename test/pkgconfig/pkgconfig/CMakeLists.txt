cmake_minimum_required(VERSION 3.1)
find_package(PkgConfig REQUIRED)

project(PkgConfigTest
  LANGUAGES C
)

pkg_check_modules(OPENCL REQUIRED OpenCL)

if(CMAKE_VERSION VERSION_LESS 3.12)
  link_directories("${OPENCL_LIBRARY_DIRS}")
endif()

add_executable(${PROJECT_NAME}
  ../pkgconfig.c
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${OPENCL_INCLUDE_DIRS}
)

if(CMAKE_VERSION VERSION_LESS 3.12)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${OPENCL_LIBRARIES}
)
else()
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${OPENCL_LINK_LIBRARIES}
)
endif()

target_compile_options(${PROJECT_NAME}
  PRIVATE
    ${OPENCL_CFLAGS_OTHER}
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
