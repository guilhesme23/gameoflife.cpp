cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(gameoflife VERSION 0.2.0)
add_executable(gameoflife src/main.cpp)
target_include_directories(gameoflife PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui)

find_package(SFML 2
COMPONENTS 
system window graphics REQUIRED)
target_link_libraries(gameoflife PUBLIC	sfml-graphics)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})


add_library(imgui lib/imgui/imgui.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_widgets.cpp lib/imgui/imgui_tables.cpp lib/imgui/imgui-SFML.cpp) 
target_link_libraries(gameoflife PUBLIC imgui GL GLU glut)