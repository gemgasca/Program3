cmake_minimum_required(VERSION 3.14)
project(SearchNewBooks)

set(CMAKE_CXX_STANDARD 14)

add_executable(Program3 buildheap.cxx createheapoperationdata.cxx createteamdata.cxx createteams.cxx json.hpp priorityqueue.cpp priorityqueue.h teamdata.cpp teamdata.h)