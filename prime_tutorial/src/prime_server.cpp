#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <prime_tutorial/PrimeAction.h>

class PrimeAction
{
protected:

  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  actionlib::SimpleActionServer<prime_tutorial::PrimeAction> as_;
  std::string action_name_;

  // create messages that are used to published feedback/result
  prime_tutorial::PrimeFeedback feedback_;
  prime_tutorial::PrimeResult result_;

public:

  PrimeAction(std::string name) :
    as_(nh_, name, boost::bind(&PrimeAction::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
    ROS_INFO("Action Server started");

  }

  ~PrimeAction(void)
  {
  }

  void executeCB(const prime_tutorial::PrimeGoalConstPtr &goal)
  {
    // helper variables
    ros::Rate r(10);
    result_.composite = false;

    // start executing the action
    for (int x = goal->number-1; x>1; x--)
    {
    // check that preempt has not been requested by the client
    if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        break;
      }

    else if (goal->number % x == 0)
      {
        result_.composite = true;
        break;
      }
    }
    
    if (result_.composite || goal->number < 2)
    {
      feedback_.prime = false;
      // publish the feedback
      as_.publishFeedback(feedback_);
      r.sleep();
    }
    
    else
    {
      feedback_.prime = true;
      // publish the feedback
      as_.publishFeedback(feedback_);
      r.sleep();

    }
      as_.setSucceeded();
    }

  };

int main(int argc, char** argv)
{
  ros::init(argc, argv, "prime");

  PrimeAction prime("prime");
  ros::spin();

  return 0;
}