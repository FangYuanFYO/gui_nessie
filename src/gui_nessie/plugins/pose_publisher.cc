/**
 * \file    pose_publisher.cc
 * \author  Thomas Fuhrmann <tomesman@gmail.com>
 * \date    04/10/2015
 * \copyright Copyright (c) 2015 SONIA AUV ETS <sonia@ens.etsmtl.ca>.
 * All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#include "pose_publisher.h"

namespace nessie
{
    //==============================================================================
    // C / D T O R   S E C T I O N

    //------------------------------------------------------------------------------
    //
    PosePublisherPlugin::PosePublisherPlugin() : ModelPlugin()
    {
        count_ = 0;
    }

    //------------------------------------------------------------------------------
    //
    PosePublisherPlugin::~PosePublisherPlugin()
    {

    }

    //==============================================================================
    // M E T H O D S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    void PosePublisherPlugin::Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr _sdf)
    {
        ROS_INFO("PosePublisherPlugin load");
        //check if ROS has been started
        if(!ros::isInitialized())
        {
            ROS_INFO("PosePublisherPlugin load -> error, ROS not started...\n");
            int argc = 0;
            char** argv = NULL;
            ros::init(argc,argv,"pose_publisher",ros::init_options::NoSigintHandler);
        }

        model_ = _model;

        node_handler_ = new ros::NodeHandle("nessie");

        publisher_ = node_handler_->advertise<geometry_msgs::Pose>("auv7_pose", 1);

        this->update_connection_ = gazebo::event::Events::ConnectWorldUpdateBegin(
                boost::bind(&PosePublisherPlugin::Update, this));
    }

    //------------------------------------------------------------------------------
    //
    void PosePublisherPlugin::Update()
    {
        geometry_msgs::Pose msg;
        gazebo::math::Pose pose;
        count_++;

        if(count_ > 100)
        {
            pose = model_->GetRelativePose();
            msg.position.x = pose.pos.x;
            msg.position.y = pose.pos.y;
            msg.position.z = pose.pos.z;
            msg.orientation.x = pose.rot.x;
            msg.orientation.y = pose.rot.y;
            msg.orientation.z = pose.rot.z;
            msg.orientation.w = pose.rot.w;
            count_= 0;
            publisher_.publish(msg);
        }
    }
}