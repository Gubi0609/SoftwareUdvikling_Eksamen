#include "ForestDungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

ForestDungeon::ForestDungeon() {
    name = "Default Forest Dungeon";
    gold = 0;
}

ForestDungeon::ForestDungeon(string name) : Dungeon(name) {}

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
    
    vector<Enemy*> possibleEnemies;

    if (level <= 1) {
        possibleEnemies = {new Spider(), new GiantSpider(), new Bear()};
    } else if (level <= 3) {
        possibleEnemies = {new Bear(), new Centaur()};
    } else if (level == 4) {
        possibleEnemies = {new CorruptedDryadQueen()}; // Boss fight
    } else if (level <= 5) {
        possibleEnemies = {new Centaur(), new ElvenRogue(), new ForestWisp()}; 
    } else if (level == 6) {
        possibleEnemies = {new AncientTreant()}; // Boss fight
    } else if (level <= 9) {
        possibleEnemies = {new ElvenRogue(), new ForestWisp(), new Centaur(), new GiantSpider()}; 
    } else if (level <= 10) {
        possibleEnemies = {new ElvenRogue(), new ForestWisp(), new CorruptedDryadQueen()};
    } else if (level == 11) {
        possibleEnemies = {new Dragon()}; //Boss fight
    } else {
        possibleEnemies = {new Spider(), new GiantSpider(), new Bear(), new Centaur(), new ElvenRogue(), new ForestWisp()}; // All non-boss enemies
    }

    if (possibleEnemies.size() > 1) { // If more than one enemy in list of possible enemies (not a boss fight), randomize choice.

        random_device rd; // Seed for random number generator
        mt19937 g(rd());  // Mersenne Twister random number generator
        uniform_int_distribution<> dist(0, possibleEnemies.size() - 1);

        enemyList.clear();

        for (int i = 0; i < 4; ++i) {
            int randomIndex = dist(g);
            enemyList.push_back(possibleEnemies[randomIndex]);
        }

    } else {
        enemyList = possibleEnemies; // Boss fight
    }

    return enemyList;
}