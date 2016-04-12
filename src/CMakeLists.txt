#first, make sure that stuff can link directly to here without appending source
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


#macro to get all the subdirectory names. from:
#http://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
macro(MACRO_SUBDIRLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

MACRO_SUBDIRLIST(src_libraries ${CMAKE_CURRENT_SOURCE_DIR})

foreach(src_library ${src_libraries})
    add_subdirectory(${src_library})
endforeach()


MESSAGE(WARNING ${src_libraries})


add_executable(RayTracer473 main.cpp)

target_link_libraries(RayTracer473 ${ext_libraries} ${src_libraries})