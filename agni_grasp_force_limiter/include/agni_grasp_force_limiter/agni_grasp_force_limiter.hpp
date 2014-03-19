/**
 * @file   agni_grasp_force_limiter.hpp
 * @author Guillaume Walck <gwalck@techfak.uni-bielefeld.de>
 * @date   Feb 2014
 *
 * @brief  Check at the joint states for high forces on joints to limit the force
 *
 */

#ifndef AGNI_GRASP_FORCE_LIMITER_H
#define AGNI_GRASP_FORCE_LIMITER_H

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

using namespace ros;

class AgniGraspForceLimiter
  {
  public:
    AgniGraspForceLimiter();
    ~AgniGraspForceLimiter();

  protected:
    NodeHandle nh, nh_tilde;
    Subscriber sub;
    
    void stateProcessingCB(const sensor_msgs::JointStateConstPtr& msg);
    void initializeServices();
    void controller_command_cb(const std_msgs::Float64ConstPtr& msg, std::string jointname);

    std::vector<ros::Subscriber> controller_command_sub;
    std::map<std::string,double> controller_last_command;
    
    std::map<std::string,ros::Publisher>  controller_maxforcepub_map;      //!< store the controller max force publisher per joint
    std::map<std::string,unsigned int> force_cutout_counter;
    std::map<std::string,unsigned int> force_monitor_counter;
    
    std::map<std::string,double> prevError;
    std::map<std::string,bool> forcelimited;
    std::map<std::string,bool> forcecutout;
  };//end class



/* For the emacs weenies in the crowd.
Local Variables:
   c-basic-offset: 2
End:
*/


#endif //AGNI_GRASP_FORCE_LIMITER_H
