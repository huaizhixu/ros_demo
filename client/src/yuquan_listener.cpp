#include "ros/ros.h"
#include "include/proto/agreement.pb.h"

void pbChatterCallback(const boost::shared_ptr<pb_msgs::agreement>& msg)
{
  ROS_INFO_STREAM("Time:");
  
}

void counterCallback(const boost::shared_ptr<pb_msgs::agreement>& msg)
{
  ROS_INFO("I get counter message: [%f]", msg->id());
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber pb_sub = n.subscribe("pb_chatter", 1000, pbChatterCallback);
  ros::Subscriber sub = n.subscribe("counter", 1000, counterCallback);
  ros::spin();

  return 0;
}
