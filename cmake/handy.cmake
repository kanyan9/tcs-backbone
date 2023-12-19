include(ExternalProject)
include(GNUInstallDirs)

set(HANDY_DIR
    "${PROJECT_SOURCE_DIR}/third_party/handy"
    CACHE STRING "handy directory")
set(HANDY_BUILD_DIR ${PROJECT_BINARY_DIR}/third_party/handy)

ExternalProject_Add(
  handy 
  SOURCE_DIR ${HANDY_DIR}
  PREFIX ${HANDY_BUILD_DIR}
  CMAKE_ARGS -DCMAKE_C_COMPILER_LAUNCHER=${CMAKE_C_COMPILER_LAUNCHER}
             -DCMAKE_CXX_COMPILER_LAUNCHER=${CMAKE_CXX_COMPILER_LAUNCHER}
             -DCMAKE_BUILD_TYPE=release
             -DCMAKE_INSTALL_PREFIX=/usr/local/
             -DBUILD_HANDY_EXAMPLES=OFF
             -DBUILD_HANDY_SHARED_LIBRARY=OFF
             -DCMAKE_HOST_UNIX=ON
             -DCMAKE_POSITION_INDEPENDENT_CODE=ON)
