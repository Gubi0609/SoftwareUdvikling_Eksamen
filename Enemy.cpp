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

Enemy::Enemy(string name, int health, int attackPower, int xp) {
    this->name = name;
    this->health = health;
    this->attackPower = attackPower;
    this->xp = xp;
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
    cout << "Dealing " << attackPower << " damage!" << endl;

    return attackPower;
}

void Enemy::takeDamage(int damage) {
    health -= damage;
    cout << name << " takes " << damage << " damage!" << endl;
    // cout << name << "'s remaining health: " << health << endl;
}

Enemy::~Enemy() {
    cout << name << " has been defeated! (Enemy Class)" << endl;
}