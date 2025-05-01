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
    
    vector<string> possibleEnemies;

    if (level <= 1) {
        possibleEnemies = {"Wolf", "SmallTroll", "Troll"};
    } else if (level <= 3) {
        possibleEnemies = {"WeakGoblin", "Goblin", "GoblinGuard"};
    } else if (level == 4) {
        possibleEnemies = {"GoblinKing"}; // Boss fight
    } else if (level <= 5) {
        possibleEnemies = {"WeakGoblin", "Goblin", "GoblinGuard"};
    } else if (level == 6) {
        possibleEnemies = {"Gollum"}; // Boss fight
    } else if (level <= 7) {
        possibleEnemies = {"Wolf", "SmallTroll", "Troll", "WeakGoblin", "Goblin"};
    } else if (level <= 9) {
        possibleEnemies = {"Spider", "GiantSpider", "Wolf"};
    } else if (level <= 10) {
        possibleEnemies = {"Wolf", "SmallTroll", "Troll"};
    } else if (level == 11) {
        possibleEnemies = {"Dragon"}; // Boss fight
    } else {
        possibleEnemies = {"Wolf", "SmallTroll", "Troll", "WeakGoblin", "Goblin", "GoblinGuard", "Spider", "GiantSpider"}; // All non-boss enemies
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

Enemy* Dungeon::createEnemy(string enemyType) {
    /*
    Creates an enemy based on given enemyType.
    :param enemyType: The type of enemy to create.
    :return: Returns a pointer to the created enemy.
    */
  
    // -- PLAINS -- //
    if (enemyType == "Wolf") {
        return new Wolf();
    } else if (enemyType == "Boar") {
        return new Boar();
    } else if (enemyType == "Bandit") {
        return new Bandit();
    } else if (enemyType == "SmallTroll") {
        return new SmallTroll();
    } else if (enemyType == "Troll") {
        return new Troll();
    } else if (enemyType == "NomadArcher") {
        return new NomadArcher();
    } else if (enemyType == "WindSprite") {
        return new WindSprite();
    } else if (enemyType == "AlphaDirewolf") {
        return new AlphaDirewolf();
    } else if (enemyType == "WarlordMarauder") {
        return new WarlordMarauder();
     
    // --- CAVE --- //
    } else if (enemyType == "WeakGoblin") {
        return new WeakGoblin();
    } else if (enemyType == "Goblin") {
        return new Goblin();
    } else if (enemyType == "GoblinGuard") {
        return new GoblinGuard();
    } else if (enemyType == "UmbralCrawler") {
        return new UmbralCrawler();
    } else if (enemyType == "StoneGolem") {
        return new StoneGolem();
    } else if (enemyType == "PaleWatcher") {
        return new PaleWatcher();
    } else if (enemyType == "CrystalWraith") {
        return new CrystalWraith();
    } else if (enemyType == "GoblinKing") {
        return new GoblinKing();
    } else if (enemyType == "Gollum") {
        return new Gollum();

    // --- FOREST --- //
    } else if (enemyType == "Spider") {
        return new Spider();
    } else if (enemyType == "GiantSpider") {
        return new GiantSpider();
    } else if (enemyType == "Bear") {
        return new Bear();
    } else if (enemyType == "Centaur") {
        return new Centaur();
    } else if (enemyType == "TreantSapling") {
        return new TreantSapling();
    } else if (enemyType == "ElvenRogue") {
        return new ElvenRogue();
    } else if (enemyType == "ForestWisp") {
        return new ForestWisp();
    } else if (enemyType == "CorruptedDryadQueen") {
        return new CorruptedDryadQueen();
    } else if (enemyType == "AncientTreant") {
        return new AncientTreant();

    // --- FINAL BOSS --- //
    } else if (enemyType == "Dragon") {
        return new Dragon();
    } else {
        cout << "Invalid enemy type!" << endl;
        return nullptr;
    }
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