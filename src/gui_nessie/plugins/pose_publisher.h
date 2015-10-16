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
#include <gazebo/physics/physics.hh>

#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <geometry_msgs/Pose.h>

#include <boost/bind.hpp>

namespace nessie {

class PosePublisherPlugin : public gazebo::ModelPlugin {
 public:
  //============================================================================
  // P U B L I C   C / D T O R S

  PosePublisherPlugin();

  ~PosePublisherPlugin();

 protected:
  //============================================================================
  // P R O T E C T E D   M E T H O D S

  void Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr _sdf);

  void Update();

 private:
  //============================================================================
  // P R I V A T E   M E M B E R S

  ros::NodeHandle* node_handler_;

  ros::Publisher publisher_;

  gazebo::event::ConnectionPtr update_connection_;

  gazebo::physics::ModelPtr model_;

  uint32_t count_;
};

GZ_REGISTER_MODEL_PLUGIN(PosePublisherPlugin)

}  // namespace nessie

#endif  // PROJECT_POSE_PUBLISHER_H
