#include "UarmController.hh"
#include "new_position.pb.h"

namespace gazebo
{
UarmController::UarmController()
{
  for (int i = 0; i < NUM_JOINTS; i++)
  {
    this->jointPIDs[i] = common::PID(40, 0, 20, 1, -1);
    this->jointPositions[i] = 0;
    this->jointVelocities[i] = 0;
    this->jointMaxEfforts[i] = 10;
  }
  jointPositions[1] = 1;
}

//////////////////////////////////////////////////
void UarmController::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
  this->model = _model;

  this->node = transport::NodePtr(new transport::Node());
  this->node->Init(this->model->GetWorld()->GetName());

  // get all joints
  this->joints[0] = _model->GetJoint("center_table_mount");
  this->joints[1] = _model->GetJoint("left_base_shoulder_joint");
  this->joints[2] = _model->GetJoint("left_base_arm_joint");

  this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&UarmController::OnUpdate, this));

  // Initialize transport
//  gazebo::transport::init();
  // Create our node for communication
  gazebo::transport::NodePtr node(new gazebo::transport::Node());
  node->Init(this->model->GetName());
  // Listen to Gazebo world_stats topic
  sub = node->Subscribe("/uarm/topic", &UarmController::MoveCallback, this);
}

/////////////////////////////////////////////////
void UarmController::Init()
{
  // physics::EntityPtr parent = boost::dynamic_pointer_cast<physics::Entity>(
  //   this->joints[0]->GetChild());
}

//////////////////////////////////////////////////
void UarmController::OnUpdate()
{
  common::Time currTime = this->model->GetWorld()->GetSimTime();
  common::Time stepTime = currTime - this->prevUpdateTime;
  this->prevUpdateTime = currTime;

  double pos_target, pos_curr, max_cmd, pos_err, effort_cmd;

  for (int i = 0; i < NUM_JOINTS; i++)
  {
    // first joint, set position
    pos_target = this->jointPositions[i];
    pos_curr = this->joints[i]->GetAngle(0).Radian();
    max_cmd = this->jointMaxEfforts[i];

    pos_err = pos_curr - pos_target;

    effort_cmd = this->jointPIDs[i].Update(pos_err, stepTime);
    effort_cmd = effort_cmd > max_cmd ? max_cmd : (effort_cmd < -max_cmd ? -max_cmd : effort_cmd);
    this->joints[i]->SetForce(0, effort_cmd);
//    if (i == 1)
//      std::cout << effort_cmd << std::endl;
  }
}

void UarmController::MoveCallback(NewPosition &_msg)
{
	std::cout << "Received new Position" << std::endl;
	for (int i = 0; i< _msg->positions().size(); i++){
		if (_msg->positions().Get(i).joint_name() == "center_table_mount"){
			this->jointPositions[0] = _msg->positions().Get(i).angle();
		}

		if (_msg->positions().Get(i).joint_name() == "left_base_shoulder_joint"){
			this->jointPositions[1] = _msg->positions().Get(i).angle();

		}
		if (_msg->positions().Get(i).joint_name() == "left_base_arm_joint"){
			this->jointPositions[2] = _msg->positions().Get(i).angle();
		}
	}

}

}
