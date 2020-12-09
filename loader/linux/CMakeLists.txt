target_sources(OpenCL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_linux.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_linux_envvars.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_exports.map
)

target_include_directories (OpenCL PRIVATE ${PROJECT_BINARY_DIR})

target_compile_definitions(OpenCL PRIVATE _DEFAULT_SOURCE)
set_property(TARGET OpenCL APPEND PROPERTY
    LINK_FLAGS -Wl,--version-script="${CMAKE_CURRENT_SOURCE_DIR}/icd_exports.map"
)
set_property(TARGET OpenCL APPEND PROPERTY
    LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/icd_exports.map"
)

