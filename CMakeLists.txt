cmake_minimum_required(VERSION 3.23)
project(Cpp_OpenCV)

set(CMAKE_CXX_STANDARD 14)


#find_library(OpenCV)
SET(OpenCV_INCLUDE_DIR -L/usr/local/opt/opencv@3/lib)
SET(OpenCV_INCLUDE_DIR -I/usr/local/opt/opencv@3/include)

    find_package(OpenCV)
#IF (OpenCV_FOUND)
include_directories(${OpenCV_INCLUDE_DIRS})
#ENDIF()

set(CMAKE_CXX_STANDARD 14)

add_executable(Cpp_OpenCV main.cpp)

target_link_libraries(Cpp_OpenCV ${OpenCV_LIBS})