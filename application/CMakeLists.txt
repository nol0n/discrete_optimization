cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(apps)

add_executable(rational_test
	rational_test.cpp
)

target_link_libraries(rational_test PRIVATE 
	rational_numbers
)

add_executable(table_test
	table_test.cpp
)

target_link_libraries(table_test PRIVATE 
	rational_numbers
	table
)

add_executable(perf_app
	perf_app.cpp
)

target_link_libraries(perf_app PRIVATE 
	rational_numbers
	table
	lp_algs
	perfomance_collector
)

add_executable(lp_app
	main.cpp
)

target_link_libraries(lp_app PRIVATE 
	rational_numbers
	table
	lp_algs
)

configure_file(${CMAKE_SOURCE_DIR}/resources/test.txt ${CMAKE_CURRENT_BINARY_DIR}/test.txt COPYONLY)
file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/output.txt)
