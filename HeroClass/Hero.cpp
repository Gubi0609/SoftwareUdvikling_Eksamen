#include "Hero.h"
#include <iostream>
#include <string>

using namespace std;

Hero::Hero() {
    name = "Default Hero";
    this->heroId = 0;
    level = 1;
    health = 10;
    attackPower = 2;
    xp = 0;
    gold = 0;
    currentWeapon = new Hands();
    weaponDurabilityLeft = currentWeapon->getDurability();
}

Hero::Hero(string name, int heroId) {
    this->name = name;
    this->heroId = heroId;
    level = 1;
    maxHealth = 10;
    health = maxHealth;
    attackPower = 2;
    xp = 0;
    gold = 0;
    currentWeapon = new Hands();
    weaponDurabilityLeft = currentWeapon->getDurability();
}

int Hero::getHeroId() {
    return heroId;
}

string Hero::getName() {
    return name;
}

int Hero::getHealth() {
    return health;
}

int Hero::getMaxHealth() {
    return maxHealth;
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

int Hero::getDurrabilityLeft() {
    return weaponDurabilityLeft;
}

Weapon* Hero::getWeapon() {
    return currentWeapon;
}

void Hero::setHeroId(int heroId) {
    this->heroId = heroId;
}

void Hero::setName(string name) {
    this->name = name;
}

void Hero::setLevel(int level) {
    this->level = level;
}

void Hero::setMaxHealth(int maxHealth) {
    this->maxHealth = maxHealth;
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

void Hero::setGold(int gold) {
    this->gold = gold;
}

void Hero::setWeapon(Weapon* newWeapon) {
    currentWeapon = newWeapon;
    
    attackPower = currentWeapon->getAttackPower() + (level*currentWeapon->getStrengthModifier());
}

void Hero::obtainWeapon(Weapon* newWeapon) {
    currentWeapon = newWeapon;
    weaponDurabilityLeft = currentWeapon->getDurability();

    attackPower = currentWeapon->getAttackPower() + (level*currentWeapon->getStrengthModifier());
}

void Hero::setDurabilityLeft(int durabilityLeft) {
    weaponDurabilityLeft = durabilityLeft;
}

int Hero::attackEnemy() {
    cout << name << " attacks the enemy!" << endl;
    cout << "Dealing \033[1;31m" << attackPower << "\033[0m damage!" << endl;

    weaponDurabilityLeft -= 1;

    if (weaponDurabilityLeft <= 0) {
        cout << "\033[7;31mYour " << currentWeapon->getName() << " broke!\033[0m" << endl;
        currentWeapon = new Hands();
        weaponDurabilityLeft = currentWeapon->getDurability(); 
    }

    return attackPower;
}

void Hero::gainXP(int xp) {
    this->xp += xp;
    cout << name << " gains \033[1;36m" << xp << " XP\033[0m!" << endl;

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

    cout << name << " levels up to level \033[1;34m" << level << "\033[0m!" << endl;
    cout << "Health: \033[1;32m" << health << "\033[0m, \033[1;31mAttack Power: " << attackPower << "\033[0m" << endl;
}

void Hero::takeDamage(int damage) {
    health -= damage;
    cout << name << " takes "<< "\033[1;31m" << damage << "\033[0m damage!" << endl;
}

void Hero::earnGold(int gold) {
    this->gold += gold;
}

void Hero::spendGold(int gold) {
    this->gold -= gold;
}

void Hero::displayDetails() {
    cout << "Hero: " << name << ", Level: \033[1;34m" << level << "\033[0m, XP: \033[1;36m" << xp << "\033[0m" << endl;
    cout << "Health: \033[1;32m" << health << "\033[0m, Attack Power: \033[1;31m" << attackPower << "\033[0m" << endl;
    cout << "Gold: \033[1;33m" << gold << " g\033[0m" <<  endl;
    cout << "Wielding: " << currentWeapon->getName() << endl;
    cout << "--------------------------------" << endl;
}

Hero::~Hero() {}