#include "PlainsDungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

PlainsDungeon::PlainsDungeon() {
    name = "Default Plains Dungeon";
    gold = 0;
}

PlainsDungeon::PlainsDungeon(string name) : Dungeon(name) {}

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
    
    vector<Enemy*> possibleEnemies;

    if (level <= 1) {
        possibleEnemies = {new Wolf(), new Boar(), new Bandit()};
    } else if (level <= 3) {
        possibleEnemies = {new Bandit(), new SmallTroll()};
    } else if (level == 4) {
        possibleEnemies = {new AlphaDirewolf()}; // Boss fight
    } else if (level <= 5) {
        possibleEnemies = {new SmallTroll(), new Troll(), new NomadArcher()};
    } else if (level == 6) {
        possibleEnemies = {new WarlordMarauder()}; // Boss fight
    } else if (level <= 9) {
        possibleEnemies = {new NomadArcher(), new WindSprite(), new Troll(), new Boar()};
    } else if (level <= 10) {
        possibleEnemies = {new NomadArcher(), new WindSprite(), new AlphaDirewolf()};
    } else if (level == 11) {
        possibleEnemies = {new Dragon()}; // Boss fight
    } else {
        possibleEnemies = {new Wolf(), new Boar(), new Bandit(), new SmallTroll(), new Troll(), new NomadArcher(), new WindSprite()}; // All non-boss enemies
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