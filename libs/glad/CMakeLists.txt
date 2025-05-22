cmake_minimum_required(VERSION 3.31.7 FATAL_ERROR)

set(lib_name glad)

project(${lib_name})

add_library(${lib_name} STATIC include/glad/glad.h src/glad.c)

target_include_directories(${lib_name} PUBLIC include/)