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

		model_ = _model;
		
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
		//msg->motor_front_d
		gazebo::math::Vector3 accel_;
		// if(msg->motor_front_d == 1)
		// {
		// 	accel_.x = -2;
		// }
		// else if(msg->motor_front_d == 2)
		// {
		// 	accel_.x = 2;
		// }	
		// accel_.y = 0;
		// if(msg->motor_front_h == 1)
		// {
		// 	accel_.z = -0.5;
		// }
		// else if(msg->motor_front_h == 2)
		// {
		// 	accel_.z = 0.5;
		// }
		// model_->SetLinearVel(accel_);


		gazebo::math::Vector3 pos_;
		link_ = model_->GetLink("motor_front_depth");
		if(link_)
		{
			accel_.z = 50;
			// pos_.x = 0.5;
			// link_->AddForceAtRelativePosition(accel_, pos_);
			link_->AddForce(accel_);
		}
		link_ = model_->GetLink("motor_back_depth");
		if(link_)
		{
			accel_.z = 50;
			// pos_.x = 0.5;
			// link_->AddForceAtRelativePosition(accel_, pos_);
			link_->AddForce(accel_);
		}
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