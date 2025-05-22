#ifndef WEAPON_H
#define WEAPON_H

#include <string>

using namespace std;

class Weapon {

    public:
        Weapon();
        Weapon(string name, int weaponId,int attackPower, int strengthModifier, int durability, int price, string description = "");
        string getName();
        int getWeaponId();
        int getAttackPower();
        int getStrengthModifier();
        int getDurability();
        int getPrice();
        string getDescription();
        ~Weapon();

    protected:
        string name;
        int weaponId;
        int attackPower;
        int strengthModifier;
        int durability;
        string description;
        int price;

};

#endif