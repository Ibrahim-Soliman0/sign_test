cmake_minimum_required(VERSION 3.30)
project(Sign_Test)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(Sign_Test main.cpp)

target_link_libraries(Sign_Test PRIVATE ws2_32)