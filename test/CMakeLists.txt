set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

file(GLOB_RECURSE SOURCES *.cc)

add_executable(tcs_backbone_test ${SOURCES})

target_link_libraries(tcs_backbone_test tcs_backbone)
target_link_libraries(tcs_backbone_test gtest gmock)
