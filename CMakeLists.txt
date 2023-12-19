cmake_minimum_required(VERSION 3.19)

project(tcs_backbone)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# add third_party libs
add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/spdlog")

add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/abseil")

include(cmake/protobuf.cmake)

include(cmake/handy.cmake)

add_subdirectory(src)

if(TCS_WITH_TEST)
  include(cmake/gtest.cmake)
  add_subdirectory(test)
endif()
