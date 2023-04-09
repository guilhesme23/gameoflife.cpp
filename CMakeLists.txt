cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(gameoflife VERSION 0.2.0)
add_executable(gameoflife src/main.cpp) 

find_package(SFML 2
  COMPONENTS 
    system window graphics REQUIRED)
target_link_libraries(gameoflife PUBLIC	sfml-graphics)
