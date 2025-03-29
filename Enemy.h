#ifndef ENEMY_H
#define ENEMY_H

#include <string>

using namespace std;

class Enemy { 
    public:
        Enemy();
        Enemy(string name, int health, int attackPower, int xp);
        string getName();
        int getHealth();
        int getAttackPower();
        int getXP();
        int attackHero();
        void takeDamage(int damage);
        ~Enemy();

    private:
        string name;
        int health;
        int attackPower;
        int xp;

};

#endif // ENEMY_H