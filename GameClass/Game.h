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
#include "../Factories/DungeonFactory.h"
#include "../Factories/EnemyFactory.h"

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
        Enemy* currentEnemy;
        int currentLevel;
        int currentDungeonGold;
        int currentDungeonIndex;
        bool gameOver;
        vector <Enemy*> enemyList;
        vector <Dungeon*> dungeonList;
        Dungeon* currentDungeon;
        DungeonFactory dungeonFactory;

        void loadHero(string name);
        void loadLevel(int level);
        void loadCurrentDungeon();

        bool dungeonOptions();
        bool enemyOptions();
        
        void battle(Hero& hero, Enemy& enemy);
        
        void generateDungeonList(int level);
        void displayDungeonList();
        void modifyDungeonList(int position);

        void generateEnemyList(int level);
        void displayEnemyList();
        void modifyEnemyList(int position);
        
        //void endGame(Hero& hero);

};

#endif // GAME_H
