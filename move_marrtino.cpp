#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
using std::array;
using namespace std;

array<float, 2> x = {5,1};
array<float, 2> y = {3,1};
array<float, 2> w = {1,1};

int main(int argc, char** argv){
  ros::init(argc, argv, "move_marrtino");

  int lunghezza = x.size();
  MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  move_base_msgs::MoveBaseGoal goal[lunghezza];

  ROS_INFO("Sending goal");
  for(int i=0; i<lunghezza; i++){
      goal[i].target_pose.header.frame_id = "odom";
      goal[i].target_pose.header.stamp = ros::Time::now();
      
      goal[i].target_pose.pose.position.x = x[i];
      goal[i].target_pose.pose.position.y = y[i];
      goal[i].target_pose.pose.orientation.w = w[i];
            
      ac.sendGoal(goal[i]);
      ac.waitForResult();


    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("Robot ha raggiungo l'obiettivo");
     } else {
      ROS_INFO("Il robot non e' riuscito a raggiungere l'obiettivo");
     } 
  }
  return 0;     
}
