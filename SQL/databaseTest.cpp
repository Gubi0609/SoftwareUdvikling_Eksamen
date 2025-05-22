#include "Database.h"

int main() {
    Database db;

    db.saveHero(1, 10, 9000, 90, 30, 30000, 100, 8);
    db.showHeroSaves();

    return 0;

}