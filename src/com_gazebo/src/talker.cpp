#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
//import pour Gazebo
#include "gazebo_msgs/ApplyBodyWrench.h"

/**********************************************************************
* Programme de test du package gazebo_ros
* Permet de demander au sous-marin d'effectuer un déplacement
* Contient les commandes de bases pour utiliser le package gazebo_ros
***********************************************************************/

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Time startTime(0);
  ros::Duration durationTime(1000000);

  ros::Rate loop_rate(0.3); //rate en Hz

  //int count = 0;

  //permet de demander à Gazebo d'envoyer l'état d'un modèle
  //ros::ServiceClient client = n.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");

  //création d'un client d'un service Gazebo
  //permet d'appliquer une force sur un modèle dans Gazebo (ici il s'agit du sous-marin SONIA)
  ros::ServiceClient client = n.serviceClient<gazebo_msgs::ApplyBodyWrench>("/gazebo/apply_body_wrench");
  gazebo_msgs::ApplyBodyWrench srv;
  
  //données du message (voir le message ApplyBodyWrench pour plus de détails)
  srv.request.body_name = "sonia_sub::sub";
  srv.request.reference_frame = "sonia_sub::sub";
  srv.request.start_time = startTime;
  srv.request.duration = durationTime;
  srv.request.wrench.force.x = -10; //signe négatif à cause du rérérentiel considéré

  //on applique la commande
  if (client.call(srv))
  {
    ROS_INFO("Le sub avance !");
  }
  else
  {
    ROS_ERROR("Failed to call service ApplyBodyWrench");
    return 1;
  }

  //temporisation
  loop_rate.sleep();

  //on fait reculer le sub
  srv.request.wrench.force.x = 20;
  if (client.call(srv))
  {
    ROS_INFO("Le sub amorce l'arret !");
  }
  else
  {
    ROS_ERROR("Failed to call service ApplyBodyWrench");
    return 1;
  }

  //temporisation
  loop_rate.reset();
  loop_rate.sleep();

  //on arrête le sub, test de clear
  srv.request.wrench.force.x = 0;
  if (client.call(srv))
  {
    ROS_INFO("On stoppe le sub");
  }
  else
  {
    ROS_ERROR("Failed to call service ApplyBodyWrench");
    return 1;
  }

  return 0;
}