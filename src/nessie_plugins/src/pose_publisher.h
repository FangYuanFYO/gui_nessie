/**
 * \file	pose_publisher.h
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	04/10/2015
 * \copyright Copyright (c) 2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>.
 * All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#ifndef NESSIE_PLUGINS_POSE_PUBLISHER_H
#define NESSIE_PLUGINS_POSE_PUBLISHER_H

#include <thread>

#include <gazebo/gazebo.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/math/Vector3.hh>
#include <gazebo/common/common.hh>
#include <gazebo/msgs/msgs.hh>

#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <geometry_msgs/Pose.h>

#include <boost/bind.hpp>

namespace nessie
{
    //==============================================================================
    // G L O B A L   V A R I A B L E S   A N D   S T R U C T


    class PosePublisherPlugin : public gazebo::ModelPlugin
    {
    public:
        //============================================================================
        // P U B L I C   C / D T O R S
        PosePublisherPlugin();
        ~PosePublisherPlugin();

    protected:
        //============================================================================
        // P R O T E C T E D   M E T H O D S
        void Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr _sdf);

    private:
        //============================================================================
        // P R I V A T E   M E M B E R S
        ros::NodeHandle* node_handler_;
        ros::Publisher publisher_;
    };
    GZ_REGISTER_MODEL_PLUGIN(PosePublisherPlugin)
}

/*
 * 	class WorldPluginTutorial : public WorldPlugin
	{
		public: WorldPluginTutorial() : WorldPlugin()
		{
			printf("Fucking shit not working !!!\n");
			ROS_INFO("test\n");
		}
		public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
		{
			printf("Load function...\n");
			transport::NodePtr node(new transport::Node());
			node->Init("testNode");
			transport::PublisherPtr pub = node->Advertise<msgs::Vector3d>("velocity");
			math::Vector3 vel_;
			vel_.x = 0.0;
			vel_.y = 0.0;
			vel_.z = 1.0;
			// msgs::Vector3d vel_msg_;
			//check tuto programmatic world control
			// pub->Publish(vel_);
		}
	};
	GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial)
 */

#endif //PROJECT_POSE_PUBLISHER_H
