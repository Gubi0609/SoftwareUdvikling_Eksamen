#ifndef CAVEDUNGEON_H
#define CAVEDUNGEON_H

#include "Dungeon.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CaveDungeon : public Dungeon {

    public:
        CaveDungeon();
        vector<Enemy*> generateEnemyList(int level) override;

    protected:

};

#endif