#include "suction_cup.hh"

namespace gazebo
{

void SuctionCup::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
  this->model = _model;

  this->link = this->model->GetLink("suction_cup");

  this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&SuctionCup::OnUpdate, this));
}

void SuctionCup::Init()
{

}

void SuctionCup::OnUpdate()
{
  physics::Collision_V collisions = this->link->GetCollisions();
  math::Vector3 axis;

  if (this->link->GetChildJointsLinks().empty())
  {
    for (int i = 0; i<  collisions.size(); i++)
    {
      if (collisions[i]->GetLink()->GetName() != "suction_cup")
      {
        std::cout << "Attach Joint." << std::endl;
        physics::JointPtr joint =
            this->model->GetWorld()->GetPhysicsEngine()->CreateJoint("revolute", this->model);
        joint->Attach(this->link, collisions[i]->GetLink());
        joint->Load(this->link, collisions[i]->GetLink(), axis);
        joint->SetAxis(0, axis);
      }
    }
  }
}

}
