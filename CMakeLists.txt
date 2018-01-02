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

# add the binary tree to the search path for include files ?  wut?
# so that we will find IntroConfig.h
include_directories("${PROJECT_BINARY_DIR}")


# add the executables
#add_executable( version.out version.cpp )
#target_link_libraries(version.out ${OpenCV_LIBS})
#add_executable( simple.out version.cpp simple.cpp)
#target_link_libraries( simple.out ${OpenCV_LIBS} )
#add_executable( read.out imreading.cpp )
#target_link_libraries( read.out ${OpenCV_LIBS} )
#add_executable( bgrTg.out bgrToGray.cpp )
#target_link_libraries( bgrTg.out ${OpenCV_LIBS} )
#add_executable( t.out traverseImages.cpp )
#target_link_libraries( t.out ${OpenCV_LIBS} )
#add_executable( m.out mask.cpp )
#target_link_libraries( m.out ${OpenCV_LIBS} )
#add_executable( split.out split.cpp )
#target_link_libraries( split.out ${OpenCV_LIBS} )
#add_executable( em.out extractMetrics.cpp )
#target_link_libraries( em.out ${OpenCV_LIBS} )
add_executable( d.out draw.cpp )
target_link_libraries( d.out ${OpenCV_LIBS} )


#experiment after
#add_dependencies(simple.out ver.out )
#target_link_libraries( simple.out ${OpenCV_LIBS} ${CMAKE_SOURCE_DIR}/simple.cpp)

#add_executable( plot.out plot.cpp )
#target_link_libraries( plot.out ${OpenCV_LIBS} )

# g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o binaryName  main.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy
# g++ `pkg-config --cflags --libs opencv` IntroConfig.h version.cpp simple.cpp
# etc