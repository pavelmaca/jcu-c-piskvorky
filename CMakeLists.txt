cmake_minimum_required(VERSION 3.5)
project(Piskvorky)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        src/Engine.h
        src/Player.h
        src/Gui.h src/Gui.cpp
        src/Storage.h src/Storage.cpp
        src/InputReader.h src/InputReader.cpp
        src/AI.h  src/AI.cpp
        src/Coordinates.h
        src/CoordinatesBlock.cpp src/CoordinatesBlock.h
        src/WinException.h)
add_executable(Piskvorky ${SOURCE_FILES})