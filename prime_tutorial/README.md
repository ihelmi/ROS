# Table of Contents
- [Description](#description)
- [Executing the nodes](#executing-the-nodes)


# Description


- This is a simple ROS action client / server to check if a number is prime. 

- The action client sends the number to the server which will compute it and return the result back to the client.

- This tutorial was created and tested on Ubuntu 20.04 and ROS Noetic.




# Executing the nodes


- Startup the ROS master:

       
        roscore


- Start the action server:

       
        rosrun prime_tutorial prime_server


- Then start the action client:


        rosrun prime_tutorial prime_client
