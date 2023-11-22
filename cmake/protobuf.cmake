function(protobuf_generate_cpp_with_root SRCS HDRS ROOT_DIR)
  if(NOT ARGN)
    message(
      SEND_ERROR
        "Error: protobuf_generate_cpp_with_root() called without any proto files")
    return()
  endif()

  set(${SRCS})
  set(${HDRS})

  foreach(FIL ${ARGN})
    set(ABS_FIL ${ROOT_DIR}/${FIL})
    get_filename_component(FIL_WE ${FIL} NAME_WE)
    get_filename_component(FIL_DIR ${ABS_FIL} PATH)
    file(RELATIVE_PATH REL_DIR ${ROOT_DIR} ${FIL_DIR})

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/protobuf")
    set(PROTO_GENERATE_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/protobuf")

    list(APPEND ${SRCS} "${PROTO_GENERATE_OUT_DIR}/${FIL_WE}.pb.cc")
    list(APPEND ${HDRS} "${PROTO_GENERATE_OUT_DIR}/${FIL_WE}.pb.h")

    add_custom_command(
      OUTPUT "${PROTO_GENERATE_OUT_DIR}/${FIL_WE}.pb.cc"
             "${PROTO_GENERATE_OUT_DIR}/${FIL_WE}.pb.h"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ARGS --cpp_out
              ${PROTO_GENERATE_OUT_DIR}
              -I ${FIL_DIR} ${ABS_FIL} -I ${PROTOBUF_INCLUDE_DIRS}
      DEPENDS ${ABS_FIL} libprotobuf
      COMMENT "Running C++ protocol buffer compiler on ${FIL}"
      VERBATIM)
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS}
      ${${SRCS}}
      PARENT_SCOPE)
  set(${HDRS}
      ${${HDRS}}
      PARENT_SCOPE)
endfunction()


include(ExternalProject)
include(GNUInstallDirs)

set(PROTOBUF_DIR
    "${PROJECT_SOURCE_DIR}/third_party/protobuf"
    CACHE STRING "protobuf directory")
set(PROTOBUF_BUILD_DIR ${PROJECT_BINARY_DIR}/third_party/protobuf)
set(PROTOBUF_LIB ${PROTOBUF_BUILD_DIR}/${CMAKE_INSTALL_LIBDIR}/libprotobuf.a)
set(PROTOBUF_PROTOC_EXECUTABLE ${PROTOBUF_BUILD_DIR}/bin/protoc)


ExternalProject_Add(
  protobuf
  SOURCE_DIR ${PROTOBUF_DIR}
  PREFIX ${PROTOBUF_BUILD_DIR}
  CMAKE_ARGS -DCMAKE_C_COMPILER_LAUNCHER=${CMAKE_COMPILER_LAUNCHER}
             -DCMAKE_CXX_COMPILER_LAUNCHER=${CMAKE_CXX_COMPILER_LAUNCHER}
             -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
             -DCMAKE_INSTALL_PREFIX=${PROTOBUF_BUILD_DIR}
             -Dprotobuf_BUILD_EXAMPLES=OFF
             -Dprotobuf_BUILD_TESTS=OFF
             -DBUILD_SHARED_LIBS=OFF
             -DCMAKE_POSITION_INDEPENDENT_CODE=ON
  BUILD_BYPRODUCTS ${PROTOBUF_LIB} ${PROTOBUF_PROTOC_EXECUTABLE})

set(PROTOBUF_INC ${PROTOBUF_BUILD_DIR}/include)
file(MAKE_DIRECTORY ${PROTOBUF_INC})

add_library(libprotobuf STATIC IMPORTED GLOBAL)
add_dependencies(libprotobuf protobuf)
set_target_properties(
  libprotobuf PROPERTIES IMPORTED_LOCATION ${PROTOBUF_LIB}
                         INTERFACE_INCLUDE_DIRECTORIES ${PROTOBUF_BUILD_DIR}/include)

add_executable(protoc IMPORTED GLOBAL)
add_dependencies(protoc protobuf)
set_target_properties(protoc PROPERTIES IMPORTED_LOCATION
                                         ${PROTOBUF_BUILD_DIR}/bin/protoc)

set(PROTOBUF_ROOT ${PROTOBUF_BUILD_DIR})
set(PROTOBUF_PROTOC_EXECUTABLE protoc)
set(PROTOBUF_INCLUDE_DIRS ${PROTOBUF_BUILD_DIR}/include)