cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# lib with perf collection

project(perfomance_collection)

set(SRC 
	./source/perf.cpp
)

set(HEADERS
	./include/perf.hpp
) 

add_library(perfomance_collector
	${SRC}
	${HEADERS}
)

target_link_libraries(perfomance_collector
	table
)
