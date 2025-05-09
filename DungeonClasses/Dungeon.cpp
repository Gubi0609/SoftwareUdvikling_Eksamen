#include "Dungeon.h"

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

vector<Enemy*> Dungeon::generateEnemyList(int level) {
    /*
    Generates a list of enemies based on the current level.
    If not a boss level, the enemies are randomized, and 4 enemies are selected.
    :param level: The current level
    :return: A vector with enemy pointers.
    */
    
    enemyList = enemyFactory.generateEnemyList(level, "Plains");

    return enemyList;
    
}

void Dungeon::modifyEnemyList(int position) {
    /*
    Deletes the enemy at a given position of the enemyList vector.
    :param position: The 0-index position of the enemy.
    */
    if (position >= 0 && position < enemyList.size()) {
        enemyList.erase(enemyList.begin() + position);
    } else {
        cout << "Invalid position!" << endl;
    }
}

vector<Enemy*> Dungeon::getEnemyList() const {
    return enemyList;
}

int Dungeon::getGold() {
    /*
    Calculates amount of gold in dungeon based on the XP of enemies in dungeon.
    :return: Returns the amount of gold in dungeon.
    */

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
    /*
    Prints the dungeon name and description to terminal.
    */
    cout << "Dungeon: " << name << endl;
    cout << description << endl;
    cout << "--------------------------------" << endl;
}

Dungeon::~Dungeon() {}