cmake_minimum_required(VERSION 3.15)
project(CourseCpp)
include_directories(include)
set(CMAKE_CXX_STANDARD 14)

add_executable(CourseCpp src/main.cpp src/bmp.cpp include/bmp.h src/processings_bmp.cpp include/processings_bmp.h src/menu.cpp include/menu.h)