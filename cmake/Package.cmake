set(CPACK_PACKAGE_VENDOR "khronos")

set(CPACK_DEBIAN_DESCRIPTION "Khronos OpenCL ICD Loader")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

if(NOT CPACK_PACKAGING_INSTALL_PREFIX)
  set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
endif()

# Configuring pkgconfig

# We need two different instances of OpenCL.pc
# One for installing (cmake --install), which contains CMAKE_INSTALL_PREFIX as prefix
# And another for the Debian development package, which contains CPACK_PACKAGING_INSTALL_PREFIX as prefix

join_paths(OPENCL_INCLUDEDIR_PC "\${prefix}" "${CMAKE_INSTALL_INCLUDEDIR}")
join_paths(OPENCL_LIBDIR_PC "\${exec_prefix}" "${INSTALL_LIBDIR}")

set(pkg_config_location ${INSTALL_LIBDIR}/pkgconfig)
set(PKGCONFIG_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Configure and install OpenCL.pc for installing the project
configure_file(
  OpenCL.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/pkgconfig_install/OpenCL.pc
  @ONLY)
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/pkgconfig_install/OpenCL.pc
  DESTINATION ${pkg_config_location}
  COMPONENT pkgconfig_install)

# Configure and install OpenCL.pc for the Debian package
set(PKGCONFIG_PREFIX "${CPACK_PACKAGING_INSTALL_PREFIX}")
configure_file(
  OpenCL.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/pkgconfig_package/OpenCL.pc
  @ONLY)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/pkgconfig_package/OpenCL.pc
  DESTINATION ${pkg_config_location}
  COMPONENT dev
  EXCLUDE_FROM_ALL)

# DEB packaging configuration
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_VENDOR})

set(CPACK_DEBIAN_PACKAGE_HOMEPAGE
    "https://github.com/KhronosGroup/OpenCL-ICD-Loader")

# Version number [epoch:]upstream_version[-debian_revision]
set(CPACK_DEBIAN_PACKAGE_VERSION "${PROJECT_VERSION}") # upstream_version
set(CPACK_DEBIAN_PACKAGE_RELEASE "1") # debian_revision (because this is a
                                      # non-native pkg)
set(PACKAGE_VERSION_REVISION "${CPACK_DEBIAN_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_RELEASE}")

# Get architecture
execute_process(COMMAND dpkg "--print-architecture" OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE)
string(STRIP "${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}" CPACK_DEBIAN_PACKAGE_ARCHITECTURE)

##########################################################
#                       Components                       #
##########################################################

set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL runtime dev)

set(DEBIAN_FILE_NAME "ocl-icd")

## Package runtime component
set(DEBIAN_RUNTIME_PACKAGE_SUFIX "libopencl1")
set(CPACK_DEBIAN_RUNTIME_PACKAGE_NAME
    "${DEBIAN_FILE_NAME}-${DEBIAN_RUNTIME_PACKAGE_SUFIX}"
    CACHE STRING "Package name" FORCE)

# Package file name in deb format:
# <PackageName>_<VersionNumber>-<DebianRevisionNumber>_<DebianArchitecture>.deb
set(CPACK_DEBIAN_RUNTIME_FILE_NAME "${CPACK_DEBIAN_RUNTIME_PACKAGE_NAME}_${PACKAGE_VERSION_REVISION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")

# Dependencies
set(CPACK_DEBIAN_RUNTIME_PACKAGE_DEPENDS "libc6")


## Package dev component
set(DEBIAN_DEV_PACKAGE_SUFIX "opencl-dev")
set(CPACK_DEBIAN_DEV_PACKAGE_NAME
    "${DEBIAN_FILE_NAME}-${DEBIAN_DEV_PACKAGE_SUFIX}"
    CACHE STRING "Package name" FORCE)

# Package file name in deb format:
# <PackageName>_<VersionNumber>-<DebianRevisionNumber>_<DebianArchitecture>.deb
set(CPACK_DEBIAN_DEV_FILE_NAME "${CPACK_DEBIAN_DEV_PACKAGE_NAME}_${PACKAGE_VERSION_REVISION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}.deb")

# Dependencies
set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON) # Component dependencies are reflected in package relationships
set(CPACK_DEBIAN_DEV_PACKAGE_DEPENDS "opencl-c-headers")
set(CPACK_COMPONENT_DEV_DEPENDS runtime)

set(CPACK_DEBIAN_PACKAGE_DEBUG ON)

include(CPack)
