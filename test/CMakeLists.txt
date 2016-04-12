project(RayTracer473_Test)
#get Google Test from lib and add to binary. include its sources for use in tests
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/googletest ${CMAKE_CURRENT_BINARY_DIR}/ext/googletest)
include_directories(${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)

include_directories(${JohnnyEngine2_SOURCE_DIR}/src)

add_executable(BaseTest BaseTest.cpp)
target_link_libraries(BaseTest gtest gtest_main geometry util)