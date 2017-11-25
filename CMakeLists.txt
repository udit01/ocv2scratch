cmake_minimum_required(VERSION 2.8)


set (Intro_VERSION_MAJOR 1)
set (Intro_VERSION_MINOR 0)
 

project( intro )
find_package( OpenCV REQUIRED )
#TARGET_LINK_LIBRARIES( project ${OpenCV_LIBS} )


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

#experiment after
#add_dependencies(simple.out ver.out )
#target_link_libraries( simple.out ${OpenCV_LIBS} ${CMAKE_SOURCE_DIR}/simple.cpp)

add_executable( read.out imreading.cpp )
target_link_libraries( read.out ${OpenCV_LIBS} )

add_executable( bgrTg.out bgrToGray.cpp )
target_link_libraries( bgrTg.out ${OpenCV_LIBS} )
