#include "server/server.h"

using namespace Server;

int main(int argc, char **argv) {
    ros::init(argc, argv, "control_node2");
    Server::server Server;
    Server.receveMessage();
    return 0;
}