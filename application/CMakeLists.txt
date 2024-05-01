cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(apps)

# rational numbers test

add_executable(rational_test
	rational_test.cpp
)

target_link_libraries(rational_test PRIVATE 
	rational_numbers
)

# table class test

add_executable(table_test
	table_test.cpp
)

target_link_libraries(table_test PRIVATE 
	rational_numbers
	table
)

# app for perfomance testing

add_executable(perf_app
	perf_app.cpp
)

target_link_libraries(perf_app PRIVATE 
	rational_numbers
	table
	lp_algs
	lp_algs_dev
	perfomance_collector
)

# main app

add_executable(lp_app
	main.cpp
)

target_link_libraries(lp_app PRIVATE 
	rational_numbers
	table
	lp_algs
	lp_algs_dev
)

# adding test files to binaries

configure_file(${CMAKE_SOURCE_DIR}/resources/test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)
file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/output.txt)
