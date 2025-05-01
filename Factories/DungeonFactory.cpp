#include "DungeonFactory.h"

#include <string>
#include <vector>
#include <algorithm>
#include <random>

DungeonFactory::DungeonFactory() {}

vector<Dungeon*> DungeonFactory::generateDungeonList(int level) {
    // Generates a list of dungeons based on the current level.

    dungeonList.clear(); // Clears the list of dungeons.

    vector<string> possibleDungeons = {"Forest", "Cave", "Plains"}; // List of possible dungeons.

    random_device rd; // Seed for random number generator
    mt19937 g(rd());  // Mersenne Twister random number generator
    uniform_int_distribution<> dist(0, possibleDungeons.size() - 1);

    if (level == 11) {
        
        dungeonList = {createDungeon("Dragon")};

    } else if (!(level == 4 || level == 6)) {

        for (int i = 0; i < 4; ++i) {
            int randomIndex = dist(g);
            dungeonList.push_back(createDungeon(possibleDungeons[randomIndex]));
        }

    } else {
        
        dungeonList = {createDungeon("Forest"), createDungeon("Cave"), createDungeon("Plains")};
    
    }

    return dungeonList;
}

vector<Dungeon*> DungeonFactory::getDungeonList() {
    return dungeonList;
}

void DungeonFactory::modifyDungeonList(int position) {
    // Modifies the list of dungeons.
    dungeonList.erase(dungeonList.begin() + position);
}

Dungeon* DungeonFactory::createDungeon(string dungeonType) {
    // Creates a dungeon based on the given type.

    if (dungeonType == "Cave") {
        return new CaveDungeon();
    } else if (dungeonType == "Forest") {
        return new ForestDungeon();
    } else if (dungeonType == "Plains") {
        return new PlainsDungeon();
    } else if (dungeonType == "Dragon") {
        return new DragonDungeon();
    } else {
        cout << "Invalid dungeon type!" << endl;
        return nullptr;
    }
}