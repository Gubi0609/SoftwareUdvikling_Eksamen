#include "Dungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

Dungeon::Dungeon() {
    name = "Default Dungeon";
    gold = 0;
}

Dungeon::Dungeon(string name, string description) {
    this->name = name;
    this->description = description;
}

vector<Enemy*> Dungeon::generateEnemyList(int level) {
    
    vector<Enemy*> possibleEnemies;

    if (level <= 1) {
        possibleEnemies = {new Wolf(), new SmallTroll(), new Troll()};
    } else if (level <= 3) {
        possibleEnemies = {new WeakGoblin(), new Goblin(), new GoblinGuard()};
    } else if (level == 4) {
        possibleEnemies = {new GoblinKing()}; // Boss fight
    } else if (level <= 5) {
        possibleEnemies = {new WeakGoblin(), new Goblin(), new GoblinGuard()};
    } else if (level == 6) {
        possibleEnemies = {new Gollum()}; // Boss fight
    } else if (level <= 7) {
        possibleEnemies = {new Wolf(), new SmallTroll(), new Troll(), new WeakGoblin(), new Goblin()};
    } else if (level <= 9) {
        possibleEnemies = {new Spider(), new GiantSpider(), new Wolf()};
    } else if (level <= 10) {
        possibleEnemies = {new Wolf(), new SmallTroll(), new Troll()};
    } else if (level == 11) {
        possibleEnemies = {new Dragon()}; //Boss fight
    } else {
        possibleEnemies = {new Wolf(), new SmallTroll(), new Troll(), new WeakGoblin(), new Goblin(), new GoblinGuard(), new Spider(), new GiantSpider()}; // All non-boss enemies
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

void Dungeon::modifyEnemyList(int position) {
    if (position >= 0 && position < enemyList.size()) {
        enemyList.erase(enemyList.begin() + position);
    } else {
        cout << "Invalid position!" << endl;
    }
}

vector<Enemy*> Dungeon::getEnemyList() {
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