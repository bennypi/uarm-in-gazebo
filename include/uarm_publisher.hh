#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo.hh>
#include "new_position.pb.h"
#include "new_joint_position.pb.h"

class UarmPublisher
{
  public: UarmPublisher();
  public: ~UarmPublisher();
  private: gazebo::transport::PublisherPtr pub;
  public: void send_message(char *joint_name, double angle);
  public: void send_message(char *joint_name[], double angle[]);
};
