uarm-in-gazebo
==============
We are planning to create a working model of the uarm in gazebo. The uarm is a open-source robotic arm which was created by uFactory and founded through Kickstarter https://www.kickstarter.com/projects/ufactory/uarm-put-a-miniature-industrial-robot-arm-on-your.

Our plan (3. and 4. are bonuses if we have enough time):

1. Create a urdf-file from the CAD-model of the uarm and possibly merge or remove some parts to optimize it for the simulation.
2. Create plugins to control the arm.
3. Add a endeffector to the arm.
4. Connect the arm to ROS.

Installation
==============

1. Clone this repository.
2. Go into the directory "uarm-in-gazebo"
3. mkdir build && cd build
4. cmake ../src/
5. make
6. execute launch_simulation.zsh or launch_simulation.bash (depending on your shell type)