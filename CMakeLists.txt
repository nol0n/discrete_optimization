cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(app)

add_executable(app
	main.cpp
)

add_subdirectory(
	forward_method
)

target_link_libraries(app
	PRIVATE forward_method
)