cmake_minimum_required(VERSION 3.3)

project(Hunta2)

# Copy game data (imgs/maps etc) to the build dir
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# Copy fonts used to build dir
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/freefont DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# Compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11 -I/usr/include/lua5.1 -Wall -pedantic")

add_subdirectory(src/ui)
add_subdirectory(src/components)
add_subdirectory(src/tools)
add_subdirectory(src/physics)
add_subdirectory(src/scripting)
add_subdirectory(src)