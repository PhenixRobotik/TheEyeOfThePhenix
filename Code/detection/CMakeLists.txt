cmake_minimum_required(VERSION 2.8)
project( Detect )
find_package( OpenCV REQUIRED )
add_executable( Detect detect.cpp )
target_link_libraries( Detect ${OpenCV_LIBS} )

add_executable( Detect_cam detect_cam.cpp )
target_link_libraries( Detect_cam ${OpenCV_LIBS} )
