cmake_minimum_required (VERSION 3.1)

project (OpenCL-ICD-Loader VERSION 1.2)
include (GNUInstallDirs)
find_package (Threads REQUIRED)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
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

# This option enables/disables support for OpenCL layers in the ICD loader.
# It is currently needed default while the specification is being formalized,
# and to study the performance impact.
option (ENABLE_OPENCL_LAYERS "Enable OpenCL Layers" ON)

include(CheckFunctionExists)
check_function_exists(secure_getenv HAVE_SECURE_GETENV)
check_function_exists(__secure_getenv HAVE___SECURE_GETENV)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/loader/icd_cmake_config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/icd_cmake_config.h)

set (OPENCL_ICD_LOADER_SOURCES
    loader/icd.c
    loader/icd.h
    loader/icd_dispatch.c
    loader/icd_dispatch.h
    loader/icd_dispatch_generated.c
    loader/icd_envvars.h
    loader/icd_platform.h)

if (WIN32)
    list (APPEND OPENCL_ICD_LOADER_SOURCES 
        loader/windows/adapter.h
        loader/windows/icd_windows.c
        loader/windows/icd_windows.h
        loader/windows/icd_windows_dxgk.c
        loader/windows/icd_windows_dxgk.h
        loader/windows/icd_windows_envvars.c
        loader/windows/icd_windows_hkr.c
        loader/windows/icd_windows_hkr.h
        loader/windows/icd_windows_apppackage.cpp
        loader/windows/icd_windows_apppackage.h
        loader/windows/OpenCL.def
        loader/windows/OpenCL.rc)
    # Only add the DXSDK include directory if the environment variable is
    # defined.  Since the DXSDK has merged into the Windows SDK, this is
    # only required in rare cases.
    if (DEFINED ENV{DXSDK_DIR} AND NOT (MINGW OR MSYS OR CYGWIN))
        include_directories ($ENV{DXSDK_DIR}/Include)
    endif ()
else ()
    list (APPEND OPENCL_ICD_LOADER_SOURCES
        loader/linux/icd_linux.c
        loader/linux/icd_linux_envvars.c
        loader/linux/icd_exports.map)
endif ()

set (OPENCL_ICD_LOADER_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc CACHE PATH "Path to OpenCL Headers")

add_library (OpenCL ${OPENCL_ICD_LOADER_SOURCES})
set_target_properties (OpenCL PROPERTIES VERSION "1.2" SOVERSION "1")
target_include_directories(OpenCL SYSTEM PUBLIC ${OPENCL_ICD_LOADER_HEADERS_DIR})
target_include_directories(OpenCL PRIVATE include)


if (WIN32)
    target_link_libraries (OpenCL cfgmgr32.lib runtimeobject.lib)

    option (OPENCL_ICD_LOADER_DISABLE_OPENCLON12 "Disable support for OpenCLOn12. Support for OpenCLOn12 should only be disabled when building an import lib to link with, and must be enabled when building an ICD loader for distribution!" OFF)
    if (OPENCL_ICD_LOADER_DISABLE_OPENCLON12)
        target_compile_definitions(OpenCL PRIVATE OPENCL_ICD_LOADER_DISABLE_OPENCLON12)
    endif()

    if(NOT USE_DYNAMIC_VCXX_RUNTIME)
        string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
        string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL}")
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}")
        string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO}")
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
        string(REPLACE "/MDd" "/MTd" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
        string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    endif()
else()
    if (APPLE)
        target_link_libraries (OpenCL ${CMAKE_THREAD_LIBS_INIT})
    else ()
        set_target_properties (OpenCL PROPERTIES LINK_FLAGS "-Wl,--version-script -Wl,${CMAKE_CURRENT_SOURCE_DIR}/loader/linux/icd_exports.map")
        if (OPENCL_ICD_LOADER_PIC)
            set_target_properties(OpenCL PROPERTIES POSITION_INDEPENDENT_CODE ON)
        endif ()
        target_link_libraries (OpenCL ${CMAKE_THREAD_LIBS_INIT})
    endif ()
endif ()

include_directories (${OPENCL_ICD_LOADER_HEADERS_DIR})
add_definitions (-DCL_TARGET_OPENCL_VERSION=300)

if (ENABLE_OPENCL_LAYERS)
    add_definitions (-DCL_ENABLE_LAYERS)
endif ()

target_include_directories (OpenCL PRIVATE ${CMAKE_CURRENT_BINARY_DIR} loader)
target_link_libraries (OpenCL ${CMAKE_DL_LIBS})

option (OPENCL_ICD_LOADER_BUILD_TESTING "Enable support for OpenCL ICD Loader testing." OFF)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR OPENCL_ICD_LOADER_BUILD_TESTING)
    include(CTest)
endif()
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR OPENCL_ICD_LOADER_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory (test)
endif()

install (TARGETS OpenCL
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
