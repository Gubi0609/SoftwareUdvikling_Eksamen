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

vector<unique_ptr<Enemy>> PlainsDungeon::generateEnemyList(int level) {

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
    
    vector<unique_ptr<Enemy>> possibleEnemies;

    if (level <= 1) {
        possibleEnemies.emplace_back(make_unique<Wolf>());
        possibleEnemies.emplace_back(make_unique<Boar>());
        possibleEnemies.emplace_back(make_unique<Bandit>());
    } else if (level <= 3) {
        possibleEnemies.emplace_back(make_unique<Bandit>());
        possibleEnemies.emplace_back(make_unique<SmallTroll>());
    } else if (level == 4) {
        possibleEnemies.emplace_back(make_unique<AlphaDirewolf>()); // Boss fight
    } else if (level <= 5) {
        possibleEnemies.emplace_back(make_unique<SmallTroll>());
        possibleEnemies.emplace_back(make_unique<Troll>());
        possibleEnemies.emplace_back(make_unique<NomadArcher>());
    } else if (level == 6) {
        possibleEnemies.emplace_back(make_unique<WarlordMarauder>()); // Boss fight
    } else if (level <= 9) {
        possibleEnemies.emplace_back(make_unique<NomadArcher>());
        possibleEnemies.emplace_back(make_unique<WindSprite>());
        possibleEnemies.emplace_back(make_unique<Troll>());
        possibleEnemies.emplace_back(make_unique<Boar>());
    } else if (level <= 10) {
        possibleEnemies.emplace_back(make_unique<NomadArcher>());
        possibleEnemies.emplace_back(make_unique<WindSprite>());
        possibleEnemies.emplace_back(make_unique<AlphaDirewolf>());
    } else {
        possibleEnemies.emplace_back(make_unique<Wolf>());
        possibleEnemies.emplace_back(make_unique<Boar>());
        possibleEnemies.emplace_back(make_unique<Bandit>());
        possibleEnemies.emplace_back(make_unique<SmallTroll>());
        possibleEnemies.emplace_back(make_unique<Troll>());
        possibleEnemies.emplace_back(make_unique<NomadArcher>());
        possibleEnemies.emplace_back(make_unique<WindSprite>()); // All non-boss enemies
    }  possibleEnemies = {make_unique<Wolf>(), make_unique<Boar>(), make_unique<Bandit>(), make_unique<SmallTroll>(), make_unique<Troll>(), make_unique<NomadArcher>(), make_unique<WindSprite>()}; // All non-boss enemies

    vector<unique_ptr<Enemy>> selectedEnemies;

    if (possibleEnemies.size() > 1) { // If more than one enemy in list of possible enemies (not a boss fight), randomize choice.

        random_device rd; // Seed for random number generator
        mt19937 g(rd());  // Mersenne Twister random number generator
        uniform_int_distribution<> dist(0, possibleEnemies.size() - 1);

        enemyList.clear();

        for (int i = 0; i < 4; ++i) {
            int randomIndex = dist(g);
            selectedEnemies.push_back(move(possibleEnemies[randomIndex]));
        }

    } else {
        selectedEnemies = move(possibleEnemies); // Boss fight
    }

    enemyList = move(selectedEnemies);
    return move(selectedEnemies);
}