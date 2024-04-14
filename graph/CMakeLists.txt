cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(graph)

add_library(graph
	graph.cpp
	graph.hpp
)
target_include_directories(graph PRIVATE 
	./
	./../table
	./../rational_numbers
	./../lp_algs
)
target_link_libraries(graph PRIVATE
	rational_numbers
	lp_algs
	table
)

add_executable(graph_app 
	main.cpp
)	
target_include_directories(graph_app PRIVATE 
	./
	./../rational_numbers
	./../table
	./../lp_algs
)
target_link_libraries(graph_app PRIVATE 
	rational_numbers
	lp_algs
	table
)

configure_file(${CMAKE_SOURCE_DIR}/resources/test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)
