#ifndef GAME_H
#define GAME_H

#include "../HeroClass/Hero.h"
#include "../EnemyClasses/Enemies.h"
#include "../EnemyClasses/Enemy.h"
#include "../DungeonClasses/Dungeon.h"
#include "../DungeonClasses/CaveDungeon.h"
#include "../DungeonClasses/ForestDungeon.h"
#include "../DungeonClasses/PlainsDungeon.h"
#include "../DungeonClasses/DragonDungeon.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Game {
    public:
        Game();
        void topMenu();
        void startGame();

    private:
        Hero hero;
        unique_ptr<Enemy> currentEnemy;
        int currentLevel;
        int currentDungeonGold;
        int currentDungeonIndex;
        bool gameOver;
        vector <unique_ptr<Enemy>> enemyList;
        vector <unique_ptr<Dungeon>> dungeonList;
        unique_ptr<Dungeon> currentDungeon;

        void loadHero(string name);
        void loadLevel(int level);
        void loadCurrentDungeon();

        bool dungeonOptions();
        bool enemyOptions();
        
        void battle(Hero& hero, Enemy& enemy);
        
        void getDungeonList(int level);
        void displayDungeonList();
        void modifyDungeonList(int position);

        void getEnemyList(int level);
        void displayEnemyList();
        void modifyEnemyList(int position);
        //Enemy* createEnemy(string enemyType);
        
        //void endGame(Hero& hero);

};

#endif // GAME_H
