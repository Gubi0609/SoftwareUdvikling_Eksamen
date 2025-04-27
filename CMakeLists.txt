cmake_minimum_required(VERSION 3.10)

# Project name and language
project(dungeonGame VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable (include all cpp files here)

# Automatically find all .cpp and .h files
file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

# Exclude files in the CMakeFiles directory
foreach(FILE ${SOURCES})
    if(${FILE} MATCHES ".*/CMakeFiles/.*")
        list(REMOVE_ITEM SOURCES ${FILE})
    endif()
endforeach()

# Add executable
add_executable(dungeonGame ${SOURCES})

# add_executable(dungeonGame
#     main.cpp
#     EnemyClasses/Enemy.cpp EnemyClasses/Enemy.h
#     EnemyClasses/Enemies.h
#     GameClass/Game.cpp GameClass/Game.h
#     HeroClass/Hero.cpp HeroClass/Hero.h
#     DungeonClasses/Dungeon.cpp DungeonClasses/Dungeon.h
#     DungeonClasses/ForestDungeon.cpp DungeonClasses/ForestDungeon.h
#     DungeonClasses/PlainsDungeon.cpp DungeonClasses/PlainsDungeon.h
#     DungeonClasses/CaveDungeon.cpp DungeonClasses/CaveDungeon.h
#     DungeonClasses/DragonDungeon.cpp DungeonClasses/DragonDungeon.h
# )
