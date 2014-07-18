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

Usage
==============

Start the simulation with:
```
launch_simulation.bash
```
or
```
launch_simulation.zsh
```

Now you can use `uarm_pub` to send commands to the uarm. It's possible to send an angle in radian to a specific joint:
```
./build/uarm_pub joint_name angle
```
Controllable joints are *left_base_shoulder_joint*, *left_base_arm_joint* and *center_table_mount*.
Alternatively you can give the `uarm_pub` a specific pose that the uarm should take:
```
./build/uarm_pub pose
```
At the moment the only available pose is *home_pose* which gives all three joints the angle 0.
