# \file	CMakeLists.txt
# \author	Thomas Fuhrmann <tomesman@gmail.com>
# \date	15/10/2015
# \copyright	2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>

#===============================================================================
# G L O B A L   P R O J E C T   C O N F I G U R A T I O N

cmake_minimum_required( VERSION 2.8.3 )

project( gui_nessie )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo\
       MinSizeRel."
      FORCE )
endif( NOT CMAKE_BUILD_TYPE )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11" )
set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++1 -O3" )

#===============================================================================
# C A T K I N   C O N F I G U R A T I O N

find_package( catkin REQUIRED COMPONENTS
   std_msgs
   geometry_msgs
   roscpp
   message_generation
)

find_package( gazebo
	REQUIRED Boost
	REQUIRED COMPONENTS system)

#===============================================================================
# G E N E R A T E   M E S S A G E S   &   S E R V I C E S
add_message_files(
	DIRECTORY msg
    FILES
    auv7_motor_control.msg
)

generate_messages( DEPENDENCIES std_msgs )

#===============================================================================
# C R E A T E   C A T K I N   P A C K A G E

catkin_package(
    INCLUDE_DIRS src
    LIBRARIES
    CATKIN_DEPENDS
    std_msgs
    message_runtime
    message_generation
    roscpp
)

#===============================================================================
# I N C L U D E   F I L E S

# Defining the sources and headers directories.
set(gui_nessie_SRC_DIR "src")

# Get all the files of the projects.
file(GLOB_RECURSE gui_nessie_FILES
  "${gui_nessie_SRC_DIR}/*.h"
  "${gui_nessie_SRC_DIR}/*.cc"
)

# Include all the directories where source can be found.
include_directories(include
	${gui_nessie_SRC_DIR}
	${GAZEBO_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${catkin_INCLUDE_DIRS}
)

#==========================================================================
# C R E A T E   E X E C U T A B L E

link_directories(
	${GAZEBO_LIBRARY_DIRS}
	${Boost_LIBRARY_DIRS}
)

# Create the Gazebo plugins as shared libraries
set( TARGET_NAME pose_publisher )
#add_library( ${TARGET_NAME} SHARED ${gui_nessie_FILES} )
add_library( ${TARGET_NAME} src/gui_nessie/plugins/${TARGET_NAME}.cc )
target_link_libraries( ${TARGET_NAME}
   ${catkin_LIBRARIES}
   ${GAZEBO_LIBRAIRIES}
   ${Boost_LIBRARIES}
)
set_target_properties( ${TARGET_NAME}
   PROPERTIES
   LINKER_LANGUAGE CXX
)

set( TARGET_NAME thruster )
#add_library( ${TARGET_NAME} SHARED ${gui_nessie_FILES} )
add_library( ${TARGET_NAME} src/gui_nessie/plugins/${TARGET_NAME}.cc )
add_dependencies(${TARGET_NAME} ${PROJECT_NAME}_gencpp)
target_link_libraries( ${TARGET_NAME}
   ${catkin_LIBRARIES}
   ${GAZEBO_LIBRAIRIES}
   ${Boost_LIBRARIES}
)
set_target_properties( ${TARGET_NAME}
   PROPERTIES
   LINKER_LANGUAGE CXX
)

# Create a CXX file from the given sources
set( TARGET_NAME auv7_emulator )
#add_executable( ${TARGET_NAME} ${gui_nessie_FILES} )
add_executable( ${TARGET_NAME} src/gui_nessie/ros/${TARGET_NAME}.cc src/gui_nessie/main.cc)
add_dependencies(${TARGET_NAME} ${PROJECT_NAME}_gencpp)
set_target_properties( ${TARGET_NAME}
   PROPERTIES
   LINKER_LANGUAGE CXX
)

# Link all the used libraries to the previsouly created executable.
target_link_libraries( ${TARGET_NAME}
    ${catkin_LIBRARIES}
    ${GAZEBO_LIBRARIES}
)

#==========================================================================
# C R E A T I N G   U N I T   T E S T S

#==========================================================================
# I N S T A L L I N G   T A R G E T S
