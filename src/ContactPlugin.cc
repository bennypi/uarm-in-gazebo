#include "ContactPlugin.hh"

using namespace gazebo;
GZ_REGISTER_SENSOR_PLUGIN(ContactPlugin)

/////////////////////////////////////////////////
ContactPlugin::ContactPlugin() :
		SensorPlugin() {
//	gazebo::load();
//	gazebo::transport::init();
//	gazebo::transport::run();
	gazebo::transport::NodePtr node(new gazebo::transport::Node());

	node->Init("suction_cup_contact_publisher");
	this->pub = node->Advertise<uarm_msgs::msgs::SuctionCupContact>(
			"/uarm/suction_cup_contact"); //add topic name

//	std::cout << "Waiting for connection." << std::endl;
//	pub->WaitForConnection();
//	std::cout << "Connection established." << std::endl;
}

/////////////////////////////////////////////////
ContactPlugin::~ContactPlugin() {
	gazebo::transport::fini();
}

/////////////////////////////////////////////////
void ContactPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/) {

	// Get the parent sensor.
	this->parentSensor = boost::dynamic_pointer_cast<sensors::ContactSensor>(
			_sensor);

	// Make sure the parent sensor is valid.
	if (!this->parentSensor) {
		gzerr << "ContactPlugin requires a ContactSensor.\n";
		return;
	}

	// Connect to the sensor update event.
	this->updateConnection = this->parentSensor->ConnectUpdated(
			boost::bind(&ContactPlugin::OnUpdate, this));

	// Make sure the parent sensor is active.
	this->parentSensor->SetActive(true);

}

/////////////////////////////////////////////////
void ContactPlugin::OnUpdate() {
	// Get all the contacts.
	msgs::Contacts contacts;
	contacts = this->parentSensor->GetContacts();
	for (unsigned int i = 0; i < contacts.contact_size(); ++i) {
//    if(contacts.contact(i).collision1() != "ground_plane::ground_link::collision" &&
//    		contacts.contact(i).collision2() != "ground_plane::ground_link::collision"){
//    	std::cout << "Collision between[" << contacts.contact(i).collision1()
//    	              << "] and [" << contacts.contact(i).collision2() << "]\n";
//    }

//    if ((contacts.contact(i).collision1() == "uarm::suction_cup::collision" && contacts.contact(i).collision2() == "uarm_box::link::uarm_box_collision")
//        			|| (contacts.contact(i).collision2() == "uarm::suction_cup::collision" && contacts.contact(i).collision1() == "uarm_box::link::uarm_box_collision")){
//    	std::cout << "Found contact between suction cup and uarm_box\n";
		if (std::strcmp(contacts.contact(i).collision1().c_str(), "uarm::suction_cup::collision")== 0 && std::strcmp(contacts.contact(i).collision2().c_str(), "uarm::suction_cup::collision")!= 0)
			this->send_message(contacts.contact(i).collision2().c_str());
		if (std::strcmp(contacts.contact(i).collision2().c_str(), "uarm::suction_cup::collision")== 0 && std::strcmp(contacts.contact(i).collision1().c_str(), "uarm::suction_cup::collision")!= 0)
			this->send_message(contacts.contact(i).collision1().c_str());
//    }
	}
}

void ContactPlugin::send_message(const char* contact_name) {
	uarm_msgs::msgs::SuctionCupContact msg;
	//uarm_msgs::msgs::NewJointPosition joint_msg;
	msg.set_collision_name(contact_name);
//	std::cout << "Trying to send message." << std::endl;
	pub->Publish(msg);
//	std::cout << "Send message." << std::endl;
}
