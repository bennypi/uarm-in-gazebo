#ifndef _UARMCONTROLLER_HH_
#define _UARMCONTROLLER_HH_

#include "gazebo/gazebo.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/transport/TransportTypes.hh"

#define NUM_JOINTS 1

namespace gazebo
{
class UarmController : public ModelPlugin
{
public:
  UarmController();

public:
  virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);

public:
  void OnUpdate();

private:
  virtual void Init();

private:
  transport::NodePtr node;

private:
  event::ConnectionPtr updateConnection;

private:
  physics::ModelPtr model;

private:
  physics::JointPtr joints[NUM_JOINTS];

private:
  common::PID jointPIDs[NUM_JOINTS];

private:
  double jointPositions[NUM_JOINTS];

private:
  double jointVelocities[NUM_JOINTS];

private:
  double jointMaxEfforts[NUM_JOINTS];

private:
  common::Time prevUpdateTime;
};
GZ_REGISTER_MODEL_PLUGIN(UarmController)
}
#endif
