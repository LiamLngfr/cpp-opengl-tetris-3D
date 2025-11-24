cmake_minimum_required(VERSION 3.5)

project(OpenGL_Corrige LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES
    "*.cpp"
    "*.h")

add_executable(OpenGL_TP ${SRC_FILES})

target_include_directories(OpenGL_TP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(OpenGL_TP glfw GLEW libGLEW.so libGLU.so libGL.so)
