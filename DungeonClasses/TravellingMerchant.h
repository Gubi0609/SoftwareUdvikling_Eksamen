#ifndef TRAVELLINGMERCHANT_H
#define TRAVELLINGMERCHANT_H

#include "../WeaponClasses/Weapon.h"
#include "../WeaponClasses/Weapons.h"

#include <string>
#include <vector>

using namespace std;

class TravellingMerchant {
    public:
        TravellingMerchant();
        Weapon* createWeapon(string weapontype);
        string getName();
        vector<string> getStockList();
        ~TravellingMerchant();

    protected:
        string name;
        vector<string> stockList;
};

#endif