cmake_minimum_required(VERSION 3.6)
project(assembler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES assembler/main.cpp assembler/firstPass.cpp assembler/secondPass.cpp assembler/wombat2IS.cpp)
add_executable(asdasd ${SOURCE_FILES})