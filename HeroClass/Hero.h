#ifndef HERO_H
#define HERO_H

#include <string>

#include "../WeaponClasses/Weapon.h"
#include "../WeaponClasses/Weapons.h"

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
        int getGold();
        Weapon* getWeapon();
        
        void setHealth(int health);
        void setAttackPower(int attackPower);
        void setXP(int xp);
        void setLevel(int level);
        void setWeapon(Weapon* newWeapon);
        
        int attackEnemy();
        void gainXP(int xp);
        void levelUp();
        void takeDamage(int damage);
        void earnGold(int gold);
        void spendGold(int gold);

        void displayDetails();

        ~Hero();

    private:
        string name;
        int level;
        int maxHealth;
        int health;
        int attackPower;
        int xp;
        int gold;
        Weapon* currentWeapon;
        int weaponDurabilityLeft;

};


#endif // HERO_H