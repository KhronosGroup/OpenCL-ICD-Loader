target_sources(OpenCL PRIVATE
    linux/icd_linux.c
    linux/icd_exports.map
)

target_compile_definitions(OpenCL PRIVATE _DEFAULT_SOURCE)
set_property(TARGET OpenCL APPEND PROPERTY
    LINK_FLAGS -Wl,--version-script="${CMAKE_CURRENT_SOURCE_DIR}/icd_exports.map"
)
set_property(TARGET OpenCL APPEND PROPERTY
    LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/icd_exports.map"
)