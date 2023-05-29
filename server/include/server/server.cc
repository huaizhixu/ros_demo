#include "server/server.h"
 
using namespace Server;
 
server::server() {
  shmID = shmget((key_t)1933, sizeof(pb_msgs::agreement), 0666 | IPC_CREAT);
  if (shmID != -1) {
    shm = shmat(shmID, NULL, 0);
  } else {
    ROS_ERROR("Cann't get shared memory,error num is %d, for %sn", errno,
              strerror(errno));
  }
  mem = (pb_msgs::agreement *)shm;
}
 
void server::receveMessage() {
  std::cout << "server receve message from client " << std::endl;

  while (true) {

std::cout << " mem->flag:"<< mem->flag() << std::endl;
std::cout << " mem->sid:"<< mem->id() << std::endl;

std::cout << " mem->x:"<< mem->x() << std::endl;
std::cout << " mem->y:"<< mem->y() << std::endl;
std::cout << " mem->z:"<< mem->z() << std::endl;

    sleep(1);
  }
}
 
server::~server() {
  if (shmdt(shm) == -1) {
    ROS_ERROR("Error is %d, cann't not release shared memory. for %sn", errno,
              strerror(errno));
  }
}