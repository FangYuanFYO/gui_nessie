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
#include <ros/callback_queue.h>

#include <string>
#include <thread>

#include <nessie_msgs/auv7_motor_control.h>

#include <std_msgs/String.h>

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
//		void MotorControlCallback(const nessie_msgs::auv7_motor_control::ConstPtr& msg);
		void MotorControlCallback(const std_msgs::String::ConstPtr& msg);
        void gazeboQueueThread();

	private:
		ros::NodeHandle* node_handler_;
		ros::Subscriber subscriber_;
		event::ConnectionPtr update_connection_;
		std::string topic_name_;
		physics::WorldPtr world_;
		physics::ModelPtr model_;

        gazebo::transport::NodePtr gazebonode_;
//        gazebo::transport::SubscriberPtr subscriber_;

		event::ConnectionPtr updateConnection;

		ros::CallbackQueue gazebo_queue_;
        std::shared_ptr<std::thread> gazebo_callback_queue_thread_;

	};
	GZ_REGISTER_MODEL_PLUGIN(ThrusterPlugin)
}

/*************************************/
/******* Links to keep in minde *******

-> gazebo_ros_joint_state_publisher (robotNamespace)

**************************************/