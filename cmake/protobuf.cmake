include(ExternalProject)

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
