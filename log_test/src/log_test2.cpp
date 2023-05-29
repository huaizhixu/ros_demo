
#include <ros/ros.h>
#include<sensor_msgs/Joy.h>
//引入日志库log4cxx的头文件
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include<log4cxx/basicconfigurator.h>
#include<log4cxx/helpers/exception.h>
#include<log4cpp/Category.hh>
#include <log4cpp/Configurator.hh>

using namespace log4cxx;
using namespace log4cxx::helpers;


void callback(const sensor_msgs::Joy::ConstPtr& Joy)
{
 ROS_INFO("a----------------------------: start");
 ROS_WARN("------test----------");

}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "log_test");
     ros::Subscriber sub ;
    //设置日志的运行级别
    // log4cxx::Logger::getLogger(ROSCONSOLE_DEFAULT_NAME)->setLevel(ros::console::g_level_lookup[ros::console::levels::Debug]);
    // //刷新一下，如果在修改日志运行级别之前没有生成日志也可以不调用，例如此处可以不调用
    // ros::console::notifyLoggerLevelsChanged();

         // 1 读取解析配置文件
    // 读取出错, 完全可以忽略，可以定义一个缺省策略或者使用系统缺省策略
    // BasicLayout输出所有优先级日志到ConsoleAppender
try
{
    log4cxx::PropertyConfigurator::configure("/home/cherish/code/yuquan_test/test_demo/src/log_test/map_manage.conf");
}
catch (log4cpp::ConfigureFailure& f)
{
    std::cout << "Configure Problem: " << f.what() << std::endl;
}

// log4cpp::Category& root = log4cpp::Category::getRoot();

log4cpp::Category& log = log4cpp::Category::getInstance(std::string("TESTAppender"));	//类Category的静态函数进行初始化

 ROS_INFO("111111111");
 log.info("222info.log");
  ROS_INFO("122222");
log.error("Hello log, %s", "abc");
log.error("[%s -> %s -> %d] Test option",__FILE__,__FUNCTION__,__LINE__);

#if 0
log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("lib"));
LOG4CXX_INFO(logger, "this is log4cxx info");
LOG4CXX_WARN(logger,"---------------");

#endif
    ros::NodeHandle n;
    // printf("日志格式: 时间－驱动器序号－参数值");
    // printf("参数有三个，request rpm是发送的每个车轮转速，current rpm是当前车轮的实际转速，error是驱动器的错误状态码");
    sub = n.subscribe<sensor_msgs::Joy>("joy",10,callback);
    ros::spin();
    log4cpp::Category::shutdown();
    return 0;
}

