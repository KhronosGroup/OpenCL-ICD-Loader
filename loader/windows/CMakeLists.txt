target_sources(OpenCL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_windows.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_windows.h
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_windows_dxgk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_windows_dxgk.h
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_windows_envvars.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_windows_hkr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_windows_hkr.h
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL.def
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL.rc
)

# Only add the DXSDK include directory if the environment variable is
# defined.  Since the DXSDK has merged into the Windows SDK, this is
# only required in rare cases.
if (DEFINED ENV{DXSDK_DIR} AND NOT (MINGW OR MSYS OR CYGWIN))
    target_include_directories(OpenCL PRIVATE $ENV{DXSDK_DIR}/Include)
endif ()

target_link_libraries(OpenCL PUBLIC cfgmgr32)

option (OPENCL_ICD_LOADER_REQUIRE_WDK "Build with D3DKMT support, which requires the Windows WDK." ON)
    if (OPENCL_ICD_LOADER_REQUIRE_WDK)
        if(DEFINED ENV{WDKContentRoot})
            file(GLOB D3DKMT_HEADER "$ENV{WDKContentRoot}/Include/*/km/d3dkmthk.h")
        else()
            file(GLOB D3DKMT_HEADER "$ENV{HOMEDRIVE}/Program Files */Windows Kits/10/Include/*/km/d3dkmthk.h")
        endif()

        if(D3DKMT_HEADER)
            list(GET D3DKMT_HEADER -1 LATEST_D3DKMT_HEADER)
            get_filename_component(WDK_DIRECTORY ${LATEST_D3DKMT_HEADER} DIRECTORY)
            get_filename_component(WDK_DIRECTORY ${WDK_DIRECTORY} DIRECTORY)
            message(STATUS "Found the Windows WDK in: ${WDK_DIRECTORY}")
            target_compile_definitions(OpenCL PRIVATE OPENCL_ICD_LOADER_REQUIRE_WDK)
            target_include_directories(OpenCL PRIVATE ${WDK_DIRECTORY}/um)
            target_include_directories(OpenCL PRIVATE ${WDK_DIRECTORY}/km)
            target_include_directories(OpenCL PRIVATE ${WDK_DIRECTORY}/shared)
        else()
            message(FATAL_ERROR "The Windows WDK was not found. Consider disabling OPENCL_ICD_LOADER_REQUIRE_WDK. Aborting.")
        endif()
    endif()

