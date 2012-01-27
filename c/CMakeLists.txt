cmake_minimum_required(VERSION 2.8)
project(example)

add_executable(example example.c)

if(UNIX)
  target_link_libraries(example m)
endif(UNIX)
