#include "EnemyFactory.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

EnemyFactory::EnemyFactory() {}

vector<Enemy*> EnemyFactory::generateEnemyList(int level, string dungeonType) {

    vector<string> possibleEnemies;

    if (dungeonType == "Forest") {
        
        if (level <= 1) {
            possibleEnemies = {"Spider", "GiantSpider", "Bear"};
        } else if (level <= 3) {
            possibleEnemies = {"Bear", "Centaur"};
        } else if (level == 4) {
            possibleEnemies = {"CorruptedDryadQueen"}; // Boss fight
        } else if (level <= 5) {
            possibleEnemies = {"Centaur", "ElvenRogue", "ForestWisp"};
        } else if (level == 6) {
            possibleEnemies = {"AncientTreant"}; // Boss fight
        } else if (level <= 9) {
            possibleEnemies = {"ElvenRogue", "ForestWisp", "Centaur", "GiantSpider"};
        } else if (level <= 10) {
            possibleEnemies = {"ElvenRogue", "ForestWisp", "CorruptedDryadQueen"};
        } else if (level == 11) {
            possibleEnemies = {"Dragon"}; // Boss fight
        } else {
            possibleEnemies = {"Spider", "GiantSpider", "Bear", "Centaur", "ElvenRogue", "ForestWisp"}; // All non-boss enemies
        }

    } else if (dungeonType == "Plains") {
        
        if (level <= 1) {
            possibleEnemies = {"Wolf", "Boar", "Bandit"};
        } else if (level <= 3) {
            possibleEnemies = {"Bandit", "SmallTroll"};
        } else if (level == 4) {
            possibleEnemies = {"AlphaDirewolf"}; // Boss fight
        } else if (level <= 5) {
            possibleEnemies = {"SmallTroll", "Troll", "NomadArcher"};
        } else if (level == 6) {
            possibleEnemies = {"WarlordMarauder"}; // Boss fight
        } else if (level <= 9) {
            possibleEnemies = {"NomadArcher", "WindSprite", "Troll", "Boar"};
        } else if (level <= 10) {
            possibleEnemies = {"NomadArcher", "WindSprite", "AlphaDirewolf"};
        } else {
            possibleEnemies = {"Wolf", "Boar", "Bandit", "SmallTroll", "Troll", "NomadArcher", "WindSprite"}; // All non-boss enemies
        }

    } else if (dungeonType == "Cave") {

        if (level <= 1) {
            possibleEnemies = {"WeakGoblin", "Goblin", "GoblinGuard"};
        } else if (level <= 3) {
            possibleEnemies = {"UmbralCrawler", "GoblinGuard"};
        } else if (level == 4) {
            possibleEnemies = {"GoblinKing"}; // Boss fight
        } else if (level <= 5) {
            possibleEnemies = {"UmbralCrawler", "StoneGolem", "PaleWatcher"};
        } else if (level == 6) {
            possibleEnemies = {"Gollum"}; // Boss fight
        } else if (level <= 7) {
            possibleEnemies = {"StoneGolem", "PaleWatcher", "CrystalWraith"};
        } else if (level <= 9) {
            possibleEnemies = {"CrystalWraith", "PaleWatcher", "UmbralCrawler"};
        } else if (level <= 10) {
            possibleEnemies = {"CrystalWraith", "PaleWatcher", "GoblinGuard"};
        } else {
            possibleEnemies = {"WeakGoblin", "Goblin", "GoblinGuard", "UmbralCrawler", "StoneGolem", "PaleWatcher", "CrystalWraith"}; // All non-boss enemies
        }

    } else if (dungeonType == "Dragon") {
        possibleEnemies = {"Dragon"};
    } else {
        cout << "Invalid dungeon type!" << endl;
        return {};
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

vector<Enemy*> EnemyFactory::getEnemyList() const {
    return enemyList;
}

void EnemyFactory::modifyEnemyList(int position) {
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

Enemy* EnemyFactory::createEnemy(string enemyType) {
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