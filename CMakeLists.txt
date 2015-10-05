cmake_minimum_required(VERSION 3.3)
project(gui_nessie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ressources/models/sonia_sub/meshes/base_link.STL
    ressources/models/sonia_sub/ASM_SONIA_2013.URDF
    ressources/models/sonia_sub/model.config
    ressources/worlds/sonia.world
    ressources/script-placement-fichiers.sh
    ressources/setup_gz5.sh
    ressources/setup_gz6.sh
    ressources/sonia_world.launch
    src/nessie_msgs/msg/auv7_motor_control.msg
    src/nessie_msgs/CMakeLists.txt
    src/nessie_msgs/package.xml
    src/nessie_plugins/src/gz_ros.cc
    src/nessie_plugins/src/gz_ros.h
    src/nessie_plugins/src/pose_publisher.cc
    src/nessie_plugins/src/pose_publisher.h
    src/nessie_plugins/src/thruster.cc
    src/nessie_plugins/src/thruster.h
    src/nessie_plugins/CMakeLists.txt
    src/nessie_plugins/package.xml
    src/nessie_ros/src/auv7_emulator.cc
    src/nessie_ros/src/auv7_emulator.h
    src/nessie_ros/src/main.cc
    src/nessie_ros/CMakeLists.txt
    src/nessie_ros/package.xml
    src/CMakeLists.txt
    AUTHORS.md
    LICENSE
    README.md)

add_executable(gui_nessie ${SOURCE_FILES})