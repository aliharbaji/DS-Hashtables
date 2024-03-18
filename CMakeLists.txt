cmake_minimum_required(VERSION 3.24)
project(Wet2_DS)

set(CMAKE_CXX_STANDARD 14)

add_executable(Wet2_DS
        main.cpp Hashtable.h Team.cpp Team.h Player.cpp Player.h
        olympics24a2.cpp olympics24a2.h )
