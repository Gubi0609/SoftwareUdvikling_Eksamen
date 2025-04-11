cmake_minimum_required(VERSION 3.10)

# Project name and language
project(dungeonGame VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable (include all cpp files here)
add_executable(dungeonGame
    main.cpp
    Enemy.cpp Enemy.h
    Enemies.h
    Game.cpp Game.h
    Hero.cpp Hero.h
)
