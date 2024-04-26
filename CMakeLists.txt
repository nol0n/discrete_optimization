cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

project(LinearProgrammingAlgs)

include_directories(
	./external/BigInt/include
	./rational_numbers/include
	./table/include
	./lp_algs/include
	./perfomance_collection/include
)

add_subdirectory(
	./external/BigInt
)

add_subdirectory(
	rational_numbers
)

add_subdirectory(
	table
)

add_subdirectory(
	lp_algs
)

add_subdirectory(
	perfomance_collection
)

add_subdirectory(
	application
)
