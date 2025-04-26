#include "CaveDungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

CaveDungeon::CaveDungeon() {
    name = "Default Cave Dungeon";
    gold = 0;
}

CaveDungeon::CaveDungeon(string name) : Dungeon(name) {}

vector<Enemy*> CaveDungeon::generateEnemyList(int level) {
    
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

    vector<Enemy*> possibleEnemies;

    if (level <= 1) {
        possibleEnemies = {new WeakGoblin(), new Goblin(), new GoblinGuard()};
    } else if (level <= 3) {
        possibleEnemies = {new UmbralCrawler(), new GoblinGuard()};
    } else if (level == 4) {
        possibleEnemies = {new GoblinKing()}; // Boss fight
    } else if (level <= 5) {
        possibleEnemies = {new UmbralCrawler(), new StoneGolem(), new PaleWatcher()};
    } else if (level == 6) {
        possibleEnemies = {new Gollum()}; // Boss fight
    } else if (level <= 7) {
        possibleEnemies = {new StoneGolem(), new PaleWatcher(), new CrystalWraith()};
    } else if (level <= 9) {
        possibleEnemies = {new CrystalWraith(), new PaleWatcher(), new UmbralCrawler()};
    } else if (level <= 10) {
        possibleEnemies = {new CrystalWraith(), new PaleWatcher(), new GoblinGuard()};
    } else {
        possibleEnemies = {new WeakGoblin(), new Goblin(), new GoblinGuard(), new UmbralCrawler(), new StoneGolem(), new PaleWatcher(), new CrystalWraith()}; // All non-boss enemies
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