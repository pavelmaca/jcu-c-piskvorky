cmake_minimum_required(VERSION 3.5)
project(Piskvorky)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/Engine.h src/Player.h src/Gui.h src/Storage.h)
add_executable(Piskvorky ${SOURCE_FILES})