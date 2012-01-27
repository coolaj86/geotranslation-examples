project(example Java)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_Java_LINK_EXECUTABLE "mv CMakeFiles/example.dir/example.class ./")

add_executable(example example.java)
