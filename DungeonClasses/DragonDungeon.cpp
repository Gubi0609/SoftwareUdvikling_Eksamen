#include "DragonDungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

DragonDungeon::DragonDungeon() {
    name = "Dragon Dungeon";
    gold = 0;
    description = "High atop a jagged mountain peak, the Dragon's Lair looms — a cavernous hollow carved by fire and time.\nThe air is thin and cold, the paths treacherous with crumbling stone. Gold and ancient relics lie buried\nbeneath centuries of dust, but so too sleeps an ancient beast, whose wrath once shaped the world itself.";
    currentLevel = 11;
}

vector<Enemy*> DragonDungeon::generateEnemyList(int level) {
    /*
    A special case of the parent class Dungeon. DragonDungeon only has one enemy.
    */

    enemyList = enemyFactory.generateEnemyList(level, "Dragon");
    return enemyList;
}