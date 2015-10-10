#The simulator Nessie

Nessie is the team SONIA's simulator, based on Gazebo and working with ROS. This project is a part of the AUV7 project.

##Install Gazebo

As Nessie works with Gazebo, you have first to install it. First, check if you have already installed it. Open a terminal and write the following : 

```
gazebo -v
```

If it says that Gazebo doesn't exist, or if your version is less than 6, [please install the Gazebo 6 software] (http://www.gazebosim.org/tutorials?tut=install_ubuntu&cat=install).

##Compile Nessie

Once Gazebo is installed, you have to do a little more things before compiling Nessie. 
In fact, you have to source the Nessie's bashrc. The simplest way is to add it to your main bashrc file.

- path_to_gui_nessie is the path of the GUI_NESSIE folder.

```
echo "source path_to_gui_nessie/ressources/setup_gz.sh" >> ~/.bashrc
echo "source path_to_gui_nessie/devel/setup.bash" >> ~/.bashrc
```

For example, if GUI_NESSIE is a included in you SONIA workspace :

```
echo "source $SONIA_WORKSPACE_ROOT/gui_nessie/ressources/setup_gz.sh" >> ~/.bashrc
echo "source $SONIA_WORKSPACE_ROOT/gui_nessie/devel/setup.bash" >> ~/.bashrc
```

Now you can compile the project. As Nessie is a ROS project, you just have to run the catkin_make command on the root of the project's folder.

When it's your first compilation, you may have an error of missing .h files. You just have to source the project's bashrc and compile again :

```
source path_to_gui_nessie/devel/setup.bash
catkin_make
```

##Launch Nessie

When Nessie is compiled, you have to launch it. First launch ROS (roscore), then Gazebo and finaly the ROS node which control the submarine (in different terminals) :

```
gazebo worlds/sonia.world
rosrun nessie_ros auv7_emulator
```
