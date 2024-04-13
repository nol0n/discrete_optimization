cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

project(app)

add_executable(app
	main.cpp
)

add_subdirectory(
	lp_methods
)

add_subdirectory(
	rational_numbers
)

target_include_directories(app PRIVATE 
	./lp_methods
	./rational_numbers
)

target_link_libraries(app PRIVATE 
	lp_methods
	rational_numbers
)