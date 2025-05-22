#include <sqlite3.h>
#include <string>

#include "../HeroClass/Hero.h"

using namespace std;

class Database {

    public:
        Database();
        bool openDatabase();
        int getNewSaveNumForHero(int heroId);
        int getLatestHeroId();
        void saveHero(int heroId, int level, int xp, int hp, int attackPower, int gold, int durrabilityLeft, int weaponId);
        Hero createHero(string name);
        Hero loadHero(int heroId);
        void showHeroSaves();
        void showHeroesAlphabetically();
        void showHeroKils();
        void showHeroWeaponsKills(int heroId);
        void showWeaponHighscore();
        void closeDataBase();
        ~Database();

    protected:
        sqlite3* database;
        string databasePath;
        bool isOpen;

};