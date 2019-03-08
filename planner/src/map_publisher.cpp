#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>


int main(int argc, char **argv)
{
    /// initialize ros
    ros::init(argc, argv, "publisher");
    /// create node handlecd
    ros::NodeHandle nh;
    /// build the map message
    nav_msgs::OccupancyGrid grid_map_msg;
    grid_map_msg.header.frame_id = "static_map";
    grid_map_msg.info.height = 11;
    grid_map_msg.info.width  = 11;
    grid_map_msg.info.resolution = 10;
    grid_map_msg.data.resize(grid_map_msg.info.height*grid_map_msg.info.width);
    // free map
    for( int i=0; i<grid_map_msg.info.height*grid_map_msg.info.width; i++ )
    {
        grid_map_msg.data[i] = 0;
    }
    /// publisher
    ros::Publisher map_pub = nh.advertise<nav_msgs::OccupancyGrid>("map",5);
    ros::Rate loop_rate(10);
    while( ros::ok() )
    {
        map_pub.publish(grid_map_msg);
        ROS_INFO("Publishing the map");
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}