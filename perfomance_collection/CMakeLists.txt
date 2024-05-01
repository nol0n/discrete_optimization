cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# lib with perf collection

project(perfomance_collection)

set(SOURCES 
	sources/perf.cpp
)

set(HEADERS
	headers/perf.hpp
) 

add_library(perfomance_collector
	${SOURCES}
	${HEADERS}
)

target_link_libraries(perfomance_collector PRIVATE
	table
)
