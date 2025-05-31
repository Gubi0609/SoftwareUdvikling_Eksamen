#include "TravellingMerchant.h"

#include <string>
#include <vector>

using namespace std;

TravellingMerchant::TravellingMerchant() {
    name = "Bargle the Traveller";
    stockList = {"Stick", "Dagger", "Travellers Spear", "Soldiers Sword", "Royal Claymore", "Katana", "Master Sword"};
    description = "A travelling merchant. No one knows where he came from. He just… shows up.";
}

vector<string> TravellingMerchant::getStockList() {
    return stockList;
}

string TravellingMerchant::getName() {
    return name;
}

string TravellingMerchant::getDescription() {
    return description;
}

Weapon* TravellingMerchant::createWeapon(string weaponType) {
    /*
    Creates a weapon pointer by the given weaponType
    :param weaponType: The type of weapon to create
    :return: A pointer to the created weapon
    */
    
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
        return new Hands(); // Invalid weapon type
    }
}

TravellingMerchant::~TravellingMerchant() {}