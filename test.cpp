#include "Enemies.h"
#include "Enemy.h"


using namespace std;

int main() {

    cout << "Initializing enemies..." << endl;
    Wolf wolf;
    SmallTroll smallTroll;

    cout << "Enemies initialized!" << endl;

    cout << "Wolf: " << wolf.getName() << ", Health: " << wolf.getHealth() << ", Attack Power: " << wolf.getAttackPower() << ", XP: " << wolf.getXP() << endl;
    cout << "Small Troll: " << smallTroll.getName() << ", Health: " << smallTroll.getHealth() << ", Attack Power: " << smallTroll.getAttackPower() << ", XP: " << smallTroll.getXP() << endl;

    wolf.attackHero();
    smallTroll.attackHero();

    return 0;

}