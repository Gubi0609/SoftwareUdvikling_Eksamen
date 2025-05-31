#include "CaveDungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

CaveDungeon::CaveDungeon() {
    name = "Cave Dungeon";
    gold = 0;
    description = "A dark and damp cave, filled with the sounds of dripping water and distant growls.";
    currentLevel = 1;
}

vector<Enemy*> CaveDungeon::generateEnemyList(int level) {
    /*
    Uses EnemyFactory to generate a enemyList fitting to the cave theme and level
    :param level: The current level
    :return: A vector with enemy pointers.
    */

    /*
    -- CAVE --
[x] Weak Goblin 2 hp, 1 attackPower, 50 xp
[x] Goblin 3 hp, 1 attackPower, 75 xp
[x] Goblin guard 4 hp, 2 attackPower, 100 xp

[x] Umbral Crawler 2 hp, 5 attackPower, 150 xp
[x] Stone Golem 8 hp, 3 attackPower, 250 xp
[x] Pale Watcher 6 hp, 5 attackPower, 300 xp
[x] Crystal Wratih 10 hp, 3 attackPower, 350 xp

[x] Goblin king 20 hp, 5 attackPower, 4000 xp
[x] Gollum 30 hp, 5 attackPower, 6000 xp
    */

    enemyList = enemyFactory.generateEnemyList(level, "Cave");

    return enemyList;
}