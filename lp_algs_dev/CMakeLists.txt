cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lp_algs_dev)

set(SOURCES 
	sources/lp_algs_dev.cpp
)

set(HEADERS 
	headers/lp_algs_dev.hpp
)

add_library(lp_algs_dev
	${SOURCES}
	${HEADERS}
)

target_link_libraries(lp_algs_dev PRIVATE
	table
)
