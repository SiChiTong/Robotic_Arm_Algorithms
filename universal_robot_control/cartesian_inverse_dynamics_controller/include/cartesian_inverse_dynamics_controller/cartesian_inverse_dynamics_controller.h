#ifndef CARTESIAN_INVERSE_DYNAMICS_CONTROLLER_H
#define CARTESIAN_INVERSE_DYNAMICS_CONTROLLER_H

#include <ros/ros.h>
#include <geometry_msgs/Wrench.h>
#include "kinematics_base.h"
namespace cartesian_inverse_dynamics_controller
{

class Cartesian_Inverse_Dynamics_Controller : public kinematics_base::Kinematics_Base
{
public:
    Cartesian_Inverse_Dynamics_Controller(){}
    ~Cartesian_Inverse_Dynamics_Controller(){}

    bool init(hardware_interface::EffortJointInterface *robot, ros::NodeHandle &n);

    void starting(const ros::Time &time);

    void update(const ros::Time &time, const ros::Duration &period);

    void command_cart_tau(const geometry_msgs::Wrench &msg);

    // void command_cart_vel(const geometry_msgs::Twist)
private:
    void writeTorqueCommands(const ros::Duration &period);
protected:
    ros::Subscriber                             sub_command_;

    ros::Time                                   last_publish_time_;
    double                                      publish_rate;

    //KDL
    boost::shared_ptr<KDL::ChainDynParam>       dyn_param_solver_;
    boost::shared_ptr<KDL::ChainJntToJacSolver> ee_jacobian_solver_, wrist_jacobian_solver_;
    boost::shared_ptr<KDL::ChainJntToJacSolver> ee_jacobian_dot_solver_;
    boost::shared_ptr<KDL::ChainFkSolverVel>    fk_vel_solver_;
    boost::shared_ptr<KDL::ChainFkSolverPos>    fk_pos_solver_;
    boost::shared_ptr<KDL::ChainIkSolverVel>    ik_vel_solver_;

    KDL::Wrench                                 wrench_wrist_;

    KDL::JntArray                               Jnt_Pos_State_;
    KDL::JntArrayVel                            Jnt_Vel_State_;
    KDL::JntArrayVel                            Jnt_Vel_Past_State_;
    KDL::JntArray                               Jnt_Acc_State_;

    KDL::JntSpaceInertiaMatrix                  B;
    KDL::JntArray                               C;
    KDL::JntArray                               G;

    Eigen::MatrixXd                             Jnt_Effort;

    KDL::Jacobian                               base_J_ee;
    KDL::Frame                                  End_Pos_;
    // boost::shared_ptr<realtime_tools::RealtimePublisher<
    //     cartesian_state_msgs::PoseTwist> > realtime_pub_;

    
};

}

#endif //CARTESIAN_INVERSE_DYNAMICS_CONTROLLER_H