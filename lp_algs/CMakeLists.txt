cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lp_algs)

add_library(lp_algs
	lp_algs.cpp
	lp_algs.hpp
)
target_include_directories(lp_algs PRIVATE 
	./
)
