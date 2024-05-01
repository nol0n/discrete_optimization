cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(rational_numbers)

set(SOURCES 
	sources/rational.cpp
)

set(HEADERS 
	headers/rational.hpp
)

add_library(rational_numbers
	${SOURCES}
	${HEADERS}
)

target_link_libraries(rational_numbers PRIVATE 
	BigInt
)
