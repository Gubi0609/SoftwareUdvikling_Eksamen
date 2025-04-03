#ifndef GAME_H
#define GAME_H

#include "Hero.h"
#include "Enemies.h"
#include "Enemy.h"

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
        bool gameOver;
        vector <string> enemyList;

        void loadHero(string name);
        void loadLevel(int level);
        void battle(Hero& hero, Enemy& enemy);
        void getEnemyList(int level);
        void displayEnemyList();
        void modifyEnemyList(int position);
        Enemy* createEnemy(string enemyType);
        //void endGame(Hero& hero);

};

#endif // GAME_H
