cmake_minimum_required(VERSION 3.5)

project(RL_NSE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RL_NSE main.cpp
                      input_output.cpp input_output.h
                      initialization.cpp initialization.h
                      memory_management.cpp memory_management.h
                      time_stepping.cpp time_stepping.h
                      pressure_calculation.cpp pressure_calculation.h
                      boundary_conditions.cpp boundary_conditions.h
                      config.cfg)

set(CMAKE_CXX_FLAGS "-lconfig++")
