cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

project(LinearProgrammingAlgs)

add_subdirectory(
	application
)

add_subdirectory(
	lp_methods
)

add_subdirectory(
	lp_algs
)

add_subdirectory(
	rational_numbers
)

add_subdirectory(
	table
)

add_subdirectory(
	perfomance_collection
)
