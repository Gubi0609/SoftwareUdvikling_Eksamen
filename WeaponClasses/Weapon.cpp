#include "Weapon.h"

#include <string>

using namespace std;

Weapon::Weapon() {
    name = "Default Weapon";
    weaponId = 0;
    attackPower = 0;
    strengthModifier = 0;
    durability = 1;
    price = 0;
    description = "";
}

Weapon::Weapon(string name, int weaponId,int attackPower, int strengthModifier, int durability, int price, string description) {
    this->name = name;
    this->weaponId = weaponId;
    this->attackPower = attackPower;
    this->strengthModifier = strengthModifier;
    this->durability = durability;
    this->price = price;
    this->description = description;
}

string Weapon::getName() {
    return name;
}

int Weapon::getWeaponId() {
    return weaponId;
}

int Weapon::getAttackPower() {
    return attackPower;
}

int Weapon::getStrengthModifier() {
    return strengthModifier;
}

int Weapon::getDurability() {
    return durability;
}

int Weapon::getPrice() {
    return price;
}

string Weapon::getDescription() {
    return description;
}

Weapon::~Weapon() {}