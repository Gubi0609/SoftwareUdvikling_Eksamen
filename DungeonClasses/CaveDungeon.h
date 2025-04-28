#ifndef CAVEDUNGEON_H
#define CAVEDUNGEON_H

#include "Dungeon.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class CaveDungeon : public Dungeon {

    public:
        CaveDungeon();
        vector<unique_ptr<Enemy>> generateEnemyList(int level) override;

    protected:

};

#endif