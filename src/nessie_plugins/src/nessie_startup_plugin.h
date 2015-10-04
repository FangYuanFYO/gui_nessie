/**
 * \file	nessie_startup_plugin.h
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	01/10/2015
 * \copyright Copyright (c) 2015 Thibaut Mattio. All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#ifndef NESSIE_STARTUP_PLUGIN_H_
#define NESSIE_STARTUP_PLUGIN_H_

#include <ros/ros.h>
#include <ros/callback_queue.h>

#include <gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/transport.hh>

#include <boost/bind.hpp>

#include <thread>

namespace nessie
{
	//==============================================================================
	// G L O B A L   V A R I A B L E S   A N D   S T R U C T
	class NessieStartupPlugin : public gazebo::SystemPlugin
	{
	public:
	//============================================================================
  	// P U B L I C   C / D T O R S
		NessieStartupPlugin();
		~NessieStartupPlugin();

	//============================================================================
  	// P U B L I C  M E T H O D S
		void Load(int argc, char** argv);
        void shutdownSignal();
		void gazeboQueueThread();

	protected:
	//============================================================================
  	// P R O T E C T E D   M E T H O D S
		

	private:
	//============================================================================
  	// P R I V A T E   M E M B E R S
		// detect if sigint event occurs
  		bool stop_;
        gazebo::event::ConnectionPtr sigint_event_;

        std::shared_ptr<ros::NodeHandle> node_handler_;

        ros::CallbackQueue gazebo_queue_;
        std::shared_ptr<std::thread> gazebo_callback_queue_thread_;
        std::shared_ptr<ros::AsyncSpinner> async_ros_spin_;

//        gazebo::transport::NodePtr gazebonode_;

	};
	GZ_REGISTER_SYSTEM_PLUGIN(NessieStartupPlugin)
}

#endif