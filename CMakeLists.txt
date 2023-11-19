cmake_minimum_required(VERSION 3.10)

project(tcs_backbone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(BINARY ${CMAKE_PROJECT_NAME})

# add thirdparty libs
add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/spdlog")

add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/abseil")

include(cmake/protobuf.cmake)

# compile project to generate shard library
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false "${CMAKE_SOURCE_DIR}/src/*.cc")
file(GLOB_RECURSE INCLUDE LIST_DIRECTORIES false "${CMAKE_SOURCE_DIR}/src/*.h")
set(SOURCES ${SOURCES})
set(INCLUDE ${INCLUDE})

message(${SOURCES})
message(${INCLUDE})

add_library(tcs_backbone SHARED ${SOURCES})

set_target_properties(tcs_backbone PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(tcs_backbone PUBLIC ${INCLUDE})

target_link_libraries(tcs_backbone
  PUBLIC
    spdlog::spdlog
    absl::symbolize
)

# add test
enable_testing()

include(cmake/gtest.cmake)

# logging test
add_executable(logging_test)

target_sources(logging_test
  PRIVATE
    "tests/utils/logging_test.cc"
)
target_link_libraries(logging_test
  PRIVATE
    tcs_backbone
    gtest
    gtest_main
)

# add_test(logging_test logging_test)
