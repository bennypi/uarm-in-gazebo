#include "suction_cup.hh"

namespace gazebo
{

void SuctionCup::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
  this->model = _model;

  this->link = this->model->GetLink("suction_cup");

  this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&SuctionCup::OnUpdate, this));

  std::cout << "Suction Cup plugin loaded" << std::endl;

  this->node = transport::NodePtr(new transport::Node());
  this->node->Init(this->model->GetWorld()->GetName());
  // Create our node for communication
  gazebo::transport::NodePtr node(new gazebo::transport::Node());
  node->Init(this->model->GetName());
  // Listen to Gazebo world_stats topic
  sub_con = node->Subscribe("/uarm/suction_cup_contact", &SuctionCup::ContactCallback, this);
  sub_con = node->Subscribe("/uarm/topic", &SuctionCup::SuckCallback, this);
}

void SuctionCup::Init()
{

}

void SuctionCup::OnUpdate()
{

//  physics::Collision_V collisions = this->link->GetCollisions();
//  math::Vector3 axis;
//
//  if (this->link->GetChildJointsLinks().empty())
//  {
//    for (int i = 0; i<  collisions.size(); i++)
//    {
////    	if(updatecounter % 100 == 0)
////		  std::cout << "Collision Object: " << collisions[i]->GetLink()->GetName() << std::endl;
//      if (collisions[i]->GetLink()->GetName() != "suction_cup")
//      {
//        std::cout << "Attach Joint." << std::endl;
//        physics::JointPtr joint =
//            this->model->GetWorld()->GetPhysicsEngine()->CreateJoint("revolute", this->model);
//        joint->Attach(this->link, collisions[i]->GetLink());
//        joint->Load(this->link, collisions[i]->GetLink(), axis);
//        joint->SetAxis(0, axis);
//      }
//    }
//  }
}

void SuctionCup::ContactCallback(SuctionCupContact &_msg){
	std::stringstream stream;
	stream << _msg->collision_name();
	std::getline(stream, link_name, ':');
	updatecounter++;
//	if(updatecounter % 100 == 0)
		std::cout << "link_name: " << "" << std::endl;

}

void SuctionCup::SuckCallback(NewPosition &_msg){
	if(_msg->positions().Get(0).joint_name() == "attach"){
		if(_msg->positions().Get(0).angle() == 1){
			std::cout << "attach object" << std::endl;
//			physics::LinkPtr obj = this->model->GetWorld()->GetModelBelowPoint(this->link->GetWorldPose().pos)->GetLink(link_name);
			std::cout << this->model->GetWorld()->GetModelBelowPoint(this->link->GetWorldPose().pos)->GetName() << std::endl;
		}
		else {

			std::cout << "detach object" << std::endl;
		}

	}

}

}
