#ifndef DUNGEONFACTORY_H
#define DUNGEONFACTORY_H

#include <vector>
#include <string>

#include "../DungeonClasses/Dungeon.h"
#include "../DungeonClasses/ForestDungeon.h"
#include "../DungeonClasses/CaveDungeon.h"
#include "../DungeonClasses/PlainsDungeon.h"
#include "../DungeonClasses/DragonDungeon.h"
#include "../DungeonClasses/TravellingMerchant.h"

using namespace std;

class DungeonFactory {

    public:
        DungeonFactory();
        vector<Dungeon*> generateDungeonList(int level);
        vector<Dungeon*> getDungeonList() const;
        void modifyDungeonList(int position);
        Dungeon* createDungeon(string dungeonType);

    protected:
        vector <Dungeon*> dungeonList;
};

#endif