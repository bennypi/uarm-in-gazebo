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
    else
    {
    	cout << "Use uarm_pub joint_name angle" << endl;
    }

    return -1;
}