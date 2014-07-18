#!/bin/bash
export GAZEBO_MODEL_PATH=models/
gazebo world/uarm_world_with_box.world
source ~/.zshrc
