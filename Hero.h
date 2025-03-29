#ifndef HERO_H
#define HERO_H

#include <string>

using namespace std;

class Hero {
    public:
        Hero();
        Hero(string name);
        string getName();
        int getHealth();
        int getAttackPower();
        int getXP();
        int getLevel();
        int attackEnemy();
        void gainXP(int xp);
        void levelUp();
        void takeDamage(int damage);
        ~Hero();

    private:
        string name;
        int level;
        int health;
        int attackPower;
        int xp;

};


#endif // HERO_H