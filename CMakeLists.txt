cmake_minimum_required(VERSION 3.0.2)
project(RayTracer473)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

#general cmake output organization
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#link 3rd party libraries
find_package(Eigen REQUIRED)
include_directories(${EIGEN_INCLUDE_DIRS})

set(ext_libraries "")
add_subdirectory(src)
add_subdirectory(test)

#lastly, jam all the resources into whereever cmake build this to
#todo, see if there is better way than globbing all the resrouces. Will have to rebuild everytime with current setup
file(GLOB_RECURSE resources RELATIVE ${CMAKE_SOURCE_DIR} res/*)
MESSAGE(WARNING ${resources})
file(COPY ${resources} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)
