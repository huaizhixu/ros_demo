#include "ros/ros.h"
#include "include/proto/agreement.pb.h"

#include <sstream>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher pb_chatter_pub = n.advertise<pb_msgs::agreement>("pb_chatter", 1000);
  ros::Publisher counter_pub = n.advertise<pb_msgs::agreement>("counter", 1000);
  
  ros::Rate loop_rate(10);

  double count = 555;
  while (ros::ok())
  {
    // pb_msgs::ShortMessage pb_msg;
    // ros::Time now = ros::Time::now();
    // pb_msg.mutable_stamp()->set_sec(now.sec);
    // pb_msg.mutable_stamp()->set_nsec(now.nsec);
    // std::stringstream ss;
    // ss << "Hello world " << count;
    // pb_msg.set_content(ss.str());

    // ROS_INFO("%s", pb_msg.content().c_str());
    // pb_chatter_pub.publish(pb_msg);

    pb_msgs::agreement counter;
    counter.set_id(count);
    counter_pub.publish(counter);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}
