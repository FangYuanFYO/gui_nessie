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
	// int main(int argc, char **argv)
	// {
	//   ros::init(argc, argv, "nessie");

	//   ros::NodeHandle n;
	//   return 0;
	// }

	ThrusterPlugin::ThrusterPlugin() : ModelPlugin()
	{
		// node_handler_ = new ros::NodeHandle("auv7_emulator");
		printf("ThrusterPlugin constructor.\n");
	}

	ThrusterPlugin::~ThrusterPlugin()
	{
		printf("ThrusterPlugin destructor.\n");
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
			ROS_INFO("ThrusterPlugin load -> error, ROS not started...\n");
//			return;
            int argc = 0;
            char** argv = NULL;
            ros::init(argc,argv,"thruster",ros::init_options::NoSigintHandler);
		}
		
		math::Pose position;
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

		//SEE : gazebo_ros_api_plugin
		//-> a master plugin has to be launched to launch ROS for gazebo !
        node_handler_ = new ros::NodeHandle("nessie");
//        node_handler_ = new ros::NodeHandle();

//		subscriber_ = node_handler_->subscribe("auv7_motor_control", 200, &ThrusterPlugin::MotorControlCallback, this);
//        subscriber_ = node_handler_->subscribe("nessie/auv7_motor_control", 200, &ThrusterPlugin::MotorControlCallback, this);

//        gazebonode_ = gazebo::transport::NodePtr(new gazebo::transport::Node());
//        gazebonode_->Init("nessie");
//        subscriber_ = gazebonode_->Subscribe("auv7_motor_control", &ThrusterPlugin::MotorControlCallback);

		this->updateConnection = event::Events::ConnectWorldUpdateBegin (
				boost::bind ( &ThrusterPlugin::OnUpdate, this, _1 ) );



        gazebo_callback_queue_thread_.reset(new std::thread(&ThrusterPlugin::gazeboQueueThread, this) );

        ros::SubscribeOptions link_state_so =
                ros::SubscribeOptions::create<std_msgs::String>(
                        "auv7_motor_control",10,
                        boost::bind( &ThrusterPlugin::MotorControlCallback,this,_1),
                        ros::VoidPtr(), &gazebo_queue_);
        subscriber_ = node_handler_->subscribe(link_state_so);

        printf("ThrusterPlugin load !\n");
	}

	void ThrusterPlugin::OnUpdate(const common::UpdateInfo &_info)
	{
		// math::Pose position;
		// position = _model->GetRelativePose();
		// printf("Update position : %f, %f, %f\n", position.pos.x, position.pos.y, position.pos.z);
//		printf("ThrusterPlugin update !\n");
	}

//	void ThrusterPlugin::MotorControlCallback(const nessie_msgs::auv7_motor_control::ConstPtr& msg)
	void ThrusterPlugin::MotorControlCallback(const std_msgs::String::ConstPtr& msg)
	{
		ROS_INFO("MotorControlCallback !!\n");
	}

	//------------------------------------------------------------------------------
	//
	void ThrusterPlugin::gazeboQueueThread()
	{
        static const double timeout = 0.001;
		while (node_handler_->ok())
		{
			gazebo_queue_.callAvailable(ros::WallDuration(timeout));
		}
    }
}