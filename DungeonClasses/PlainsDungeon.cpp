#include "PlainsDungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

PlainsDungeon::PlainsDungeon() {
    name = "Plains Dungeon";
    gold = 0;
    description = "A vast and open expanse, where the wind howls and danger lurks in the tall grass.";
    currentLevel = 1;
}

vector<Enemy*> PlainsDungeon::generateEnemyList(int level) {
    /*
    Uses EnemyFactory to generate a enemyList fitting to the cave theme and level
    :param level: The current level
    :return: A vector with enemy pointers.
    */

    /*
    -- PLAINS --
[x] Wolf 2 hp, 1 attackPower, 50 xp
[x] Boar 4 hp, 1 attackPower, 75 xp
[x] Bandit 3 hp, 2 attackPower, 100 xp
[x] Small troll 6 hp, 3 attackPower, 150 xp
[x] Troll 8 hp, 4 attackPower, 250 xp
[x] Nomad Archer 6 hp, 5 attackPower, 300 xp
[x] Wind Sprite 10 hp, 3 attackPower, 350 xp

[x] Alpha Direwolf 20 hp, 5 attackPower, 4000 xp
[x] Warlord Marauder 30 hp, 5 attackPower, 6000 xp

    */
    
    enemyList = enemyFactory.generateEnemyList(level, "Plains");

    return enemyList;
}