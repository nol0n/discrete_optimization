cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lp_algs_dev)

set(SRC 
	./source/lp_algs_dev.cpp
)

set(HEADERS 
	./include/lp_algs_dev.hpp
)

add_library(lp_algs_dev
	${SRC}
	${HEADERS}
)

target_link_libraries(lp_algs_dev PRIVATE
	table
)
