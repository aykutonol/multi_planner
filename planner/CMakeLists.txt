cmake_minimum_required(VERSION 2.8.3)
project(planner)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	std_msgs
	nav_msgs
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(map_publisher src/map_publisher.cpp src/map_publisher.cpp src/create_agent.cpp)
target_link_libraries(map_publisher ${catkin_LIBRARIES})
