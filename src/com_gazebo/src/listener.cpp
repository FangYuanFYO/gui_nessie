#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ModelStates.h"

/****************************************************************
Programme qui s'abonne au topic Gazebo pour avoir la position
du sub au cours du temps.
*****************************************************************/


//fonction de callback utilisée quand on récupère une donnée sur le topic
void chatterCallback(gazebo_msgs::ModelStates msg)
{
	double pos_x = msg.pose[1].position.x;
	double pos_y = msg.pose[1].position.y;
	double pos_z = msg.pose[1].position.z;
  //on affiche la position (x,y,z) du modèle via lecture d'un topic dédié
  ROS_INFO("I heard something : x = %lf, y = %lf, z = %lf", pos_x, pos_y, pos_z);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;
  //on s'abonne au topic créé par Gazebo où on peut récupérer les données de position du sub
  ros::Subscriber sub = n.subscribe("/gazebo/model_states", 100, chatterCallback);

  ros::spin();
  return 0;
}