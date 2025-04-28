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
    
    vector<string> possibleEnemies;

    if (level <= 1) {
        possibleEnemies = {"Spider", "GiantSpider", "Bear"};
    } else if (level <= 3) {
        possibleEnemies = {"Bear", "Centaur"};
    } else if (level == 4) {
        possibleEnemies = {"CorruptedDryadQueen"}; // Boss fight
    } else if (level <= 5) {
        possibleEnemies = {"Centaur", "ElvenRogue", "ForestWisp"};
    } else if (level == 6) {
        possibleEnemies = {"AncientTreant"}; // Boss fight
    } else if (level <= 9) {
        possibleEnemies = {"ElvenRogue", "ForestWisp", "Centaur", "GiantSpider"};
    } else if (level <= 10) {
        possibleEnemies = {"ElvenRogue", "ForestWisp", "CorruptedDryadQueen"};
    } else if (level == 11) {
        possibleEnemies = {"Dragon"}; // Boss fight
    } else {
        possibleEnemies = {"Spider", "GiantSpider", "Bear", "Centaur", "ElvenRogue", "ForestWisp"}; // All non-boss enemies
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