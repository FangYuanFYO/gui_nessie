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
		if(node_handler_)
		{
			delete node_handler_;
		}
	}

	//==============================================================================
	// M E T H O D S   S E C T I O N

	//------------------------------------------------------------------------------
	//
	void NessieStartupPlugin::Load(int argc, char** argv)
	{
		if (!ros::isInitialized())
		    {
		    	ros::init(argc,argv,"nessie",ros::init_options::NoSigintHandler);
		    	ROS_INFO("NessieStartupPlugin::Load\n");
		    }
		else
		    ROS_ERROR("Something other than this gazebo_ros_api plugin started ros::init(...), command line arguments may not be parsed properly.");
	}
}