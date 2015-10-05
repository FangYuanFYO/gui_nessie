# \file	CMakeLists.txt
# \author	Thomas Fuhrmann <tomesman@gmail.com>
# \date	19/09/2015
# \copyright	2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>

#===============================================================================
# C M A K E   C O N F I G U R A T I O N

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(nessie_ros)

#===============================================================================
# C A T K I N   P A C K A G E S

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rosconsole
)

#===============================================================================
# OTHER PACKAGES

find_package(gazebo REQUIRED
			Boost REQUIRED COMPONENTS system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

catkin_package(
  CATKIN_DEPENDS roscpp
  DEPENDS system_lib
)

#===============================================================================
# I N C L U D E   F I L E S

# Defining the sources and headers directories.
set(auv7_emulator_HDR_DIR "src")
set(auv7_emulator_SRC_DIR "src")

# Get all the files of the projects.
file(GLOB_RECURSE auv7_emulator_FILES
  "${auv7_emulator_HDR_DIR}/*.h"
  "${auv7_emulator_SRC_DIR}/*.cc"
)

set(auv7_emulator_INCLUDE_DIRS
  "${auv7_emulator_HDR_DIR}"
)

include_directories(include
	${catkin_INCLUDE_DIRS}
	${GAZEBO_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${auv7_emulator_INCLUDE_DIRS}
	)

#===============================================================================
# C R E A T E   E X E C U T A B L E

link_directories(
	${GAZEBO_LIBRARY_DIRS}
	${Boost_LIBRARY_DIRS}
	)

add_executable(auv7_emulator 
	${auv7_emulator_FILES}
	)
target_link_libraries(auv7_emulator ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})
add_dependencies(auv7_emulator auv7_motor_control_generate_messages)