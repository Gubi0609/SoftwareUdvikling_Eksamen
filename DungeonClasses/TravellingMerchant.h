#ifndef TRAVELLINGMERCHANT_H
#define TRAVELLINGMERCHANT_H

#include "Dungeon.h"
#include "../WeaponClasses/Weapon.h"
#include "../WeaponClasses/Weapons.h"

#include <string>
#include <vector>

using namespace std;

class TravellingMerchant : public Dungeon {
    public:
        TravellingMerchant();
        Weapon* createWeapon(string weapontype);
        vector<string> getStockList();

    protected:
        vector<string> stockList;
};

#endif