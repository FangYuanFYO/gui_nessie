/**
 * \file	auv7_emulator.cc
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	19/09/2015
 * \copyright Copyright (c) 2015 Thibaut Mattio. All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#include "nessie_startup_plugin.h"

namespace nessie
{
	//==============================================================================
	// C / D T O R   S E C T I O N

	//------------------------------------------------------------------------------
	//
	NessieStartupPlugin::NessieStartupPlugin()
	{
		ROS_INFO("NessieStartupPlugin Cstr\n");
	}

	//------------------------------------------------------------------------------
	//
	NessieStartupPlugin::~NessieStartupPlugin()
	{

	}

	//==============================================================================
	// M E T H O D S   S E C T I O N

	//------------------------------------------------------------------------------
	//
	void NessieStartupPlugin::Load(int argc, char** argv)
	{
        ROS_INFO("NessieStartupPlugin::Load before ros::init\n");
        // connect to sigint event
        sigint_event_ = gazebo::event::Events::ConnectSigInt(boost::bind(&NessieStartupPlugin::shutdownSignal,this));

		if (!ros::isInitialized())
		    {
		    	ros::init(argc,argv,"nessie",ros::init_options::NoSigintHandler);
		    	ROS_INFO("NessieStartupPlugin::Load\n");
		    }
		else
		    ROS_ERROR("Something other than NessieStartupPlugin plugin started ros::init(...), command line arguments may not be parsed properly.");

        // check if the ros master is available - required
        while(!ros::master::check())
        {
            ROS_WARN_STREAM_NAMED("api_plugin","No ROS master - start roscore to continue...");
            // wait 0.5 second
            usleep(500*1000); // can't use ROS Time here b/c node handle is not yet initialized

            if(stop_)
            {
                ROS_WARN_STREAM_NAMED("api_plugin","Canceled loading Gazebo ROS API plugin by sigint event");
                return;
            }
        }
        // advertise topics and services in this node's namespace
        node_handler_.reset(new ros::NodeHandle("~"));

        // Built-in multi-threaded ROS spinning
        async_ros_spin_.reset(new ros::AsyncSpinner(0)); // will use a thread for each CPU core
        async_ros_spin_->start();

        /// \brief setup custom callback queue
        gazebo_callback_queue_thread_.reset(new std::thread(&NessieStartupPlugin::gazeboQueueThread, this) );

//        gazebonode_ = gazebo::transport::NodePtr(new gazebo::transport::Node());
//        gazebonode_->Init("piscine");
	}
    //------------------------------------------------------------------------------
    //
    void NessieStartupPlugin::shutdownSignal()
    {
        stop_ = true;
    }

    //------------------------------------------------------------------------------
    //
    void NessieStartupPlugin::gazeboQueueThread()
    {
        static const double timeout = 0.001;
        while (node_handler_->ok())
        {
            gazebo_queue_.callAvailable(ros::WallDuration(timeout));
        }
    }
}