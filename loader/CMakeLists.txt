find_package (Threads REQUIRED)
find_package (OpenCLHeaders REQUIRED)

add_library(OpenCL
    ${CMAKE_CURRENT_SOURCE_DIR}/icd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd.h
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_dispatch.c
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_dispatch.h
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_envvars.h
    ${CMAKE_CURRENT_SOURCE_DIR}/icd_platform.h
)

set_target_properties(OpenCL PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION}
)

target_link_libraries(OpenCL
    PUBLIC Threads::Threads OpenCL::OpenCLHeaders ${CMAKE_DL_LIBS})
target_compile_definitions(OpenCL PRIVATE CL_TARGET_OPENCL_VERSION=220)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_subdirectory(windows)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_subdirectory(linux)
endif()

install (TARGETS OpenCL EXPORT OpenCLTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if (UNIX)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/OpenCL.pc.in
        ${CMAKE_CURRENT_BINARY_DIR}/OpenCL.pc.configured
        @ONLY)
    file(GENERATE
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/OpenCL.pc
      INPUT ${CMAKE_CURRENT_BINARY_DIR}/OpenCL.pc.configured)
    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/OpenCL.pc DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
endif()

