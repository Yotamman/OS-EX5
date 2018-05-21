cmake_minimum_required(VERSION 3.10)
project(oshw5)

set(CMAKE_CXX_STANDARD 11)

add_executable(oshw5 main.cpp Task.cpp Task.h SafeQ.h ThreadPool.cpp ThreadPool.h Requesters.cpp Requesters.h ReadFile.cpp ReadFile.h Resolvers.cpp Resolvers.h)