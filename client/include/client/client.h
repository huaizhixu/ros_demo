#ifndef CLIENT_H_
#define CLIENT_H_
 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ros/ros.h>
#include <iostream>
 
#include "include/proto/agreement.pb.h"
 
namespace Client {
 
class client {
 public: 
  client();
  ~client();
 
  void sendMessage();
 private:
  int shmID;              // 共享内存标识符
  void *shm = nullptr;    // 与进程内存连接地址
  pb_msgs::agreement *mem = nullptr;
};
} // namespace Client
 
#endif