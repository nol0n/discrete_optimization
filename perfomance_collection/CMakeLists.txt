cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(perfomance_collection)

add_library(perfomance_collection
	perf.cpp
	perf.hpp
)
target_include_directories(perfomance_collection PRIVATE 
	./
	./../table
	./../rational_numbers
	./../lp_algs
)
target_link_libraries(perfomance_collection PRIVATE
	rational_numbers
	lp_algs
	table
)

add_executable(perfomance_collector 
	main.cpp
)	
target_include_directories(perfomance_collector PRIVATE 
	./
	./../rational_numbers
	./../table
	./../lp_algs
)
target_link_libraries(perfomance_collector PRIVATE 
	rational_numbers
	lp_algs
	table
)

configure_file(${CMAKE_SOURCE_DIR}/resources/test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)
