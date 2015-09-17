#include <gazebo/gazebo.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/math/Vector3.hh>
#include <gazebo/common/common.hh>
#include <gazebo/msgs/msgs.hh>
#include "ros/ros.h"

namespace gazebo
{
	class WorldPluginTutorial : public WorldPlugin
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
}