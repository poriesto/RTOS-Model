cmake_minimum_required(VERSION 2.8)

set (PROJECT OsModel)
project (${PROJECT})
include_directories (../)

set (HEADERS
		include/os.hpp)
set (SOURCES
		src/os.cpp
		src/main.cpp)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
add_executable(bin/${PROJECT} ${HEADERS} ${SOURCES})
