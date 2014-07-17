#include "uarm_publisher.hh"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc == 3)
    {
    	UarmPublisher publisher;
      char* joint_name = argv[1];
      double angle = atof(argv[2]);
    	publisher.send_message(joint_name, angle);
    }
    else if (argc == 2)
    {
      char* joint_names[3];
      joint_names[0] = "center_table_mount";
      joint_names[1] = "left_base_shoulder_joint";
      joint_names[2] = "left_base_arm_joint";

      double angles[3];

      if (argv[1] == "home_pose")
      {
        UarmPublisher publisher;
        angles[0] = 0;
        angles[1] = 0;
        angles[2] = 0;
        publisher.send_message(joint_names, angles);
      }
    }
    else
    {
    	cout << "Use uarm_pub joint_name angle" << endl;
    }

    return -1;
}
