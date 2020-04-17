#!/bin/sh

xterm -e "source /home/workspace/catkin-ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e "source /home/workspace/catkin-ws/devel/setup.bash; roslaunch gmapping slam_gmapping_pr2.launch" &
sleep 10
xterm -e "source /home/workspace/catkin-ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "source /home/workspace/catkin-ws/devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch" 
