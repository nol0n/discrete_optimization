cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(rational_numbers)

add_library(rational_numbers
	rational.cpp
	rational.hpp
)

target_include_directories(rational_numbers
	PRIVATE /
)

add_executable(rational_test
	main.cpp
)

target_include_directories(rational_test PRIVATE 
	/
)

target_link_libraries(rational_test PRIVATE 
	rational_numbers
)