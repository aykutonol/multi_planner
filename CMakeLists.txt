cmake_minimum_required(VERSION 2.8.3)
project(multi_planner)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	std_msgs
	geometry_msgs
	nav_msgs
	message_generation
)

add_service_files(
	FILES
	PlanPath.srv
)

catkin_package(
	CATKIN_DEPENDS geometry_msgs message_runtime
)

include_directories(
	include
)

add_library(${PROJECT_NAME}
	src/dijkstra.cpp
)


include_directories(${catkin_INCLUDE_DIRS})

add_executable(agent_node		src/agent.cpp)
target_link_libraries(agent_node	${catkin_LIBRARIES})

add_executable(planner_node		src/planner.cpp)
add_dependencies(planner_node		multi_planner_generate_messages_cpp)
target_link_libraries(planner_node	${catkin_LIBRARIES}
			   		${PROJECT_NAME})
