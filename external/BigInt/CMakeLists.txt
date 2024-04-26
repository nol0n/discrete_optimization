cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(BigInt)

set(SRC 
	./source/BigInt.cpp
)

set(HEADERS 
	./include/BigInt.hpp
)

add_library(BigInt
	${SRC}
	${HEADERS}
)
