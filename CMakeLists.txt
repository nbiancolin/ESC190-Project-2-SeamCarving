cmake_minimum_required(VERSION 3.24)
project(ESC190_Project_2_SeamCarving C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(ESC190_Project_2_SeamCarving
        seamcarving.c
        seamcarving.h c_img.c)
