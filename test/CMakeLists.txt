include_directories (./inc)

add_subdirectory (log)
add_subdirectory (driver_stub)
add_subdirectory (loader_test)
if (ENABLE_OPENCL_LAYERS)
    add_subdirectory (layer)
endif ()

set_target_properties (IcdLog OpenCLDriverStub icd_loader_test
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
add_test (
    NAME opencl_icd_loader_test
    COMMAND icd_loader_test
)

if (ENABLE_OPENCL_LAYERINFO)
    add_test (
        NAME cllayerinfo_test
        COMMAND cllayerinfo
    )
endif ()

get_property(GENERATOR_IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (GENERATOR_IS_MULTI_CONFIG)
    set (TEST_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
else ()
    set (TEST_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()

set_tests_properties(opencl_icd_loader_test
    PROPERTIES
        ENVIRONMENT OCL_ICD_FILENAMES=$<TARGET_FILE:OpenCLDriverStub>
        WORKING_DIRECTORY "${TEST_WORKING_DIRECTORY}"
)
if (ENABLE_OPENCL_LAYERINFO)
    set_tests_properties(cllayerinfo_test
        PROPERTIES
            ENVIRONMENT OPENCL_LAYERS=$<TARGET_FILE:PrintLayer>
            WORKING_DIRECTORY "${TEST_WORKING_DIRECTORY}"
    )
endif()
