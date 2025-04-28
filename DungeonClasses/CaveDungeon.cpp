#include "CaveDungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>

using namespace std;

CaveDungeon::CaveDungeon() {
    name = "Cave Dungeon";
    gold = 0;
    description = "A dark and damp cave, filled with the sounds of dripping water and distant growls.";
    currentLevel = 1;
}

vector<unique_ptr<Enemy>> CaveDungeon::generateEnemyList(int level) {

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

    vector<unique_ptr<Enemy>> possibleEnemies;

    if (level <= 1) {
        possibleEnemies.emplace_back(make_unique<WeakGoblin>());
        possibleEnemies.emplace_back(make_unique<Goblin>());
        possibleEnemies.emplace_back(make_unique<GoblinGuard>());
    } else if (level <= 3) {
        possibleEnemies.emplace_back(make_unique<UmbralCrawler>());
        possibleEnemies.emplace_back(make_unique<GoblinGuard>());
    } else if (level == 4) {
        possibleEnemies.emplace_back(make_unique<GoblinKing>()); // Boss fight
    } else if (level <= 5) {
        possibleEnemies.emplace_back(make_unique<UmbralCrawler>());
        possibleEnemies.emplace_back(make_unique<StoneGolem>());
        possibleEnemies.emplace_back(make_unique<PaleWatcher>());
    } else if (level == 6) {
        possibleEnemies.emplace_back(make_unique<Gollum>()); // Boss fight
    } else if (level <= 7) {
        possibleEnemies.emplace_back(make_unique<StoneGolem>());
        possibleEnemies.emplace_back(make_unique<PaleWatcher>());
        possibleEnemies.emplace_back(make_unique<CrystalWraith>());
    } else if (level <= 9) {
        possibleEnemies.emplace_back(make_unique<CrystalWraith>());
        possibleEnemies.emplace_back(make_unique<PaleWatcher>());
        possibleEnemies.emplace_back(make_unique<UmbralCrawler>());
    } else if (level <= 10) {
        possibleEnemies.emplace_back(make_unique<CrystalWraith>());
        possibleEnemies.emplace_back(make_unique<PaleWatcher>());
        possibleEnemies.emplace_back(make_unique<GoblinGuard>());
    } else {
        possibleEnemies.emplace_back(make_unique<WeakGoblin>());
        possibleEnemies.emplace_back(make_unique<Goblin>());
        possibleEnemies.emplace_back(make_unique<GoblinGuard>());
        possibleEnemies.emplace_back(make_unique<UmbralCrawler>());
        possibleEnemies.emplace_back(make_unique<StoneGolem>());
        possibleEnemies.emplace_back(make_unique<PaleWatcher>());
        possibleEnemies.emplace_back(make_unique<CrystalWraith>()); // All non-boss enemies
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
    return move(enemyList);
}