#ifndef _SuctionCup_HH_
#define _SuctionCup_HH_

#include "gazebo/gazebo.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/transport/TransportTypes.hh"
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include "suction_cup_contact.pb.h"
#include "new_position.pb.h"

typedef const boost::shared_ptr<const uarm_msgs::msgs::SuctionCupContact> SuctionCupContact;
typedef const boost::shared_ptr<const uarm_msgs::msgs::NewPosition> NewPosition;

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

private:
  void ContactCallback(SuctionCupContact &_msg);

private:
  void SuckCallback(NewPosition &_msg);

// connection pointer to update the world
private:
  event::ConnectionPtr updateConnection;

// model pointer to get acces to the joints
private:
  physics::ModelPtr model;

private:
  physics::LinkPtr link;

private:
  LONG updatecounter;

  // transport node
  private:
    transport::NodePtr node;

  private:
    gazebo::transport::SubscriberPtr sub_con;

  private:
    gazebo::transport::SubscriberPtr sub_suck;

private: std::string link_name;
};
GZ_REGISTER_MODEL_PLUGIN(SuctionCup)
}
#endif
