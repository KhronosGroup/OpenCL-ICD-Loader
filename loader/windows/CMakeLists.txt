target_sources(OpenCL PRIVATE
    windows/icd_windows.c
    windows/icd_windows_hkr.c
    windows/OpenCL.def
    windows/OpenCL.rc
)

# Only add the DXSDK include directory if the environment variable is
# defined.  Since the DXSDK has merged into the Windows SDK, this is
# only required in rare cases.
if (DEFINED ENV{DXSDK_DIR} AND NOT (MINGW OR MSYS OR CYGWIN))
    target_include_directories(OpenCL PRIVATE $ENV{DXSDK_DIR}/Include)
endif ()

target_link_libraries(OpenCL PUBLIC cfgmgr32)