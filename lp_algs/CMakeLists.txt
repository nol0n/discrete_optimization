cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lp_algs)

set(SRC 
	./source/lp_algs.cpp
)

set(HEADERS 
	./include/lp_algs.hpp
)

add_library(lp_algs
	${SRC}
	${HEADERS}
)

target_link_libraries(lp_algs PRIVATE
	table
)
