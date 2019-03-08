cmake_minimum_required(VERSION 2.8.3)
project(planner)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
		roscpp
		std_msgs
		geometry_msgs
		tf
)

include_directories(
		include
)

add_library(${PROJECT_NAME}
		src/dijkstra.cpp
)


include_directories(${catkin_INCLUDE_DIRS})

add_executable(map_publisher 		src/map_publisher.cpp)
target_link_libraries(map_publisher ${catkin_LIBRARIES})

add_executable(create_agent 		src/create_agent.cpp)
target_link_libraries(create_agent 	${catkin_LIBRARIES})

add_executable(plan 				src/plan.cpp)
target_link_libraries(plan 			${catkin_LIBRARIES}
			   						${PROJECT_NAME})
