/**
 * \file	thruster.cc
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	19/09/2015
 * \copyright Copyright (c) 2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>.
 * All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#include "thruster.h"

namespace nessie
{
	//==============================================================================
	// C / D T O R   S E C T I O N

	//------------------------------------------------------------------------------
	//
	ThrusterPlugin::ThrusterPlugin() : ModelPlugin()
	{

	}

    //------------------------------------------------------------------------------
    //
	ThrusterPlugin::~ThrusterPlugin()
	{

	}

    //==============================================================================
    // M E T H O D S   S E C T I O N

    //------------------------------------------------------------------------------
    //
	void ThrusterPlugin::Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr _sdf)
	{
		//check if ROS has been started
		if(!ros::isInitialized())
		{
			ROS_INFO("ThrusterPlugin load -> error, ROS not started...\n");
            int argc = 0;
            char** argv = NULL;
            ros::init(argc,argv,"thruster",ros::init_options::NoSigintHandler);
		}
		
        gazebo::math::Pose position;
		position = _model->GetRelativePose();
		printf("Position : %f, %f, %f\n", position.pos.x, position.pos.y, position.pos.z);
		// common::Time::MSleep(5000);
		// math::Vector3 accel_;
		// accel_.x = 0;
		// accel_.y = 0;
		// accel_.z = 2;
		// _model->SetLinearVel(accel_);
		// printf("Velocity set ! \n");

        node_handler_ = new ros::NodeHandle("nessie");

        gazebo_callback_queue_thread_.reset(new std::thread(&ThrusterPlugin::gazeboQueueThread, this) );

        ros::SubscribeOptions link_state_so =
                ros::SubscribeOptions::create<nessie_msgs::auv7_motor_control>(
                        "auv7_motor_control",10,
                        boost::bind( &ThrusterPlugin::MotorControlCallback,this,_1),
                        ros::VoidPtr(), &gazebo_queue_);
        subscriber_ = node_handler_->subscribe(link_state_so);
	}

    //------------------------------------------------------------------------------
    //
	void ThrusterPlugin::MotorControlCallback(const nessie_msgs::auv7_motor_control::ConstPtr& msg)
	{
		ROS_INFO("MotorControlCallback : %d!!", msg->motor_front_d);
	}

	//------------------------------------------------------------------------------
	//
	void ThrusterPlugin::gazeboQueueThread()
	{
        static const double timeout = 0.001;
		while (node_handler_->ok())
		{
			gazebo_queue_.callAvailable(ros::WallDuration(timeout));
		}
    }
}