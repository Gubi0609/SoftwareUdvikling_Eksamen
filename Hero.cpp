#include "Hero.h"
#include <iostream>
#include <string>

using namespace std;

Hero::Hero() {
    name = "Default Hero";
    level = 1;
    health = 100;
    attackPower = 10;
    xp = 0;
}

Hero::Hero(string name) {
    this->name = name;
    level = 1;
    health = 10;
    attackPower = 2;
    xp = 0;
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

int Hero::attackEnemy() {
    cout << name << " attacks the enemy!" << endl;
    cout << "Dealing " << attackPower << " damage!" << endl;

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
    health += 2;
    attackPower += 1;
    xp = 0; // Remember to reset xp after leveling up

    cout << name << " levels up to level " << level << "!" << endl;
    cout << "Health: " << health << ", Attack Power: " << attackPower << endl;
}

void Hero::takeDamage(int damage) {
    health -= damage;
    cout << name << " takes " << damage << " damage!" << endl;
}

Hero::~Hero() {}