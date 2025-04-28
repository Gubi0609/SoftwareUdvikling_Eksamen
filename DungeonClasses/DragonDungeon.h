#ifndef DRAGONDUNGEON_H
#define DRAGONDUNGEON_H

#include "Dungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class DragonDungeon : public Dungeon {

    public:
        DragonDungeon();
        vector<unique_ptr<Enemy>> generateEnemyList(int level) override;

    protected:

};

#endif