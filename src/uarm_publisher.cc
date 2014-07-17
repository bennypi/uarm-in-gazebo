#include "uarm_publisher.hh"

UarmPublisher::UarmPublisher()
{
  gazebo::load();
  gazebo::transport::init();
  gazebo::transport::run();
  gazebo::transport::NodePtr node(new gazebo::transport::Node());

  node->Init("uarm_publisher");
  this->pub = node->Advertise<uarm_msgs::msgs::NewPosition>("/uarm/topic"); //add topic name

  std::cout << "Waiting for connection." << std::endl;
  pub->WaitForConnection();
  std::cout << "Connection established." << std::endl;
}

UarmPublisher::~UarmPublisher()
{
  gazebo::transport::fini();
}


void UarmPublisher::send_message(char * joint_name, double angle)
{
  uarm_msgs::msgs::NewPosition msg;
  //uarm_msgs::msgs::NewJointPosition joint_msg;
  msg.add_positions();
  msg.mutable_positions(0)->set_joint_name(joint_name);
  msg.mutable_positions(0)->set_angle(angle);
  std::cout << "Trying to send message." << std::endl;
  pub->Publish(msg);
  std::cout << "Send message." << std::endl;
}





