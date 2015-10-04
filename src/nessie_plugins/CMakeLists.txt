# \file	CMakeLists.txt
# \author	Thomas Fuhrmann <tomesman@gmail.com>
# \date	22/08/2015
# \copyright	2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>

#===============================================================================
# C M A K E   C O N F I G U R A T I O N

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(nessie_plugins)

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

include_directories(include
	${catkin_INCLUDE_DIRS}
	${GAZEBO_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	)

#===============================================================================
# C R E A T E   E X E C U T A B L E

link_directories(
	${GAZEBO_LIBRARY_DIRS}
	${Boost_LIBRARY_DIRS}
	)

add_library(hello_world_2 SHARED src/hello_world.cc)
add_library(thruster SHARED src/thruster.cc)

target_link_libraries(hello_world_2 ${GAZEBO_LIBRAIRIES} ${catkin_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(thruster ${GAZEBO_LIBRAIRIES} ${catkin_LIBRARIES} ${Boost_LIBRARIES})

#===============================================================================
# I N S T A L L   C O M P I L E D   F I L E S

set(
	GAZEBO_PLUGIN_INSTALL_DIR
	#${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}/gazebo-${GAZEBO_VERSION}/plugins
	${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}/gazebo/
	)

install(
	TARGETS	hello_world_2
	LIBRARY DESTINATION ${GAZEBO_PLUGIN_INSTALL_DIR}
	)
