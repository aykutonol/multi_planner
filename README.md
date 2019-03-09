# Multi-agent scenario with decentralized planning
This package is developed for decentralized path planning on a grid map for multiple agents.

The libraries are implemented in C++ 11.

The only dependency of this framework is [ROS](http://www.ros.org/install/).

The package consists of two nodes: an agent node and a planner node. The agent node spawns an agent given a configuration
(_x_, _y_, _theta_) and a serial number. It also publishes the agent's pose, and the planner node listens to this topic,
which is called /agent_feedback. The planner involves a service called /get_plan that returns the shortest path between the
agent's pose and a goal pose request for the 11-by-11, 4-connected grid shown below. In this grid, we assume that the 
columns from left to right represent the _x_ axis and the rows from bottom to top represent the _y_ axis. 

![](https://github.com/aykutonol/AYKUT_ONOL_INTERN/blob/master/extra/grid.png)

The shortest path is found by the Dijkstra's algorithm that is implemented in dijkstra class.

A goal pose can be requested for an arbitrary agent by using /update_goal service in the agent node.

## Installation
1. Create a workspace and download the code:  
    ```
    mkdir -p ~/cito_ws/src
    cd ~/cito_ws/src/
    git clone https://github.com/aykutonol/AYKUT_ONOL_INTERN.git
    ```  
2. Build the package:
    ```
    cd ~/cito_ws/
    catkin build
    source devel/setup.bash
    ```

## Usage
The planner node can be run by:  
`rosrun multi_planner planner_node`  
A plan can be requested with a goal pose (geometry_msgs/Pose2D) and a serial ID (string), as follows:
`rosservice /get_plan '[x,y,theta]' 'agent'`

The agent node can be run by:  
`rosrun multi_planner agent_node`  
When there is no input parameter, it spawns an agent at (0, 0, 0) with the ID 'agent'. A goal can be set by calling the
rosservice /update_goal:  
`rosservice call /agent/update_goal '[x,y,theta]'`

## Test
A test with two agents can be performed by using the launch file "launch/multiagents.lauch":  
` roslaunch multi_planner multiagents.launch`

This file initializes two agents: 'agent_1' at (0,0,0) and 'agent_2' at (5,5,0). It runs the planner node as well.

The goals of [5,5,0] and [10,8,0] for the agents 1 and 2 can then be set by the following rosservice calls:  
```
rosservice call /agent_1/agent/update_goal '[5,5,0]'
rosservice call /agent_2/agent/update_goal '[10,8,0]'
```

The planned paths can be seen by echoing the path topics:
```
rostopic echo /agent_1/agent/path
rostopic echo /agent_2/agent/path
```

They can be displayed on RViz as well:
```
rosrun rviz rviz -d src/AYKUT_ONOL_INTERN/extra/config.rviz
```
This command uses a predefined configuration file (extra/config.rviz) for better visualization. The resulting paths
can be seen in the following figure.

![](https://github.com/aykutonol/AYKUT_ONOL_INTERN/blob/master/extra/rviz_ss.png)
