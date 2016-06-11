cmake_minimum_required(VERSION 2.8.12)
option(COMPILE_WITH_ICC "used to compile on the HPC machines, since they don't have gcc 4.7" OFF)
if (COMPILE_WITH_ICC)
    include(CMakeForceCompiler)
    CMAKE_FORCE_C_COMPILER(icc "Intel C Compiler")
    CMAKE_FORCE_CXX_COMPILER(icpc "Intel C++ Compiler")
    CMAKE_FORCE_Fortran_COMPILER(ifort "Intel Fortran Compiler")

    if (${CMAKE_Fortran_COMPILER_ID} STREQUAL "Intel")
        if (NOT CMAKE_Fortran_FLAGS_RELEASE)
            set(CMAKE_Fortran_FLAGS_RELEASE "-O2 -xhost" CACHE STRING "" FORCE)
        endif ()
        set(CMAKE_Fortran_FLAGS_DEBUG "${CMAKE_Fortran_FLAGS_DEBUG} -check noarg_temp_created
    -C -traceback" CACHE STRING "" FORCE)
        set(CMAKE_Fortran_FLAGS_DEBUGHEAVY "${CMAKE_Fortran_FLAGS_DEBUG} -check noarg_temp_created -fpe0 -warn align
        ments -warn declarations -warn general -warn interfaces -warn truncated_source
        -warn uncalled -warn uninitialized -warn usage -common_args -warn unused -fp-st
        ack-check -check bounds -check uninit -check format" CACHE STRING "" FORCE)
        mark_as_advanced(CMAKE_Fortran_FLAGS_DEBUGHEAVY)
    endif ()
endif ()

project(RayTracer473)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -std=c++0x")

if(NOT COMPILE_WITH_ICC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-declarations -Wno-sign-compare")
endif()

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
#MESSAGE(WARNING ${resources})
file(COPY ${resources} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)
