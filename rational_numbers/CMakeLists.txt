cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(rational_numbers)

set(SRC 
	./source/rational.cpp
)

set(HEADERS 
	./include/rational.hpp
)

add_library(rational_numbers
	${SRC}
	${HEADERS}
)

target_link_libraries(rational_numbers
	PRIVATE BigInt
)
