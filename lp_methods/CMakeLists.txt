cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lp_methods)

add_library(lp_methods
	lp_methods.cpp
	lp_methods.hpp
)
target_include_directories(lp_methods PRIVATE 
	./
)
