#ifndef DUNGEON_H
#define DUNGEON_H

#include "Enemy.h"
#include "Enemies.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Dungeon {

    public:
        Dungeon();
        Dungeon(string name, string description = "");
        virtual vector<Enemy*> generateEnemyList(int level);
        void modifyEnemyList(int position);
        
        vector<Enemy*> getEnemyList();
        string getName();
        int getGold();
        
        void showDescription();

        ~Dungeon();

    protected:
        string name;
        int gold;
        string description;
        int currentLevel;
        vector<Enemy*> enemyList;

};


#endif