cmake_minimum_required(VERSION 3.0.2)
project(prime_tutorial)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  actionlib
  actionlib_msgs
)

find_package(Boost REQUIRED COMPONENTS system)

## Generate actions in the 'action' folder
add_action_files(
  DIRECTORY action
  FILES Prime.action
)

generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs
)

catkin_package(
  CATKIN_DEPENDS actionlib_msgs
)

include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(prime_server src/prime_server.cpp)
add_executable(prime_client src/prime_client.cpp)


target_link_libraries(
  prime_server
  ${catkin_LIBRARIES}
)
target_link_libraries(
  prime_client
  ${catkin_LIBRARIES}
)

add_dependencies(
  prime_server
  ${prime_tutorial_EXPORTED_TARGETS}
)
add_dependencies(
  prime_client
  ${prime_tutorial_EXPORTED_TARGETS}
)
