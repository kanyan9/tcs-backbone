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

include(cmake/handy.cmake)

# compile project to generate shard library
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false "${CMAKE_SOURCE_DIR}/src/*.cc")
file(GLOB_RECURSE INCLUDE LIST_DIRECTORIES false "${CMAKE_SOURCE_DIR}/src/*.h")
set(SOURCES ${SOURCES})
set(INCLUDE ${INCLUDE})

# add protobuf compile file
file(GLOB_RECURSE PROTO_FILES RELATIVE ${CMAKE_SOURCE_DIR} "src/protobuf/*.proto")
protobuf_generate_cpp_with_root(PROTO_SRCS PROTO_HDRS ${CMAKE_SOURCE_DIR}
                                ${PROTO_FILES})
list(APPEND SOURCES ${PROTO_SRCS})
list(APPEND INCLUDE ${PROTO_HDRS})

message(${SOURCES})
message(${INCLUDE})

add_library(tcs_backbone STATIC ${SOURCES})

set_target_properties(tcs_backbone PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(tcs_backbone PUBLIC ${INCLUDE})

# add "packet.pb.h"
target_include_directories(tcs_backbone
                           PRIVATE
                           ${CMAKE_CURRENT_BINARY_DIR}/protobuf)

target_link_libraries(tcs_backbone
  PUBLIC
    spdlog::spdlog
    absl::symbolize
    libprotobuf
    handy_s
)

if(TCS_WITH_TEST)
  include(cmake/gtest.cmake)

  add_subdirectory(test)
endif()
