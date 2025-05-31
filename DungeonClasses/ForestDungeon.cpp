#include "ForestDungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

ForestDungeon::ForestDungeon() {
    name = "Forest Dungeon";
    gold = 0;
    description = "A dark and twisted forest, filled with ancient trees and lurking dangers.";
    currentLevel = 1;
}

vector<Enemy*> ForestDungeon::generateEnemyList(int level) {
    /*
    Uses EnemyFactory to generate a enemyList fitting to the cave theme and level
    :param level: The current level
    :return: A vector with enemy pointers.
    */

    /*
    -- FOREST --
[x] Spider 2 hp, 1 attackPower, 50 xp
[x] Giant spider 4 hp, 1 attackPower, 75 xp
[x] Bear 3 hp, 2 attackPower, 100 xp
[x] Centaur, 6 hp, 3 attackPower, 150 xp
[x] Treant Sapling 8 hp, 4 attackPower, 250 xp
[x] Elven Rogue 6 hp, 5 attackPower, 300 xp
[x] Forest Wisp 10 hp, 3 attackPower, 350 xp

[x] Corrupted Dryad Queen 20 hp, 5 attackPower, 4000 xp
[x] Ancient Treant 30 hp, 5 attackPower, 6000 xp
    */
    
    enemyList = enemyFactory.generateEnemyList(level, "Forest");

    return enemyList;
}