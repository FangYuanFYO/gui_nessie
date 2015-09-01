#include <gazebo/gazebo.hh>
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
		}
	};
	GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial)
}