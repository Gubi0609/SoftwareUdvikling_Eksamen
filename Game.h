#ifndef GAME_H
#define GAME_H

#include "Hero.h"
#include "Enemies.h"
#include "Enemy.h"
#include "Dungeon.h"
#include "CaveDungeon.h"
#include "ForestDungeon.h"
#include "PlainsDungeon.h"

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

        void loadHero(string name);
        void loadLevel(int level);
        void loadCurrentDungeon();
        
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
