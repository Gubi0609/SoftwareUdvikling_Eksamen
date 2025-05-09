#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <string>
#include <vector>

#include "../EnemyClasses/Enemy.h"
#include "../EnemyClasses/Enemies.h"

using namespace std;

class EnemyFactory {

    public:
        EnemyFactory();
        vector<Enemy*> generateEnemyList(int level, string dungeonType);
        vector<Enemy*> getEnemyList() const;
        void modifyEnemyList(int position);
        Enemy* createEnemy(string enemyType);
        
    protected:
        vector<Enemy*> enemyList;

};


#endif