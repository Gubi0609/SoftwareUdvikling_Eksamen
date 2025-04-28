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
    
    vector<string> possibleEnemies;

    if (level <= 1) {
        possibleEnemies = {"Wolf", "Boar", "Bandit"};
    } else if (level <= 3) {
        possibleEnemies = {"Bandit", "SmallTroll"};
    } else if (level == 4) {
        possibleEnemies = {"AlphaDirewolf"}; // Boss fight
    } else if (level <= 5) {
        possibleEnemies = {"SmallTroll", "Troll", "NomadArcher"};
    } else if (level == 6) {
        possibleEnemies = {"WarlordMarauder"}; // Boss fight
    } else if (level <= 9) {
        possibleEnemies = {"NomadArcher", "WindSprite", "Troll", "Boar"};
    } else if (level <= 10) {
        possibleEnemies = {"NomadArcher", "WindSprite", "AlphaDirewolf"};
    } else {
        possibleEnemies = {"Wolf", "Boar", "Bandit", "SmallTroll", "Troll", "NomadArcher", "WindSprite"}; // All non-boss enemies
    }

    if (possibleEnemies.size() > 1) { // If more than one enemy in list of possible enemies (not a boss fight), randomize choice.

        random_device rd; // Seed for random number generator
        mt19937 g(rd());  // Mersenne Twister random number generator
        uniform_int_distribution<> dist(0, possibleEnemies.size() - 1);

        enemyList.clear();

        for (int i = 0; i < 4; ++i) {
            int randomIndex = dist(g);
            enemyList.push_back(createEnemy(possibleEnemies[randomIndex]));
        }

    } else {
        if (enemyList.size() > 0) {
            enemyList.clear();
        }
        enemyList.push_back(createEnemy(possibleEnemies[0])); // Boss fight
    }

    return enemyList;
}