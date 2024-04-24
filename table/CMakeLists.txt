cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(table)

set(SRC 
	./source/table.cpp
)

set(HEADERS 
	./include/table.hpp
)

add_library(table
	${SRC}
	${HEADERS}
)

target_link_libraries(table PRIVATE
	rational_numbers
)
