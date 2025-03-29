#ifndef ENEMIES_H
#define ENEMIES_H

#include "Enemy.h"
#include <iostream>
#include <string>

using namespace std;

/*
[x] Wolf 2 hp, 1 attackPower, 50 xp
[x] Small troll 4 hp, 1 attackPower, 75 xp
[x] Troll 6 hp, 2 attackPower, 150 xp
[x] Weak Goblin 2 hp, 1 attackPower, 75 xp
[x] Goblin 4 hp, 1 attackPower, 150 xp
[x] Goblin guard 8 hp, 3 attackPower, 300 xp
[x] Goblin king 15 hp, 5 attackPower, 500 xp
[x] Gollum 20 hp, 5 attackPower, 1000 xp
[x] Spider 10 hp, 2 attackPower, 300 xp
[x] Giant spider 12 hp, 4 attackPower, 400 xp
[x] Dragon 100 hp, 10 attackPower, 3000 xp
*/


class Wolf : public Enemy {
public:
    Wolf() : Enemy("Wolf", 2, 1, 50) {}
    ~Wolf();
};

class SmallTroll : public Enemy {
public:
    SmallTroll() : Enemy("Small Troll", 4, 1, 75) {}
    ~SmallTroll();
};

class Troll : public Enemy {
public:
    Troll() : Enemy("Troll", 6, 2, 150) {}
    ~Troll();
};

class WeakGoblin : public Enemy {
public:
    WeakGoblin() : Enemy("Weak Goblin", 2, 1, 75) {}
    ~WeakGoblin();
};

class Goblin : public Enemy {
public:
    Goblin() : Enemy("Goblin", 4, 1, 150) {}
    ~Goblin();
};

class GoblinGuard : public Enemy {
public:
    GoblinGuard() : Enemy("Goblin Guard", 8, 3, 300) {}
    ~GoblinGuard();
};

class GoblinKing : public Enemy {
public:
    GoblinKing() : Enemy("Goblin King", 15, 5, 500) {}
    ~GoblinKing();
};

class Gollum : public Enemy {
public:
    Gollum() : Enemy("Gollum", 20, 5, 1000) {}
    ~Gollum();
};

class Spider : public Enemy {
public:
    Spider() : Enemy("Spider", 10, 2, 300) {}
    ~Spider();
};

class GiantSpider : public Enemy {
public:
    GiantSpider() : Enemy("Giant Spider", 12, 4, 400) {}
    ~GiantSpider();
};

class Dragon : public Enemy {
public:
    Dragon() : Enemy("Dragon", 100, 10, 3000) {}
    ~Dragon();
};

#endif // ENEMIES_H