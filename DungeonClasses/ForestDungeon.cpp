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

vector<unique_ptr<Enemy>> ForestDungeon::generateEnemyList(int level) {

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
    
    vector<unique_ptr<Enemy>> possibleEnemies;

    if (level <= 1) {
        possibleEnemies.emplace_back(make_unique<Spider>());
        possibleEnemies.emplace_back(make_unique<GiantSpider>());
        possibleEnemies.emplace_back(make_unique<Bear>());
    } else if (level <= 3) {
        possibleEnemies.emplace_back(make_unique<Bear>());
        possibleEnemies.emplace_back(make_unique<Centaur>());
    } else if (level == 4) {
        possibleEnemies.emplace_back(make_unique<CorruptedDryadQueen>()); // Boss fight
    } else if (level <= 5) {
        possibleEnemies.emplace_back(make_unique<Centaur>());
        possibleEnemies.emplace_back(make_unique<ElvenRogue>());
        possibleEnemies.emplace_back(make_unique<ForestWisp>());
    } else if (level == 6) {
        possibleEnemies.emplace_back(make_unique<AncientTreant>()); // Boss fight
    } else if (level <= 9) {
        possibleEnemies.emplace_back(make_unique<ElvenRogue>());
        possibleEnemies.emplace_back(make_unique<ForestWisp>());
        possibleEnemies.emplace_back(make_unique<Centaur>());
        possibleEnemies.emplace_back(make_unique<GiantSpider>());
    } else if (level <= 10) {
        possibleEnemies.emplace_back(make_unique<ElvenRogue>());
        possibleEnemies.emplace_back(make_unique<ForestWisp>());
        possibleEnemies.emplace_back(make_unique<CorruptedDryadQueen>());
    } else {
        possibleEnemies.emplace_back(make_unique<Spider>());
        possibleEnemies.emplace_back(make_unique<GiantSpider>());
        possibleEnemies.emplace_back(make_unique<Bear>());
        possibleEnemies.emplace_back(make_unique<Centaur>());
        possibleEnemies.emplace_back(make_unique<ElvenRogue>());
        possibleEnemies.emplace_back(make_unique<ForestWisp>()); // All non-boss enemies
    }

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