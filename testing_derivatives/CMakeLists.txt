cmake_minimum_required(VERSION 3.5)

project(Testaufgaben LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Testaufgaben main.cpp
                      derivatives.cpp derivatives.h)

set(CMAKE_CXX_FLAGS "-lconfig++")
