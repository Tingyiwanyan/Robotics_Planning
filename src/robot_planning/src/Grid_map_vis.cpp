#include <ros/ros.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <cmath>

using namespace grid_map;

int main(int argc, char** argv)
{
  //Initialize node and Publisher
  ros::init(argc,argv,"grid_map_vis");
  ros::NodeHandle nh("~");
  ros::Publisher publisher =
    nh.advertise<grid_map_msgs::GridMap>("grid_map",1,true);

  //Create grid map
  GridMap map({"elevation","normal_x"});
  map.setFrameId("map");
  map.setGeometry(Length(10,10),1,Position(0.5, 0.5));
  ROS_INFO("Created map with size %f x %f m (%i x %i cells).",
            map.getLength().x(),map.getLength().y(),
            map.getSize()(0),map.getSize()(1));

  //work with grid map in a loop
  ros::Rate rate(10.0);
  while(nh.ok())
  {
    //Add data to grid map
    ros::Time time  = ros::Time::now();
    for(GridMapIterator it(map); !it.isPastEnd();++it)
    {
      Position position;
      map.getPosition(*it, position);
      map.at("elevation", *it) = 0.0;//-0.04+0.2*position.x();//0.2*std::sin(3.0*time.toSec()+5.0*position.y())*position.x();
    }

    //Publish grid map.
    map.setTimestamp(time.toNSec());
    grid_map_msgs::GridMap message;
    GridMapRosConverter::toMessage(map,message);
    publisher.publish(message);
    ROS_INFO_THROTTLE(1.0,"Grid map (timestamp %f) published",
      message.info.header.stamp.toSec());

    rate.sleep();
  }
  return 0;
}
