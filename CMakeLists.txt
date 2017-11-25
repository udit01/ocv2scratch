cmake_minimum_required(VERSION 2.8)

project( intro )

set (Intro_VERSION_MAJOR 1)
set (Intro_VERSION_MINOR 0)
 
find_package( OpenCV REQUIRED )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/IntroConfig.h.in"
  "${PROJECT_BINARY_DIR}/IntroConfig.h"
  )

# add the binary tree to the search path for include files ?
# so that we will find IntroConfig.h
include_directories("${PROJECT_BINARY_DIR}")
 
# add the executables
add_executable( version.out version.cpp )
target_link_libraries(version.out ${OpenCV_LIBS})


add_executable( simple.out simple.cpp)
target_link_libraries( simple.out ${OpenCV_LIBS} )


#add_dependencies(simple.out ver.out )
#target_link_libraries( simple.out ${OpenCV_LIBS} ${CMAKE_SOURCE_DIR}/simple.cpp)

add_executable( read.out imreading.cpp )
target_link_libraries( read.out ${OpenCV_LIBS} )