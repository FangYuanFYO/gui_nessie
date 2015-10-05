/**
 * \file	auv7_emulator.h
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	19/09/2015
 * \copyright Copyright (c) 2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>.
 * All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#ifndef NESSIE_ROS_AUV7_EMULATOR_H_
#define NESSIE_ROS_AUV7_EMULATOR_H_

#include <ros/ros.h>
#include <geometry_msgs/Pose.h>

#include <nessie_msgs/auv7_motor_control.h>

namespace nessie
{
	//==============================================================================
	// G L O B A L   V A R I A B L E S   A N D   S T R U C T

	/**
	 * @brief Emulate the behavior of AUV7.
	 * @details [long description]
	 * @return [description]
	 */
	class Auv7Emulator
	{
	public:
	//============================================================================
  	// P U B L I C   C / D T O R S
		Auv7Emulator(ros::NodeHandle node);
		~Auv7Emulator();
		void Auv7EmulatorPublish();
        void PoseCallback(const geometry_msgs::Pose::ConstPtr& msg);

	//============================================================================
  	// P U B L I C  M E T H O D S

	protected:
	//============================================================================
  	// P R O T E C T E D   M E T H O D S
		

	private:
	//============================================================================
  	// P R I V A T E   M E M B E R S
		ros::NodeHandle node_handler_;
		ros::Publisher	publisher_;
        ros::Subscriber subscriber_;
        bool sens_x;
		bool sens_z;
	};
}

#endif //NESSIE_ROS_AUV7_EMULATOR_H_