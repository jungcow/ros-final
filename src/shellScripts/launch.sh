#!/bin/sh

gnome-terminal -e  " roslaunch final_evaluation evaluation.launch " &
sleep 3
gnome-terminal  -e  " roslaunch final_simulator simulation.launch "
sleep 3
gnome-terminal -e  " roslaunch final_autonomous_driving manual_driving.launch " &
~