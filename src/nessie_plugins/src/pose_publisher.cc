/**
 * \file	pose_publisher.cc
 * \author	Thomas Fuhrmann <tomesman@gmail.com>
 * \date	04/10/2015
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
        msg.position.x = 3;

        publisher_.publish(msg);
    }
}