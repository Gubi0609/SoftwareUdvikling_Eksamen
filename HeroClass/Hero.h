#ifndef HERO_H
#define HERO_H

#include <string>

#include "../WeaponClasses/Weapon.h"
#include "../WeaponClasses/Weapons.h"

using namespace std;

class Hero {
    public:
        Hero();
        Hero(string name, int heroId);
        int getHeroId();
        string getName();
        int getHealth();
        int getMaxHealth();
        int getAttackPower();
        int getXP();
        int getLevel();
        int getGold();
        int getDurrabilityLeft();
        Weapon* getWeapon();
        
        void setHeroId(int heroId);
        void setName(string name);
        void setLevel(int level);
        void setMaxHealth(int maxHealth);
        void setHealth(int health);
        void setAttackPower(int attackPower);
        void setXP(int xp);
        void setGold(int gold);
        void obtainWeapon(Weapon* newWeapon);
        void setWeapon(Weapon* newWeapon);
        void setDurabilityLeft(int durabilityLeft);
        
        int attackEnemy();
        void gainXP(int xp);
        void levelUp();
        void takeDamage(int damage);
        void earnGold(int gold);
        void spendGold(int gold);

        void displayDetails();

        ~Hero();

    private:
        int heroId;
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