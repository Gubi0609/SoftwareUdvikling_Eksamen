#include "Dungeon.h"
#include "../EnemyClasses/Enemy.h"
#include "../EnemyClasses/Enemies.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>

using namespace std;

Dungeon::Dungeon() {
    name = "Default Dungeon";
    gold = 0;
}

Dungeon::Dungeon(string name, string description) {
    this->name = name;
    this->description = description;
}

vector<unique_ptr<Enemy>> Dungeon::generateEnemyList(int level) {
    
    vector<unique_ptr<Enemy>> possibleEnemies;

    if (level <= 1) {
        possibleEnemies.emplace_back(make_unique<Wolf>());
        possibleEnemies.emplace_back(make_unique<SmallTroll>());
        possibleEnemies.emplace_back(make_unique<Troll>());
    } else if (level <= 3) {
        possibleEnemies.emplace_back(make_unique<WeakGoblin>());
        possibleEnemies.emplace_back(make_unique<Goblin>());
        possibleEnemies.emplace_back(make_unique<GoblinGuard>());
    } else if (level == 4) {
        possibleEnemies.emplace_back(make_unique<GoblinKing>()); // Boss fight
    } else if (level <= 5) {
        possibleEnemies.emplace_back(make_unique<WeakGoblin>());
        possibleEnemies.emplace_back(make_unique<Goblin>());
        possibleEnemies.emplace_back(make_unique<GoblinGuard>());
    } else if (level == 6) {
        possibleEnemies.emplace_back(make_unique<Gollum>()); // Boss fight
    } else if (level <= 7) {
        possibleEnemies.emplace_back(make_unique<Wolf>());
        possibleEnemies.emplace_back(make_unique<SmallTroll>());
        possibleEnemies.emplace_back(make_unique<Troll>());
        possibleEnemies.emplace_back(make_unique<WeakGoblin>());
        possibleEnemies.emplace_back(make_unique<Goblin>());
    } else if (level <= 9) {
        possibleEnemies.emplace_back(make_unique<Spider>());
        possibleEnemies.emplace_back(make_unique<GiantSpider>());
        possibleEnemies.emplace_back(make_unique<Wolf>());
    } else if (level <= 10) {
        possibleEnemies.emplace_back(make_unique<Wolf>());
        possibleEnemies.emplace_back(make_unique<SmallTroll>());
        possibleEnemies.emplace_back(make_unique<Troll>());
    } else {
        possibleEnemies.emplace_back(make_unique<Wolf>());
        possibleEnemies.emplace_back(make_unique<SmallTroll>());
        possibleEnemies.emplace_back(make_unique<Troll>());
        possibleEnemies.emplace_back(make_unique<WeakGoblin>());
        possibleEnemies.emplace_back(make_unique<Goblin>());
        possibleEnemies.emplace_back(make_unique<GoblinGuard>());
        possibleEnemies.emplace_back(make_unique<Spider>());
        possibleEnemies.emplace_back(make_unique<GiantSpider>()); // All non-boss enemies
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
    return enemyList;

}

void Dungeon::modifyEnemyList(int position) {
    if (position >= 0 && position < enemyList.size()) {
        enemyList.erase(enemyList.begin() + position);
    } else {
        cout << "Invalid position!" << endl;
    }
}

vector<unique_ptr<Enemy>> Dungeon::getEnemyList() const {
    return enemyList;
}

int Dungeon::getGold() {

    gold = 0;

    for (int i = 0; i < enemyList.size(); i++) {
        gold += enemyList[i]->getXP();
    }

    gold = gold / 10; // Divide by 10 to get the gold amount
    if (gold < 0) {
        gold = 0; // Ensure gold is not negative
    }

    return gold;
}

string Dungeon::getName() {
    return name;
}

void Dungeon::showDescription() {
    cout << "Dungeon: " << name << endl;
    cout << description << endl;
    cout << "--------------------------------" << endl;
}

Dungeon::~Dungeon() {}