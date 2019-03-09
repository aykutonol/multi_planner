cmake_minimum_required(VERSION 2.8.3)
project(multi_planner)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
		roscpp
		std_msgs
		geometry_msgs
		tf
)

catkin_package()

include_directories(
		include
)

add_library(${PROJECT_NAME}
		src/dijkstra.cpp
)


include_directories(${catkin_INCLUDE_DIRS})

add_executable(agent 		src/agent.cpp)
target_link_libraries(agent 	${catkin_LIBRARIES})

add_executable(planner 			src/planner.cpp)
target_link_libraries(planner 		${catkin_LIBRARIES}
			   		${PROJECT_NAME})
