#ifndef FORESTDUNGEON_H
#define FORESTDUNGEON_H

#include "Dungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class ForestDungeon : public Dungeon {

    public:
        ForestDungeon();
        vector<unique_ptr<Enemy>> generateEnemyList(int level) override;

    protected:

};

#endif