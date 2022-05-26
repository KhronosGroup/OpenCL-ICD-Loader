set (OPENCL_PRINT_LAYER_SOURCES
    icd_print_layer.c
    icd_print_layer.h
    icd_print_layer_generated.c)

if (WIN32)
    list (APPEND OPENCL_PRINT_LAYER_SOURCES icd_print_layer.def)
else ()
    if (NOT APPLE)
        list (APPEND OPENCL_PRINT_LAYER_SOURCES icd_print_layer.map)
    endif ()
endif ()

add_library (PrintLayer SHARED ${OPENCL_PRINT_LAYER_SOURCES})

target_include_directories(PrintLayer PRIVATE ${PARENT_DIR}/include)
target_link_libraries(PrintLayer PUBLIC OpenCL::Headers)
target_compile_definitions (PrintLayer PRIVATE CL_TARGET_OPENCL_VERSION=300)

if (NOT WIN32 AND NOT APPLE)
  set_target_properties (PrintLayer PROPERTIES LINK_FLAGS "-Wl,--version-script -Wl,${CMAKE_CURRENT_SOURCE_DIR}/icd_print_layer.map")
endif ()
