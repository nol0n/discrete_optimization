cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# lib with perf collection

project(perfomance_collection)

add_library(perfomance_collector
	perf.cpp
	perf.hpp
)
target_include_directories(perfomance_collector PRIVATE 
	./
)

# app for testing

add_executable(perf 
	main.cpp
)	
target_include_directories(perf PRIVATE 
	./
	./../rational_numbers
	./../table
	./../lp_algs
	./../perfomance_collection
)
target_link_libraries(perf PRIVATE 
	rational_numbers
	lp_algs
	table
	perfomance_collector
)

configure_file(${CMAKE_SOURCE_DIR}/resources/test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)
file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/output.txt)