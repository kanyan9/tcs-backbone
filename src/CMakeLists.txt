file(
  GLOB_RECURSE
  SOURCES
  transport/*.cc
  utils/*.cc
)

file(
  GLOB_RECURSE
  INC
  transport/*.h
  utils/*.h
  common/*.h
)

file(
  GLOB_RECURSE PROTO_FILES
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  "protobuf/*.proto"
)

protobuf_generate_cpp_with_root(PROTO_SRCS PROTO_HDRS ${CMAKE_CURRENT_SOURCE_DIR}
                                ${PROTO_FILES})
add_custom_target(tcs_proto_target DEPENDS ${PROTO_SRCS} ${PROTO_HDRS}
                  ${PROTOBUF_PROTOC_EXECUTABLE})
# list(APPEND INCLUDE ${PROTO_HDRS})
list(APPEND SOURCES ${PROTO_SRCS})

# compile project to generate static library
add_library(tcs_backbone STATIC ${SOURCES})

# set(CMAKE_CXX_FLAGS "-Wl,--verbose")

set_target_properties(tcs_backbone PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(tcs_backbone PUBLIC ${INC})

target_include_directories(
  tcs_backbone
  PRIVATE 
  "${PROJECT_BINARY_DIR}/third_party/handy/include/"
)

target_link_libraries(
  tcs_backbone
  PRIVATE 
  handy_s
)

# for including .pb.h
target_include_directories(
  tcs_backbone
  PRIVATE
  "${CMAKE_CURRENT_BINARY_DIR}/protobuf"
)

add_dependencies(tcs_backbone tcs_proto_target)

target_link_libraries(
  tcs_backbone
  PRIVATE
  libprotobuf
)

target_link_libraries(tcs_backbone
  PRIVATE
  spdlog::spdlog
  absl::symbolize
)
