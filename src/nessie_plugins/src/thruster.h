#pragma once

#include <gazebo/gazebo.hh>
#include <gazebo/math/Pose.hh>
#include <gazebo/math/Vector3.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>

#include <boost/bind.hpp>

#include <ros/ros.h>

#include <string>

namespace gazebo
{
	class ThrusterPlugin : public ModelPlugin
	{
	public:
		ThrusterPlugin();
		~ThrusterPlugin();

	protected:
		void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
		void OnUpdate(const common::UpdateInfo &_info);

	private:	
		ros::NodeHandle node_handler_;
		ros::Subscriber subsriber_;
		event::ConnectionPtr update_connection_;
		std::string topic_name_;
		physics::WorldPtr world_;
		physics::ModelPtr model_;

	};
	GZ_REGISTER_MODEL_PLUGIN(ThrusterPlugin)
}

/*************************************/
/******* Links to keep in minde *******

-> gazebo_ros_joint_state_publisher (robotNamespace)

**************************************/