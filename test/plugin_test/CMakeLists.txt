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
