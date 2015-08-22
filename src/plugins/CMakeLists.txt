cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(plugins)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

find_package(gazebo REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp
  DEPENDS system_lib
)

include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

add_library(hello_world SHARED hello_world.cc)
target_link_libraries(hello_world ${GAZEBO_LIBRAIRIES})
