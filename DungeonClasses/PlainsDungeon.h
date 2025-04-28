#ifndef PLAINSDUNGEON_H
#define PLAINSDUNGEON_H

#include "Dungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class PlainsDungeon : public Dungeon {

    public:
        PlainsDungeon();
        vector<unique_ptr<Enemy>> generateEnemyList(int level) override;

    protected:

};

#endif