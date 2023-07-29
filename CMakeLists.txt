
cmake_minimum_required(VERSION 3.2)

# set the project name
project(ceph)
find_package(Threads) 
set(CMAKE_CXX_FLAGS "-std=c++11 -O2 -pthread")

# add the executable
add_executable(main main.cc Thread.cc TImer.cc Mutex.cc )