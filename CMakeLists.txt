cmake_minimum_required (VERSION 2.6)

project (OPENCL_ICD_LOADER)

# The option below allows building the ICD Loader library as a shared library
# (ON, default) or a static library (OFF).
#
# Khronos OpenCL Working Group strongly recommends building and using the ICD
# loader as a shared library due to the following benefits:
#
# 1. The shared library can be updated independent of the application. This
#    allows releasing new fixes and features in the ICD loader without updating
#    the application.
#
#    In rare cases when there are backward-incompatible changes to the ICD
#    loader (due to platform requirements, for instance), using a shared
#    library allows updating the library to make the transition seamless to
#    installed applications.
#
# 2. On platforms that require the ICD mechanism there are multiple vendors
#    shipping their OpenCL implementations. The vendor installers collaborate
#    to make sure that the installed ICD shared library version is suitable for
#    working with all vendor implementations installed on the system.
#
#    If applications statically link to ICD Loader then that version of the ICD
#    loader may not work with one or more installed vendor implementations.
#
# Using the OpenCL ICD loader as a static library is NOT recommended for
# end-user installations in general. However in some controlled environments it
# may be useful to simplify the build and distribution of the application. E.g.
# in test farms, or in cases where the end-user system configs are known in
# advance. Use it with discretion.
option (BUILD_SHARED_LIBS "Build shared libs" ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set (OPENCL_ICD_LOADER_SOURCES icd.c icd_dispatch.c)

if (WIN32)
    list (APPEND OPENCL_ICD_LOADER_SOURCES icd_windows.c icd_windows_hkr.c OpenCL.def OpenCL.rc)
    include_directories ($ENV{DXSDK_DIR}/Include)
else ()
    list (APPEND OPENCL_ICD_LOADER_SOURCES icd_linux.c icd_exports.map)
endif ()

# Change this to point to a directory containing OpenCL header directory "CL"
# OR copy OpenCL headers to ./inc/CL/
if (NOT DEFINED OPENCL_INCLUDE_DIRS)
    set (OPENCL_INCLUDE_DIRS ./inc)
endif ()

include_directories (${OPENCL_INCLUDE_DIRS})

add_library (OpenCL SHARED ${OPENCL_ICD_LOADER_SOURCES})
set_target_properties (OpenCL PROPERTIES VERSION "1.2" SOVERSION "1")

if (WIN32)
    target_link_libraries (OpenCL cfgmgr32.lib)
    string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
    string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
else()
    if (APPLE)
        set_target_properties (OpenCL PROPERTIES LINK_FLAGS "-pthread")
    else ()
        set_target_properties (OpenCL PROPERTIES LINK_FLAGS "-pthread -Wl,--version-script -Wl,${PROJECT_SOURCE_DIR}/icd_exports.map")
    endif ()
endif ()

target_link_libraries (OpenCL ${CMAKE_DL_LIBS})

enable_testing()
add_subdirectory (test)
