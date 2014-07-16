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
  uarm_msgs::msgs::NewJointPosition joint_msg;
  joint_msg.set_joint_name(joint_name);
  joint_msg.set_angle(angle);
  msg.add_positions();
  uarm_msgs::msgs::NewJointPosition* new_joint = msg.mutable_positions(0);
  new_joint = & joint_msg;
  std::cout << "Trying to send message." << std::endl;
  pub->Publish(msg);
  std::cout << "Send message." << std::endl;
}





