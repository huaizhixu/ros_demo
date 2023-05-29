#include "client/client.h"

using namespace Client;

int main(int argc, char **argv) {
    ros::init(argc, argv, "control_node");
    Client::client Client;
    Client.sendMessage();
    return 0;
}