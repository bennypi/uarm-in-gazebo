#ifndef _SuctionCup_HH_
#define _SuctionCup_HH_

#include "gazebo/gazebo.hh"
#include "gazebo/physics/physics.hh"

namespace gazebo
{
class SuctionCup : public ModelPlugin
{

public:
  virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);

/// \brief Callback method for updateConnection, is called in every world update.
/// In this callback the PID-Controller calculate the effort for the three joints.
/// After the calculation the values will be applied.
public:
  void OnUpdate();

/// \brief This method initializes the plugin, but we do nothing in here.
private:
  virtual void Init();

// connection pointer to update the world
private:
  event::ConnectionPtr updateConnection;

// model pointer to get acces to the joints
private:
  physics::ModelPtr model;

private:
  physics::LinkPtr link;

};
GZ_REGISTER_MODEL_PLUGIN(SuctionCup)
}
#endif
