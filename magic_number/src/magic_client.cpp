#include <ros/ros.h>
#include <magic_number/Magic.h>
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "magic_client");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<magic_number::Magic>("check_magic_number");
  magic_number::Magic srv;
  
  while (ros::ok())
  {
    std::cout<<"Please enter a numer: ";
    std::cin>>srv.request.entered_number;

  if(!std::cin)
  {
    // reset
    std::cin.clear();
    //skip incorrect input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  else
  {
    if (client.call(srv))
    {
      if (srv.response.sum == 1)
      {
        ROS_INFO("The entered number is magic");
      }
      else
      {
        ROS_INFO("The entered number is not magic");
      }
        
    }
    
    else
    {
      ROS_ERROR("Failed to call service magic_check");
      return 1;
    }
  }

  }
  return 0;
}
