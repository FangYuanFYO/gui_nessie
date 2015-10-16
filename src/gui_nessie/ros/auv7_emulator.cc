/**
 * \file	auv7_emulator.cc
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	19/09/2015
 * \copyright Copyright (c) 2015 Thibaut Mattio. All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#include "auv7_emulator.h"

namespace nessie {

//==============================================================================
// C / D T O R   S E C T I O N

//------------------------------------------------------------------------------
//
Auv7Emulator::Auv7Emulator(ros::NodeHandle node) {
  node_handler_ = node;
  sens_x = false;
  sens_z = false;

  publisher_ = node_handler_.advertise<gui_nessie::auv7_motor_control>(
      "nessie/auv7_motor_control", 200);

  subscriber_ = node_handler_.subscribe("nessie/auv7_pose", 200,
                                        &Auv7Emulator::PoseCallback, this);
}

//------------------------------------------------------------------------------
//
Auv7Emulator::~Auv7Emulator() {}

//==============================================================================
// M E T H O D S   S E C T I O N

//------------------------------------------------------------------------------
//
void Auv7Emulator::Auv7EmulatorPublish() {
  gui_nessie::auv7_motor_control msg;
  if (sens_x) {
    msg.motor_front_depth = 1;
  } else {
    msg.motor_front_depth = 2;
  }
  if (sens_z) {
    msg.motor_front_heading = 1;
  } else {
    msg.motor_front_heading = 2;
  }
  publisher_.publish(msg);
}

//------------------------------------------------------------------------------
//
void Auv7Emulator::PoseCallback(const geometry_msgs::Pose::ConstPtr& msg) {
  if (msg->position.x > 1) {
    sens_x = true;
  } else if (msg->position.x < -1) {
    sens_x = false;
  }
  if (msg->position.z > 2.5) {
    sens_z = true;
  } else if (msg->position.z < 2) {
    sens_z = false;
  }
}

}  // namespace nessie
