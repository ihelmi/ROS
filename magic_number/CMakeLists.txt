cmake_minimum_required(VERSION 3.0.2)
project(magic_number)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  Magic.srv
 )

generate_messages(
  DEPENDENCIES
  std_msgs
)

include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(magic_server src/magic_server.cpp)
target_link_libraries(magic_server ${catkin_LIBRARIES})

add_executable(magic_client src/magic_client.cpp)
target_link_libraries(magic_client ${catkin_LIBRARIES})