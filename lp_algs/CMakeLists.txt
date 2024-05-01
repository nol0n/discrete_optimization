cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lp_algs)

set(SOURCES 
	sources/lp_algs.cpp
)

set(HEADERS 
	headers/lp_algs.hpp
)

add_library(lp_algs
	${SOURCES}
	${HEADERS}
)

target_link_libraries(lp_algs PRIVATE
	table
)
