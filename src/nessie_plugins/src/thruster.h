/**
 * \file	thruster.h
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	19/09/2015
 * \copyright Copyright (c) 2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>.
 * All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#ifndef NESSIE_PLUGINS_THRUSTER_H_
#define NESSIE_PLUGINS_THRUSTER_H_

#include <thread>

#include <gazebo/gazebo.hh>
#include <gazebo/math/Pose.hh>
#include <gazebo/math/Vector3.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

#include <ros/ros.h>
#include <ros/callback_queue.h>

#include <boost/bind.hpp>

#include <nessie_msgs/auv7_motor_control.h>

namespace nessie
{
    //==============================================================================
    // G L O B A L   V A R I A B L E S   A N D   S T R U C T


	class ThrusterPlugin : public gazebo::ModelPlugin
	{
	public:
    //============================================================================
    // P U B L I C   C / D T O R S
		ThrusterPlugin();
		~ThrusterPlugin();

	protected:
    //============================================================================
    // P R O T E C T E D   M E T H O D S
		void Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr _sdf);
		void MotorControlCallback(const nessie_msgs::auv7_motor_control::ConstPtr& msg);
        void gazeboQueueThread();

	private:
    //============================================================================
    // P R I V A T E   M E M B E R S
		ros::NodeHandle* node_handler_;
		ros::Subscriber subscriber_;
		ros::CallbackQueue gazebo_queue_;
        std::shared_ptr<std::thread> gazebo_callback_queue_thread_;

	};
	GZ_REGISTER_MODEL_PLUGIN(ThrusterPlugin)
}

#endif //NESSIE_PLUGINS_THRUSTER_H_