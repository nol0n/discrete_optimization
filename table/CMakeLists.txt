cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(table)

add_library(table
	table.cpp
	table.hpp
)
target_include_directories(table PRIVATE 
	./
	./../rational_numbers
)
target_link_libraries(table PRIVATE
	rational_numbers
)

add_executable(table_test 
	main.cpp
)	
target_include_directories(table_test PRIVATE 
	./
	./../rational_numbers
)
target_link_libraries(table_test PRIVATE 
	table
	rational_numbers
)

configure_file(${CMAKE_SOURCE_DIR}/resources/test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)
