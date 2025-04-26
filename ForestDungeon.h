#ifndef FORESTDUNGEON_H
#define FORESTDUNGEON_H

#include "Dungeon.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ForestDungeon : public Dungeon {

    public:
        ForestDungeon();
        ForestDungeon(string name);
        vector<Enemy*> generateEnemyList(int level) override;

    protected:

};

#endif