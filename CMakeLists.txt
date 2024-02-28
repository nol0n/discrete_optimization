cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(app)

add_executable(app
	main.cpp
)

add_subdirectory(
	lp_methods
)

target_include_directories(app
	PRIVATE ./lp_methods
)

target_link_libraries(app
	PRIVATE lp_methods
)