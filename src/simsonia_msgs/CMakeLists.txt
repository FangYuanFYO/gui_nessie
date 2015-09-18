# \file CMakeLists.txt
# \author Thomas Fuhrmann <tomesman@gmail.com>
# \date 18/09/2015
# \copyright  2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>

#===============================================================================
# C M A K E   C O N F I G U R A T I O N

cmake_minimum_required(VERSION 2.8.3)
project(simsonia_msgs)

#===============================================================================
# C A T K I N   P A C K A G E S

find_package(catkin REQUIRED COMPONENTS
  std_msgs
  std_srvs
  message_generation
)

#===============================================================================
# G E N E R A T E   M E S S A G E S

add_message_files(
  DIRECTORY msg
  FILES
  auv7_motor_control.msg
)

#===============================================================================
# G E N E R A T E   S E R V I C E S

## Generate services in the 'srv' folder
#add_service_files(
#  DIRECTORY srv
#  FILES
#  todo.srv
#)

#===============================================================================
# G E N E R A T E   M E S S A G E S

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
   std_msgs
)

#===============================================================================
# O T H E R   P A C K A G E S

catkin_package(
 CATKIN_DEPENDS
 message_runtime
 std_msgs
 std_srvs
 message_generation
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
#include_directories(
#  ${catkin_INCLUDE_DIRS}
#)
