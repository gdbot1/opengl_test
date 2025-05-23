cmake_minimum_required(VERSION 3.31.7 FATAL_ERROR)

set(project_name "OPENGL")

project(${project_name})

add_executable(${project_name} src/main.cpp src/vbo.cpp src/vao.cpp src/circle.cpp)

add_subdirectory(libs/glfw)

target_link_libraries(${project_name} glfw)

add_subdirectory(libs/glad)

target_link_libraries(${project_name} glad)