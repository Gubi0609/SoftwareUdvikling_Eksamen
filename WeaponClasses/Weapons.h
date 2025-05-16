#include "Weapon.h"

#include <string>

using namespace std;

class Hands : public Weapon {
    Hands() : Weapon("Hands", 0, 1, 1000, 0, "Your own fists — unarmed, unrefined, but still capable of survival. A last resort when all else is lost.") {}
};

class Stick : public Weapon {
    Stick() : Weapon("Stick", 1, 1, 5, 200, "Sold as a 'training staff' by shifty roadside merchants. It's a stick. It will break. Probably soon.") {}
};

class Dagger : public Weapon {
    Dagger() : Weapon("Dagger", 3, 1, 10, 500, "A short blade favored by thieves and tomb-raiders. Quick to draw, quicker to silence.") {}
};

class TravellersSpear : public Weapon {
    TravellersSpear() : Weapon("Travellers Spear", 7, 2, 10, 1000, "A simple but sturdy polearm, often carried by those who wander dangerous roads.") {}
};

class SoldiersSword : public Weapon {
    SoldiersSword() : Weapon("Soldiers Sword", 10, 3, 15, 2000, "A well-balanced blade once standard issue among organized armies. Reliable, lethal, and forged for war.") {}
};

class RoyalClaymore : public Weapon {
    RoyalClaymore() : Weapon("Royal Claymore", 15, 1, 10, 2500, "A massive sword of regal make, etched with forgotten heraldry. Once wielded by kings, now waiting for a worthy hand.") {}
};

class Katana : public Weapon {
    Katana() : Weapon("Katana", 13, 5, 20, 3000, "A rare curved blade from distant lands. Its edge is impossibly sharp, its strikes as fluid as wind over steel.") {}
};

class MasterSword : public Weapon {
    MasterSword() : Weapon("Master Sword", 15, 5, 30, 5000, "An ancient blade of legend, said to choose its wielder. Bound by oath and power, it shines with an otherworldly glow, forged to vanquish evil.") {}
};
