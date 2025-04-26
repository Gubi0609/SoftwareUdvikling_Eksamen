#ifndef PLAINSDUNGEON_H
#define PLAINSDUNGEON_H

#include "Dungeon.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PlainsDungeon : public Dungeon {

    public:
        PlainsDungeon();
        PlainsDungeon(string name);
        vector<Enemy*> generateEnemyList(int level) override;

    protected:

};

#endif