cmake_minimum_required(VERSION 2.8)
project(haversine)
project(translate2d)
project(translate3d)

add_executable(haversine haversine.c translateFns.c)
add_executable(translate2d translate2d.c translateFns.c)
add_executable(translate3d translate3d.c translateFns.c)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_C_FLAGS "-Wall -Werror" CACHE STRING "" FORCE)
endif(CMAKE_COMPILER_IS_GNUCXX)

if(UNIX)
  target_link_libraries(haversine m)
  target_link_libraries(translate2d m)
  target_link_libraries(translate3d m)
endif(UNIX)
