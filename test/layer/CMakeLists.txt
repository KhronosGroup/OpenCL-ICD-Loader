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

add_library (PrintLayer ${OPENCL_PRINT_LAYER_SOURCES})

if (NOT WIN32 AND NOT APPLE)
  set_target_properties (PrintLayer PROPERTIES LINK_FLAGS "-Wl,--version-script -Wl,${CMAKE_CURRENT_SOURCE_DIR}/icd_print_layer.map")
endif ()
