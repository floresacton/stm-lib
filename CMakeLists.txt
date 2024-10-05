# CMakeLists.txt for the object library
cmake_minimum_required(VERSION 3.12)
project(stm-lib)

# Create the object library
add_library(stm_obj_lib OBJECT Src/bitmap.c)

