#include <string>

using namespace std;

class Enemy { 
    public:
        Enemy();
        Enemy(string name, int health, int attackPower, int xp);
        string getName();
        int getHealth();
        int getAttackPower();
        int getXP();
        ~Enemy();

    private:
        string name;
        int health;
        int attackPower;
        int xp;

        int attackHero();

};