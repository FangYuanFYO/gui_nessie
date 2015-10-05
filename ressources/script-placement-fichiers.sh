#script qui permet de créer des liens symboliques pour les fichiers à utiliser pour Gazebo

#pour le fichier sonia.world
ln -s $SONIA_WORKSPACE_ROOT/simsonia-gazebo/ressources/sonia.world /usr/share/gazebo-6.1/worlds/

#pour le fichier sonia_world.launch
ln -s $SONIA_WORKSPACE_ROOT/simsonia-gazebo/ressources/sonia_world.launch /opt/ros/indigo/share/gazebo_ros/launch

#pour le dossier sonia_sub
ln -s $SONIA_WORKSPACE_ROOT/simsonia-gazebo/ressources/models/sonia_sub ~/.gazebo/models


