cmake_minimum_required(VERSION 3.5)

project(testing_derivatives LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(testing_derivatives main.cpp
                      derivatives.cpp derivatives.h
                      Grid.cpp Grid.h
                      input_output.cpp input_output.h
                      initialization.cpp initialization.h)

set(CMAKE_CXX_FLAGS "-lconfig++")
