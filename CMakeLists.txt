cmake_minimum_required(VERSION 3.10)

project(tcs_backbone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})
add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

add_subdirectory("${CMAKE_SOURCE_DIR}/test")

add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/spdlog")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog/src/*.cpp")
add_library(log SHARED ${SOURCES})
target_include_directories(log PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(log PRIVATE spdlog::spdlog)

add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/abseil")