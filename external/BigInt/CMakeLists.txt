cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(BigInt)

set(SOURCES 
	sources/BigInt.cpp
)

set(HEADERS 
	headers/BigInt.hpp
)

add_library(BigInt
	${SOURCES}
	${HEADERS}
)
