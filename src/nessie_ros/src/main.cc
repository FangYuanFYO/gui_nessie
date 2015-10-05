/**
 * \file	main.cpp
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	29/09/2015
 * \copyright	2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>
 */

//==============================================================================
// I N C L U D E   F I L E S
#include "ros/ros.h"
#include "auv7_emulator.h"

/**
 * Main function of the vision_client package
 * This will launch the communication with the Vision Server and display de GUI
 */
int main(int argc, char *argv[]) {
  //** start ros */
  ros::init(argc, argv, "auv7_emulator");

  ros::NodeHandle n;

  ros::Rate loop_rate(1); //rate en Hz

  nessie::Auv7Emulator emul(n);

  while (ros::ok())
  {
//      ROS_INFO("Main loop !\n");
      emul.Auv7EmulatorPublish();
      ros::spinOnce();
      loop_rate.sleep();
  }

  return EXIT_SUCCESS;
}