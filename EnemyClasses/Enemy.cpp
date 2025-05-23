#include <string>
#include <iostream>

#include "Enemy.h"

using namespace std;

Enemy::Enemy() {
    name = "Default Enemy";
    health = 100;
    attackPower = 10;
    xp = 0;
}

Enemy::Enemy(string name, int health, int attackPower, int xp, string description) {
    this->name = name;
    this->health = health;
    this->attackPower = attackPower;
    this->xp = xp;
    this->description = description;
}

string Enemy::getName() {
    return name;
}

int Enemy::getHealth() {
    return health;
}

int Enemy::getAttackPower() {
    return attackPower;
}

int Enemy::getXP() {
    return xp;
}

int Enemy::attackHero() {

    cout << name << " attacks the hero!" << endl;
    cout << "Dealing \033[1;31m" << attackPower << "\033[0m damage!" << endl;

    return attackPower;
}

void Enemy::takeDamage(int damage) {
    health -= damage;
    cout << name << " takes \033[1;31m" << damage << "\033[0m damage!" << endl;
}

void Enemy::displayDetails() {
    /*
    Prints name, health and attackPower to termianl along with the enemy's description.
    */
    cout << "Enemy: " << name << ", Healt: \033[1;32m" << health << "\033[0m, Attack: \033[1;31m" << attackPower << "\033[0m" << endl;
    cout << description << endl;
    cout << "--------------------------------" << endl;
}

Enemy::~Enemy() {}