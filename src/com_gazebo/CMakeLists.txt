#fichier cmake avec les éléments minimals pour utiliser le package ROS gazebo_ros
#le cmake est dérivé de celui des tuto ROS sur les services

cmake_minimum_required(VERSION 2.8.3)
project(com_gazebo)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
  gazebo_msgs
)

find_package(gazebo)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(FILES Num.msg)

## Generate services in the 'srv' folder
add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services with any dependencies listed here
generate_messages(DEPENDENCIES std_msgs gazebo_msgs)

###################################
## catkin specific configuration ##
###################################

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS roscpp gazebo_msgs
    DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(include ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

## Mes déclarations
add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})
add_dependencies(talker beginner_tutorials_generate_messages_cpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})
add_dependencies(listener beginner_tutorials_generate_messages_cpp)
