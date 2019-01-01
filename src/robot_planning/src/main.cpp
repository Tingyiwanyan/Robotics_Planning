#include "Hello.h"
#include "mdp_state.h"
#include "simulate_grid2d.h"
#include "simulate_net.h"
#include "ssp.h"
#include "methods.h"
#include "grid_map_ros/grid_map_ros.hpp"
#include <unordered_map>
//#include <boost/filesystem.hpp>
#include <map>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <visualization_msgs/Marker.h>
#include<geometry_msgs/Pose.h>

using namespace std;
using namespace mdp_planner;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rtdp");
  ros::NodeHandle n;
  //ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker",20);
  ros::Rate loop_rate(10);
  ros::Rate r(1);
  int num_rows = 30;
  int num_cols = 30;
  vector<double> vec1,vec2;
  double resolution = 1;
  double ratio = num_rows/10.0;
  //vector<transform2> tf2_starts, sf2_goals;
  point2d_t origin(-num_cols/2 + 0.5, -num_rows/2 + 0.5);
  point2d_t start(10.5,-10.5);
  point2d_t goals(-10.5,10.5);
  MDP_Grid2D::Ptr pGrid2d = MDP_Grid2D::Ptr(new MDP_Grid2D(num_cols, num_rows, resolution, origin));
  MDP_Net::Ptr pNet = MDP_Net::Ptr(new MDP_Net(pGrid2d));
  pNet->getState(start)->type = START;
  pNet->getState(goals)->type = GOAL;
  //pNet->getState(goals)->optimal_value = 100;
  pNet->getState(goals)->optimal_action = ZERO;
  MDP_State* Start;
  Start = pNet->getState(start);
  //std::vector<int> mdp_obstacle_ids;
  //vector<mdp_state_t*> obstacles;
  vector<point2d_t*> top_lefts;
  point2d_t topleft(3.5,2.5);
  //point2d_t downright(6,10.5);
  double scale = 2;
  topleft[0] = 3*topleft[0];
  topleft[1] = 3*topleft[1];
  //downright[0] = downright[0];
  //downright[1] = downright[1];
  //mdp_planner::set_obstacle(pNet, topleft,scale);
  //mdp_planner::set_obstacle(pNet, downright,scale);
  //vector<point2d_t*> down_right;

  //pNet->mdp_obstacle_ids.push_back(1);
  //pNet->mdp_obstacle_ids.push_back(3);
  //pNet->mdp_obstacle_ids.push_back(4);
  //pNet->mdp_obstacle_ids.push_back(6);

  pNet->mdp_obstacle_ids.push_back(500);
  pNet->mdp_obstacle_ids.push_back(501);
  pNet->mdp_obstacle_ids.push_back(502);
  pNet->mdp_obstacle_ids.push_back(503);
  pNet->mdp_obstacle_ids.push_back(600);
  pNet->mdp_obstacle_ids.push_back(601);
  pNet->mdp_obstacle_ids.push_back(602);
  pNet->mdp_obstacle_ids.push_back(603);
  pNet->mdp_obstacle_ids.push_back(604);
  pNet->mdp_obstacle_ids.push_back(150);
  pNet->mdp_obstacle_ids.push_back(151);
  pNet->mdp_obstacle_ids.push_back(152);
  pNet->mdp_obstacle_ids.push_back(153);
  pNet->mdp_obstacle_ids.push_back(100);
  pNet->mdp_obstacle_ids.push_back(101);
  pNet->mdp_obstacle_ids.push_back(102);
  pNet->mdp_obstacle_ids.push_back(103);
  pNet->mdp_obstacle_ids.push_back(104);
  pNet->mdp_obstacle_ids.push_back(550);
  pNet->mdp_obstacle_ids.push_back(551);
  pNet->mdp_obstacle_ids.push_back(552);
  pNet->mdp_obstacle_ids.push_back(553);
  pNet->mdp_obstacle_ids.push_back(650);
  pNet->mdp_obstacle_ids.push_back(651);
  pNet->mdp_obstacle_ids.push_back(652);
  pNet->mdp_obstacle_ids.push_back(653);
  pNet->mdp_obstacle_ids.push_back(654);
  pNet->mdp_obstacle_ids.push_back(190);
  pNet->mdp_obstacle_ids.push_back(191);
  pNet->mdp_obstacle_ids.push_back(192);
  pNet->mdp_obstacle_ids.push_back(193);
  pNet->mdp_obstacle_ids.push_back(130);
  pNet->mdp_obstacle_ids.push_back(131);
  pNet->mdp_obstacle_ids.push_back(132);
  pNet->mdp_obstacle_ids.push_back(133);
  pNet->mdp_obstacle_ids.push_back(134);
  pNet->mdp_obstacle_ids.push_back(200);
  pNet->mdp_obstacle_ids.push_back(201);
  pNet->mdp_obstacle_ids.push_back(202);
  pNet->mdp_obstacle_ids.push_back(203);
  pNet->mdp_obstacle_ids.push_back(230);
  pNet->mdp_obstacle_ids.push_back(231);
  pNet->mdp_obstacle_ids.push_back(232);
  pNet->mdp_obstacle_ids.push_back(233);
  pNet->mdp_obstacle_ids.push_back(234);
  pNet->mdp_obstacle_ids.push_back(300);
  pNet->mdp_obstacle_ids.push_back(301);
  pNet->mdp_obstacle_ids.push_back(302);
  pNet->mdp_obstacle_ids.push_back(303);
  pNet->mdp_obstacle_ids.push_back(320);
  pNet->mdp_obstacle_ids.push_back(321);
  pNet->mdp_obstacle_ids.push_back(322);
  pNet->mdp_obstacle_ids.push_back(323);
  pNet->mdp_obstacle_ids.push_back(324);


  for(int i=0;i<pNet->mdp_obstacle_ids.size();i++)
  {
    //pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_value = -100;
    pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->type = OBSTACLE;
    pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_action = ZERO;
  }
  mdp_planner::uniform_transition_initialization(pNet);

  std::cout << "\nmap indices" << std::endl;
    for (int i = pGrid2d -> n_rows - 1; i >= 0; i--) {
        for (int j = 0; j < pGrid2d -> n_cols; j++) {
            std::cout << i * pGrid2d -> n_cols + j << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<pGrid2d->cell_centers.size()<<std::endl;
    mdp_state_t* iter_state = Start;
    pNet->relevant_states.push_back(iter_state);
    double error_one_trail = 0;
    uint32_t shape = visualization_msgs::Marker::CUBE;
    int frame_count = 0;
    //visualization_msgs::Marker path;
    vector<point2d_t> path_points;
    int max_iter_num = 50;
    int iter_num = 0;
    int trails_num = 0;
    int move_num_x = 0;
    int move_num_y = 0;
    int flag_move = 0;
    int flag_move2 = 0;
    int frame_num = 0;
    int num_steps = 0;
    SSP* pSSP = new SSP(pNet);
    pSSP->MFPT_obstacle(pNet);
    std::cout << "reachabilities" << std::endl;
    ofstream my_file;
    my_file.open("reachability.txt");

    for (int i = pNet -> n_rows - 1; i >= 0; i--) {
        for (int j = 0; j < pNet -> n_cols; j++) {
            //std::cout << i * pGrid2d -> n_cols + j << " ";
            std::cout<< pSSP->reachability[i * pNet -> n_cols + j]  << " ";
            my_file<<pSSP->reachability[i * pNet -> n_cols + j]<<",";
            pNet->mdp_states[i * pNet -> n_cols + j]->reachability = pSSP->reachability[i * pNet -> n_cols + j]*10-5;
        }
        std::cout << std::endl;
    }
    my_file.close();
    mdp_planner::Policy_iteration(pNet);
    while(ros::ok)
    {
/*
      if(frame_count % 15 == 0)
      {
        for(int i=0;i<pNet->mdp_obstacle_ids.size();i++)
        {
          //pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_value = -100;
          pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->type = BODY;
          pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_action = ZERO;
        }
      pNet->mdp_obstacle_ids.clear();
      if(flag_move == 0)
      {
        if(topleft[1] < pNet->n_rows-scale)
        {
          topleft[1] = topleft[1] + 1;
          mdp_planner::set_obstacle(pNet, topleft,scale);
          for(int i=0;i<pNet->mdp_obstacle_ids.size();i++)
          {
            //pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_value = -100;
            pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->type = OBSTACLE;
            pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_action = ZERO;
          }
        }
        else
        {
          flag_move = 1;
        }
      }
      if(flag_move == 1)
      {
        if(topleft[1] > scale)
        {
          topleft[1] = topleft[1] - 1;
          mdp_planner::set_obstacle(pNet, topleft,scale);
          for(int i=0;i<pNet->mdp_obstacle_ids.size();i++)
          {
            //pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_value = -100;
            pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->type = OBSTACLE;
            pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_action = ZERO;
          }
        }
        else
        {
          flag_move = 0;
        }
      }
    }
*/

/*
    if(frame_count % 15 == 0)
    {
    if(flag_move2 == 1)
    {
      if(downright[1] < pNet->n_rows-scale)
      {
        downright[1] = downright[1] + 1;
        mdp_planner::set_obstacle(pNet, downright,scale);
        for(int i=0;i<pNet->mdp_obstacle_ids.size();i++)
        {
          //pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_value = -100;
          pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->type = OBSTACLE;
          pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_action = ZERO;
        }
      }
      else
      {
        flag_move2 = 0;
      }
    }
    if(flag_move2 == 0)
    {
      if(downright[1] > scale)
      {
        downright[1] = downright[1] - 1;
        mdp_planner::set_obstacle(pNet, downright,scale);
        for(int i=0;i<pNet->mdp_obstacle_ids.size();i++)
        {
          //pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_value = -100;
          pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->type = OBSTACLE;
          pNet->mdp_states[pNet->mdp_obstacle_ids[i]]->optimal_action = ZERO;
        }
      }
      else
      {
        flag_move2 = 1;
      }
    }
  }
  */



      //mdp_planner::set_obstacle(pNet, topleft,scale);
      //mdp_planner::set_obstacle(pNet, downright,scale);
      //std::cout<<"Frame count "<<frame_count<<std::endl;
      int kk = 0;
      if(iter_state->type == GOAL)// || iter_num > max_iter_num)
      {
        //iter_state = Start;
        path_points.clear();
        iter_num = 0;
        trails_num ++;
        std::cout<<"trail number "<<trails_num<<std::endl;
        std::cout<<"num_steps "<<num_steps<<std::endl;
        num_steps = 0;
        break;
        //offline_simulate_mfpt(pNet, goals/ratio, iter_state,10);
      }
      int num_obstacles = pNet->mdp_obstacle_ids.size();//pMethod->getpNet3d()->mdp_obstacle_ids.size();
       // define some obstacles
       vector<visualization_msgs::Marker> obst(num_obstacles);
       for(int i = 0; i < num_obstacles; i++){

           int obst_id = pNet->mdp_obstacle_ids[i];//pMethod->getpNet3d()->mdp_obstacle_ids[i];
           //cout << "Obstacle List: " << obst_id << endl;
           //point_t p = pMethod->getpGrid3d()->cell_centers[obst_id];
           point2d_t p = pNet->cell_centers[obst_id];
           //std::cout<<"p.x "<<p.x()<<std::endl;
           //std::cout<<"p.y "<<p.y()<<std::endl;
           // Set obstacles as a Cube
           obst[i].type = visualization_msgs::Marker::CUBE;

           // Set the frame ID and timestamp.  See the TF tutorials for information on these.
           obst[i].header.frame_id = "map";  //NOTE: this should be "paired" to the frame_id entry in Rviz
           obst[i].header.stamp = ros::Time::now();

           // Set the namespace and id
           obst[i].ns = "obstacles";
           obst[i].id = i;

           // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
           obst[i].action = visualization_msgs::Marker::ADD;

           // Set the scale of the marker
           obst[i].scale.x = obst[i].scale.y = 1.0/ratio;
           obst[i].scale.z = 1.0/ratio; //1x1x0.2 here means the cylinder as diameter 1m and height 0.2m

           // Set the pose of the marker. since a side of the obstacle obst1 is 1m as defined above, now we place the obst1 center at (1, 2, 0.5). z-axis is height
           obst[i].pose.position.x = p.x()/ratio;
           obst[i].pose.position.y = p.y()/ratio;
           obst[i].pose.position.z = 0;
           obst[i].pose.orientation.x = 0.0;
           obst[i].pose.orientation.y = 0.0;
           obst[i].pose.orientation.z = 0.0;
           obst[i].pose.orientation.w = 1.0;	//(x, y, z, w) is a quaternion, ignore it here

           // Set the color red, green, blue. if not set, by default the value is 0
           obst[i].color.r = 0.0f;
           obst[i].color.g = 1.0f;
           obst[i].color.b = 0.0f;
           obst[i].color.a = 1.0;		//be sure to set alpha to something non-zero, otherwise it is transparent

           obst[i].lifetime = ros::Duration();

           marker_pub.publish(obst[i]);

       }
        static visualization_msgs::Marker rob;
        static visualization_msgs::Marker goal;
        static visualization_msgs::Marker path;


        rob.type = visualization_msgs::Marker::ARROW;
        //rob.type = visualization_msgs::Marker::MESH_RESOURCE;
        //rob.mesh_resource = "../../../rviz/src/test/meshes/pr2-base.dae";
        //rob.mesh_use_embedded_materials = true;
        goal.type = visualization_msgs::Marker::SPHERE;
        path.type = visualization_msgs::Marker::LINE_STRIP;

        rob.header.frame_id = path.header.frame_id = goal.header.frame_id = "map";  //NOTE: this should be "paired" to the frame_id entry in Rviz, the default setting in Rviz is "map"
        rob.header.stamp = path.header.stamp = goal.header.stamp = ros::Time::now();
        rob.ns = path.ns = goal.ns = "rob";
        rob.id = 0;
        path.id = 1;
        goal.id = 2;
        rob.action = path.action = goal.action = visualization_msgs::Marker::ADD;
      //  if(frame_count>5)
        //{
          //path.action = visualization_msgs::Marker::DELETE;
        //}
        rob.lifetime = path.lifetime = goal.lifetime = ros::Duration();

        rob.scale.x = 0.45/ratio;
        rob.scale.y = 0.45/ratio;
        rob.scale.z = 0.3/ratio;
        rob.pose.position.x = pNet->cell_centers[iter_state->id][0]/ratio;
        rob.pose.position.y = pNet->cell_centers[iter_state->id][1]/ratio;

        goal.scale.x = goal.scale.y = goal.scale.z = 0.3;

        rob.color.r = 1.0f;
        rob.color.g = 0.5f;
        rob.color.b = 0.5f;
        rob.color.a = 1.0;

        rob.pose.orientation.x = 0.0;
        rob.pose.orientation.y = -1.0;
        rob.pose.orientation.z = 0.0;
        rob.pose.orientation.w = 1.0;	//(x, y, z, w) is a quaternion, ignore it here

        goal.color.r = 1.0f;
        goal.color.g = 0.0f;
        goal.color.b = 0.0f;
        goal.color.a = 1.0;

        // path line strip is blue
        path.color.b = 1.0;
        path.color.a = 1.0;

        path.scale.x = 0.1;
        path.pose.orientation.w = 1.0;


        goal.pose.position.x = goals[0]/ratio;
        goal.pose.position.y = goals[1]/ratio;
        goal.pose.position.z = 0;
        goal.pose.orientation.x = 0.0;
        goal.pose.orientation.y = 0.0;
        goal.pose.orientation.z = 0.0;
        goal.pose.orientation.w = 1.0;	//(x, y, z, w) is a quaternion, ignore it here

        point2d_t path_point(pNet->cell_centers[iter_state->id][0]/ratio,pNet->cell_centers[iter_state->id][1]/ratio);
        path_points.push_back(path_point);
        //std::cout<<"path_points size "<<path_points.size()<<std::endl;
        /*
        for(int u=0; u<path_points.size();u++)
        {
          geometry_msgs::Point pp;
          pp.x = path_points[u][0];//rob.pose.position.x;
          pp.y = path_points[u][1];//rob.pose.position.y;
          pp.z = 0;
        //std::cout<<"path_point "<<pp.x<<std::endl;
        //std::cout<<"path_point "<<pp.y<<std::endl;
        path.points.push_back(pp);
        }
        */
        geometry_msgs::Point pp;
        pp.x = rob.pose.position.x;
        pp.y = rob.pose.position.y;
        path.points.push_back(pp);
        if(frame_count%10==0)
        {
          //offline_simulate_update_mfpt(iter_state,pNet, 10);
          ofstream my_file2;

  // print map indices
          my_file2.open("state_value.txt");
          std::cout << "\nmap indices" << std::endl;
          for (int i = pNet -> n_rows - 1; i >= 0; i--) {
              for (int j = 0; j < pNet -> n_cols; j++) {
                  //std::cout << i * pGrid2d -> n_cols + j << " ";
                  std::cout<< (int)pNet->mdp_states[i*pNet->n_cols+j]->optimal_value<<" ";
                  my_file2<<pNet->mdp_states[i*pNet->n_cols+j]->optimal_value<<",";
              }
              std::cout << std::endl;
          }
          my_file2.close();

        }
        //pSSP->initTransMatrix(pNet);
        double previous_value = iter_state->optimal_value;
        //mdp_planner::offline_simulate_update(iter_state, pNet, 50, 10);
        //mdp_planner::offline_previous_state_update(pNet, 50);
         //mdp_planner::updateState(iter_state, pNet);
         double current_value = iter_state->optimal_value;
         //error_current = std::abs(previous_value - current_value);
         //if(error_current > error_all)
         //{
          // error_all = error_current;
         //}
         action_t opt_act = iter_state->optimal_action;
          mdp_state_t* iter_state_curr  = mdp_planner::one_time_step_sample(iter_state,opt_act,pNet);
         if(iter_state_curr->type == OBSTACLE)
         {
           iter_state_curr  = mdp_planner::one_time_step_sample(iter_state,opt_act,pNet);
           //iter_state = start;
           //rob.pose.position.x = pNet->cell_centers[iter_state->id][0];
           //rob.pose.position.y = pNet->cell_centers[iter_state->id][1];
         }
         iter_state = iter_state_curr;
         pNet->relevant_states.push_back(iter_state);

        marker_pub.publish(rob);
        marker_pub.publish(path);
        marker_pub.publish(goal);
        iter_num ++;
      frame_count++;
      num_steps++;


       while (marker_pub.getNumSubscribers() < 1)
        {
            if (!ros::ok())
            {
                return 0;
            }
            ROS_WARN_ONCE("Please run Rviz in another terminal.");
            sleep(1);
        }
        ros::spinOnce();

        loop_rate.sleep();

     }

       /*
    for(int i=0;i<pNet->mdp_states.size();i++){

      if(pNet->mdp_states[i]->type != OBSTACLE)
      {
        error_one_trail = mdp_planner::Trail_update_(pNet->mdp_states[i],pNet);
        //error_one_trail = mdp_planner::Trail_update_(start,pParams,pNet);
        //if(error<error_one_trail)
        //{
        //  error = error_one_trail;
        //}
      }
      //std::cout<<"error is"<<error<<std::endl;
    }
    std::cout<<"error is"<<error_one_trail<<std::endl;

  }
  */
  /*
  std::cout << "\nmap indices" << std::endl;
  for (int i = pGrid2d -> n_rows - 1; i >= 0; i--) {
      for (int j = 0; j < pGrid2d -> n_cols; j++) {
          //std::cout << i * pGrid2d -> n_cols + j << " ";
          std::cout<< (int)pNet->mdp_states[i*pGrid2d->n_cols+j]->optimal_value<<" ";
          //my_file2<<pNet->mdp_states[i*pGrid2d->n_cols+j]->optimal_value<<",";
      }
      std::cout << std::endl;
  }
  */

/*
  mdp_planner::uniform_transition_initialization(pNet);
  std::cout<<pNet->mdp_states[2]->probs[1]<<std::endl;
  SSP *pSSP = new SSP(pNet);

  //pSSP->initTransMatrix(pNet);
  std::cout<<"goals "<<pNet->getState(goals)->id<<std::endl;
  pSSP->MFPT(pNet, pNet->getState(goals)->id);
  std::cout << "reachabilities" << std::endl;
  //ofstream my_file;
  //my_file.open("reachability.txt");

  for (int i = pNet -> n_rows - 1; i >= 0; i--) {
      for (int j = 0; j < pNet -> n_cols; j++) {
          //std::cout << i * pGrid2d -> n_cols + j << " ";
          std::cout<< (int)pSSP->reachability[i * pNet -> n_cols + j]  << " ";
          //my_file<<pSSP->reachability[i * pNet -> n_cols + j]<<",";
      }
      std::cout << std::endl;
  }
  */
  /*
  std::cout<<"transition probability"<<std::endl;
  for(int i = 0;i<pNet->n_rows*pNet->n_cols;i++)
  {
    for(int j = 0;j<pNet->n_rows*pNet->n_cols;j++)
    {
      std::cout<<pSSP->transMatrix.coeffRef(i, j)<<" ";
    }
    std::cout<<std::endl;
  }
  */

//  my_file.close();
    //mdp_planner::Trail_Based_RTDP(pNet);
  return 0;
}
