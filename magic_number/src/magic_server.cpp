#include <ros/ros.h>
#include <magic_number/Magic.h>


 bool magic_check(magic_number::Magic::Request  &req, magic_number::Magic::Response &res)
{
    while (req.entered_number > 0 || res.sum > 9) 
    { 
        if (req.entered_number == 0) 
        { 
            req.entered_number = res.sum; 
            res.sum = 0;
        } 
        res.sum += req.entered_number % 10; 
        req.entered_number /= 10; 
    } 
    std::cout<<"The server response has been sent to the client: "<< res.sum <<std::endl;
    // Return true.
    return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "magic_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("check_magic_number", magic_check);
  ROS_INFO("Ready to check for magic numbers");
  ros::spin();

  return 0;
}