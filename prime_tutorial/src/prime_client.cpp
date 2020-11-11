#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <prime_tutorial/PrimeAction.h>

using namespace prime_tutorial;

// to get the feedback from the server
bool feed;

// called once when the goal completes
void doneCb(const actionlib::SimpleClientGoalState& state, const PrimeResultConstPtr& result) {
}

// called once when the goal becomes active
void activeCb() {
}

// called every time feedback is received for the goal
void feedbackCb(const PrimeFeedbackConstPtr& feedback) {
  feed = feedback->prime;
}

int main (int argc, char **argv)
{
  ros::init(argc, argv, "test_prime");

  // Create the action client
  typedef actionlib::SimpleActionClient<PrimeAction> Client;
  Client ac("prime", true);

  ROS_INFO("Waiting for action client to connect.");

  // wait for the action server to start
  ac.waitForServer();
  ROS_INFO("Action client is connected to the server..");

  while (ros::ok())
  {
  std::cout<<"Please enter a number: ";
    prime_tutorial::PrimeGoal goal;
    std::cin>>goal.number;
  // If the user didn't input a number
  if(!std::cin)
  {
    // reset
    std::cin.clear();
    //skip incorrect input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  else
  {
    // send the goal to the action server
    ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

    // wait a bit to recieve the feedback
    ac.waitForResult();

    // check the server feedback
    if (feed)
    {
      std::cout<<"The entered number is Prime" <<std::endl;
    }
    
    else if (!feed)
    {
      std::cout<<"The entered number is not a Prime" <<std::endl;
    }
  }      

  }
  return 0;
}