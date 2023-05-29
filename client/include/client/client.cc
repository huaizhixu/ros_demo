#include "client/client.h"
 
using namespace Client;
 
client::client() {
  shmID = shmget((key_t)1933, sizeof(pb_msgs::agreement), 0666 | IPC_CREAT);
  if (shmID != -1) {
    shm = shmat(shmID, NULL, 0);
  } else {
    ROS_ERROR("Cann't get shared memory,error num is %d, for %sn", errno,
              strerror(errno));
  }
  mem = (pb_msgs::agreement *)shm;
}
 
void client::sendMessage() {
  std::cout << "Ready to send message to client " << std::endl;
  double id = 1, x = 2, y = 3, z = 4;
 
  while (true) {
    mem->set_flag(true);
    mem->set_id(id++);
    mem->set_x(x++);
    mem->set_y(y++);
    mem->set_z(z++);
    sleep(1);
  }
}
 
client::~client() {
  if (shmdt(shm) == -1) {
    ROS_ERROR("Error is %d, cann't not release shared memory. for %sn", errno,
              strerror(errno));
  }
}