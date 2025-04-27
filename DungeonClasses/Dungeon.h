#ifndef DUNGEON_H
#define DUNGEON_H

#include "../EnemyClasses/Enemy.h"
#include "../EnemyClasses/Enemies.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Dungeon {

    public:
        Dungeon();
        Dungeon(string name, string description = "");
        virtual vector<unique_ptr<Enemy>> generateEnemyList(int level);
        void modifyEnemyList(int position);
        
        vector<unique_ptr<Enemy>> getEnemyList();
        string getName();
        int getGold();
        
        void showDescription();

        ~Dungeon();

    protected:
        string name;
        int gold;
        string description;
        int currentLevel;
        vector<unique_ptr<Enemy>> enemyList;

};


#endif