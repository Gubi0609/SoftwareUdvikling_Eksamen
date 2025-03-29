#include "Enemies.h"
#include "Enemy.h"
#include "Hero.h"

#include <iostream>

using namespace std;

int main() {

    cout << "Initializing enemies..." << endl;
    Wolf wolf;
    SmallTroll smallTroll;
    cout << "Enemies initialized!" << endl;
    
    cout << "Initializing hero..." << endl;
    Hero hero("Heroic Hero");
    cout << "Hero initialized!" << endl;

    cout << "Wolf: " << wolf.getName() << ", Health: " << wolf.getHealth() << ", Attack Power: " << wolf.getAttackPower() << ", XP: " << wolf.getXP() << endl;
    cout << "Small Troll: " << smallTroll.getName() << ", Health: " << smallTroll.getHealth() << ", Attack Power: " << smallTroll.getAttackPower() << ", XP: " << smallTroll.getXP() << endl;

    cout << "Hero: " << hero.getName() << ", Health: " << hero.getHealth() << ", Attack Power: " << hero.getAttackPower() << ", XP: " << hero.getXP() << endl;

    hero.attackEnemy();
    wolf.takeDamage(hero.getAttackPower());

    wolf.attackHero();
    smallTroll.attackHero();

    hero.takeDamage(smallTroll.getAttackPower()+wolf.getAttackPower());

    return 0;

}