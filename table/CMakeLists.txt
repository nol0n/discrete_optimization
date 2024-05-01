cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(table)

set(SOURCES 
	sources/table.cpp
)

set(HEADERS 
	headers/table.hpp
)

add_library(table
	${SOURCES}
	${HEADERS}
)

target_link_libraries(table PRIVATE
	rational_numbers
)
