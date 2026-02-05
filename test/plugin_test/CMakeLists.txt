set (CL_PLUGIN_SOURCES
    cl_plugin.c)

if (WIN32)
    # For mingw-i686 builds only we need a special .def file with stdcall
    # exports.  In all other cases we can use a standard .def file.
    if ((CMAKE_SIZEOF_VOID_P EQUAL 4) AND (MINGW OR MSYS OR CYGWIN))
        list (APPEND CL_PLUGIN_SOURCES CLPlugin-mingw-i686.def)
    else ()
        list (APPEND CL_PLUGIN_SOURCES CLPlugin.def)
    endif ()
endif ()

add_library (CLPlugin MODULE ${CL_PLUGIN_SOURCES})
target_compile_definitions(CLPlugin PRIVATE CL_TARGET_OPENCL_VERSION=300)
target_link_libraries (CLPlugin OpenCL OpenCL::Headers)

set (CL_PLUGIN_LOADER_TEST_SOURCES
    cl_plugin_loader_test.c
    cl_plugin.h
    ../../loader/icd_envvars.h
    ../../loader/icd_trace.c
    ../../loader/icd_trace.h
    ../../loader/icd_library.h
)

if (WIN32)
    list (APPEND CL_PLUGIN_LOADER_TEST_SOURCES
        ../../loader/windows/icd_windows_formats.h
        ../../loader/windows/icd_windows_envvars.c
        ../../loader/windows/icd_windows_library.c)
    # Only add the DXSDK include directory if the environment variable is
    # defined.  Since the DXSDK has merged into the Windows SDK, this is
    # only required in rare cases.
    if (DEFINED ENV{DXSDK_DIR} AND NOT (MINGW OR MSYS OR CYGWIN))
        include_directories ($ENV{DXSDK_DIR}/Include)
    endif ()
else ()
    list (APPEND CL_PLUGIN_LOADER_TEST_SOURCES
        ../../loader/linux/icd_linux_envvars.c
        ../../loader/linux/icd_linux_library.c)
endif ()

add_executable(cl_plugin_loader_test ${CL_PLUGIN_LOADER_TEST_SOURCES})

add_executable(OpenCL::cl_plugin_loader_test ALIAS cl_plugin_loader_test)

target_link_libraries (cl_plugin_loader_test PUBLIC ${CMAKE_DL_LIBS})

target_include_directories (cl_plugin_loader_test
  PRIVATE
    ${CMAKE_BINARY_DIR}
    ../../loader)
