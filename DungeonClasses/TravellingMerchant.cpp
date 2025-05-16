#include "TravellingMerchant.h"

#include <string>
#include <vector>

using namespace std;

TravellingMerchant::TravellingMerchant() : Dungeon("Bargle the Traveller", "A travelling merchant. No one knows where he came from. He just… shows up.") {
    stockList = {"Stick", "Dagger", "Travellers Spear", "Soldiers Sword", "Royal Claymore", "Katana", "Master Sword"};
}

vector<string> TravellingMerchant::getStockList() {
    return stockList;
}

Weapon* TravellingMerchant::createWeapon(string weaponType) {
    
    if (weaponType == "Stick") {
        return new Stick();
    } else if (weaponType == "Dagger") {
        return new Dagger();
    } else if (weaponType == "Travellers Spear") {
        return new TravellersSpear();
    } else if (weaponType == "Soldiers Sword") {
        return new SoldiersSword();
    } else if (weaponType == "Royal Claymore") {
        return new RoyalClaymore();
    } else if (weaponType == "Katana") {
        return new Katana();
    } else if (weaponType == "Master Sword") {
        return new MasterSword();
    } else {
        return nullptr; // Invalid weapon type
    }
}