#!/bin/zsh
export GAZEBO_MODEL_PATH=models/
export LD_LIBRARY_PATH=build:$LD_LIBRARY_PATH
gazebo world/uarm_world_with_box.world
source ~/.zshrc
