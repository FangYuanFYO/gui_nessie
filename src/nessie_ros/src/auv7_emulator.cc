/**
 * \file	auv7_emulator.cc
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	19/09/2015
 * \copyright Copyright (c) 2015 Thibaut Mattio. All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#include "auv7_emulator.h"

namespace nessie
{
	//==============================================================================
	// C / D T O R   S E C T I O N

	//------------------------------------------------------------------------------
	//
	Auv7Emulator::Auv7Emulator(ros::NodeHandle node)// : node_handler_()
	{
		node_handler_ = node;
		publisher_ = node_handler_.advertise<nessie_msgs::auv7_motor_control>(
									"auv7_motor_control", 200);
	}

	//------------------------------------------------------------------------------
	//
	Auv7Emulator::~Auv7Emulator()
	{

	}

	//==============================================================================
	// M E T H O D S   S E C T I O N

	//------------------------------------------------------------------------------
	//
	void Auv7Emulator::Auv7EmulatorPublish()
	{
		nessie_msgs::auv7_motor_control msg;
		ros::Rate loop_rate(1000);

		msg.motor_front_d = 1;
		msg.motor_rear_d = 2;
		msg.motor_front_h = 3;
		msg.motor_rear_h = 4;
		msg.motor_prop_right = 5;
		msg.motor_prop_left = 6;

		publisher_.publish(msg);
	}
}