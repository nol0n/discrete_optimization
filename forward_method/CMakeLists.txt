cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(forward_method)

add_library(forward_method
	forward_method.cpp
	forward_method.hpp
)

target_include_directories(forward_method
	PUBLIC /
)