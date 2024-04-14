cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(app)

add_executable(app
	main.cpp
)

target_include_directories(app PRIVATE 
	./../lp_algs
	./../rational_numbers
	./../lp_methods
	./../table
)

target_link_libraries(app PRIVATE 
	lp_algs
	rational_numbers
	table
	lp_methods
)

configure_file(${CMAKE_SOURCE_DIR}/resources/test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)
