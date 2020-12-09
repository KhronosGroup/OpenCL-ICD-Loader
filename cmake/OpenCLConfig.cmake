list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Modules")

include(CMakeFindDependencyMacro)
find_dependency(Threads REQUIRED)
find_dependency(OpenCLHeaders REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/OpenCLTargets.cmake")
