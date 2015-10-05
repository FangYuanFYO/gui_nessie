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
	Auv7Emulator::Auv7Emulator(ros::NodeHandle node)
	{
		node_handler_ = node;
		sens = false;

		publisher_ = node_handler_.advertise<nessie_msgs::auv7_motor_control>(
									"nessie/auv7_motor_control", 200);

        subscriber_ = node_handler_.subscribe("nessie/auv7_pose", 200, &Auv7Emulator::PoseCallback, this);
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
		if(sens)
		{
			msg.motor_front_d = 1;
		}
		else
		{
			msg.motor_front_d = 2;	
		}
		ROS_INFO("Auv7EmulatorPublish, id = %d", msg.motor_front_d);

		publisher_.publish(msg);
	}

    //------------------------------------------------------------------------------
    //
    void Auv7Emulator::PoseCallback(const geometry_msgs::Pose::ConstPtr& msg)
    {
    	ROS_INFO("PoseCallback, position = %lf", msg->position.x);
        if(msg->position.x > 2)
        {
        	sens = true;
        }
        else if(msg->position.x < -2)
        {
        	sens = false;	
        }
    }
}

/*
 * Subscriber pour la pose
 * gazebo::math::Pose position;
        position = _model->GetRelativePose();
        printf("Position : %f, %f, %f\n", position.pos.x, position.pos.y, position.pos.z);
        // common::Time::MSleep(5000);
        // math::Vector3 accel_;
        // accel_.x = 0;
        // accel_.y = 0;
        // accel_.z = 2;
        // _model->SetLinearVel(accel_);
        // printf("Velocity set ! \n");
 */