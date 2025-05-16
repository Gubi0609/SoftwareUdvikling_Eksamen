#include "Hero.h"
#include <iostream>
#include <string>

using namespace std;

Hero::Hero() {
    name = "Default Hero";
    level = 1;
    health = 10;
    attackPower = 2;
    xp = 0;
    gold = 0;
    currentWeapon = new Hands();
    weaponDurabilityLeft = currentWeapon->getDurability();
}

Hero::Hero(string name) {
    this->name = name;
    level = 1;
    maxHealth = 10;
    health = maxHealth;
    attackPower = 2;
    xp = 0;
    gold = 0;
    currentWeapon = new Hands();
    weaponDurabilityLeft = currentWeapon->getDurability();
}

string Hero::getName() {
    return name;
}

int Hero::getHealth() {
    return health;
}

int Hero::getAttackPower() {
    return attackPower;
}

int Hero::getXP() {
    return xp;
}

int Hero::getLevel() {
    return level;
}

int Hero::getGold() {
    return gold;
}

Weapon* Hero::getWeapon() {
    return currentWeapon;
}

void Hero::setHealth(int health) {
    this->health = health;
}

void Hero::setAttackPower(int attackPower) {
    this->attackPower = attackPower;
}

void Hero::setXP(int xp) {
    this->xp = xp;
}

void Hero::setLevel(int level) {
    this->level = level;
}

void Hero::setWeapon(Weapon* newWeapon) {
    currentWeapon = newWeapon;
    weaponDurabilityLeft = currentWeapon->getDurability();

    attackPower = currentWeapon->getAttackPower() + (level*currentWeapon->getStrengthModifier());

    cout << name << "obtains: " << currentWeapon->getName() << endl;
}

int Hero::attackEnemy() {
    cout << name << " attacks the enemy!" << endl;
    cout << "Dealing " << attackPower << " damage!" << endl;

    weaponDurabilityLeft -= 1;

    return attackPower;
}

void Hero::gainXP(int xp) {
    this->xp += xp;
    cout << name << " gains " << xp << " XP!" << endl;

    if (this->xp >= this->level * 1000) {
        levelUp();
    }
}

void Hero::levelUp() {
    level++;
    maxHealth += 9;
    health = maxHealth;
    attackPower = currentWeapon->getAttackPower() + (level*currentWeapon->getStrengthModifier());
    xp = 0; // Remember to reset xp after leveling up

    cout << name << " levels up to level " << level << "!" << endl;
    cout << "Health: " << health << ", Attack Power: " << attackPower << endl;
}

void Hero::takeDamage(int damage) {
    health -= damage;
    cout << name << " takes " << damage << " damage!" << endl;
}

void Hero::earnGold(int gold) {
    this->gold += gold;
}

void Hero::spendGold(int gold) {
    this->gold -= gold;
}

void Hero::displayDetails() {
    cout << "Hero: " << name << ", Level: " << level << ", XP: " << xp << endl;
    cout << "Health: " << health << ", Attack Power: " << attackPower << endl;
    cout << "Gold: " << gold << endl;
    cout << "Wielding: " << currentWeapon->getName() << endl;
    cout << "--------------------------------" << endl;
}

Hero::~Hero() {}