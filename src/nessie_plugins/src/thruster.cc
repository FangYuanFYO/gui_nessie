// #include <gazebo/gazebo.hh>
// #include <gazebo/math/Pose.hh>
// #include <gazebo/math/Vector3.hh>
// #include <gazebo/physics/physics.hh>
// #include <gazebo/common/common.hh>
// #include <gazebo/transport/transport.hh>
// #include <gazebo/msgs/msgs.hh>

// #include <boost/bind.hpp>

#include "thruster.h"

namespace gazebo
{
	ThrusterPlugin::ThrusterPlugin() : ModelPlugin(), node_handler_()
	{
		printf("ThrusterPlugin constructor.\n");
	}

	ThrusterPlugin::~ThrusterPlugin()
	{
		printf("ThrusterPlugin destructor.\n");
		this->node_handler_.shutdown();
	}

	void ThrusterPlugin::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
	{
		printf("ThrusterPlugin load.\n");
		if(_model)
		{
			this->model_ = _model;
			this->world_ = this->model_->GetWorld();	
		}

		//check if ROS has been started
		if(!ros::isInitialized())
		{
			printf("ThrusterPlugin load -> error, ROS not started...\n");
			return;
		}
		
		math::Pose position;
		printf("ThrusterPlugin load !\n");
		position = _model->GetRelativePose();
		printf("Position : %f, %f, %f\n", position.pos.x, position.pos.y, position.pos.z);
		// common::Time::MSleep(5000);
		// math::Vector3 accel_;
		// accel_.x = 0;
		// accel_.y = 0;
		// accel_.z = 2;
		// _model->SetLinearVel(accel_);
		// printf("Velocity set ! \n");
		/* Add a node for get the velocity */
		// transport::NodePtr node(new transport::Node());
		// // node->Init(_model->GetName());
		// node->Init("testNode");	
		// transport::SubscriberPtr velocity_pub = node->Subscribe("velocity", cb);
		// this->upConnection = common::event::Event::ConnectWorldUpdateBegin(
		// 	boost::bind(&ThrusterPlugin::OnUpdate, this, _1));
		//check gazebo / model_plugin
	}

	void ThrusterPlugin::OnUpdate(const common::UpdateInfo &_info)
	{
		// math::Pose position;
		// position = _model->GetRelativePose();
		// printf("Update position : %f, %f, %f\n", position.pos.x, position.pos.y, position.pos.z);
		printf("ThrusterPlugin update !\n");
	}
}