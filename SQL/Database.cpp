#include <sqlite3.h>
#include <string>
#include <iostream>

#include "Database.h"
#include "../HeroClass/Hero.h"
#include "../DungeonClasses/TravellingMerchant.h"

using namespace std;

Database::Database() {
    databasePath = "./database.db";
    openDatabase();
}

bool Database::openDatabase() {
    int returnCode = sqlite3_open(databasePath.c_str(), &database);
        if (returnCode) {
            cerr << "Can't open database: " << sqlite3_errmsg(database) << endl;
            return isOpen = false;
        }
        return isOpen = true;
}

void Database::closeDataBase() {
        if (database) {
            sqlite3_close(database);
            database = nullptr;
            isOpen = false;
        }
    }

int Database::getNewSaveNumForHero(int heroId) {

    const char* sqlCommand = R"(
    SELECT COALESCE(MAX(saveNumber), 0) + 1 AS nextSaveNumber
    FROM Save
    WHERE heroId = ?;
    )";

     int newSaveNum = 0;

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(database) << std::endl;
        return 0;
    }

    sqlite3_bind_int(statement, 1, heroId);

    returnCode = sqlite3_step(statement);
    if (returnCode == SQLITE_ROW) {
        newSaveNum = sqlite3_column_int(statement, 0);
    } else {
        std::cerr << "Query failed: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(statement);
    return newSaveNum;

}

int Database::getLatestHeroId() {
    const char* sqlCommand = R"(
        SELECT MAX(heroId) FROM Hero;
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Query failed: " << sqlite3_errmsg(database) << endl;
        return 0;
    }

    int heroId = 0;

    while (sqlite3_step(statement) == SQLITE_ROW) {
        heroId = sqlite3_column_int(statement, 0);
    }

    sqlite3_finalize(statement);

    return heroId;
}

int Database::getSmallestHeroId() {
    const char* sqlCommand = R"(
        SELECT MIN(heroId) FROM Hero;
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Query failed: " << sqlite3_errmsg(database) << endl;
        return 0;
    }

    int heroId = 0;

    while (sqlite3_step(statement) == SQLITE_ROW) {
        heroId = sqlite3_column_int(statement, 0);
    }

    sqlite3_finalize(statement);

    return heroId;
}

void Database::saveHero(int heroId, int level, int xp, int hp, int maxHp,int attackPower, int gold, int durrabilityLeft, int weaponId) {

    int newSaveNum = getNewSaveNumForHero(heroId);

    const char* sqlCommand = R"(
        INSERT INTO Save (
            heroId, saveNumber, level, xp, hp, maxHp, attackPower, gold, durabilityLeft, weaponId
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Failed to prepare insert: " << sqlite3_errmsg(database) << endl;
        return;
    }

    // Bind values to ?
    sqlite3_bind_int(statement, 1, heroId);
    sqlite3_bind_int(statement, 2, newSaveNum);
    sqlite3_bind_int(statement, 3, level);
    sqlite3_bind_int(statement, 4, xp);
    sqlite3_bind_int(statement, 5, hp);
    sqlite3_bind_int(statement, 6, maxHp);
    sqlite3_bind_int(statement, 7, attackPower);
    sqlite3_bind_int(statement, 8, gold);
    sqlite3_bind_int(statement, 9, durrabilityLeft);
    sqlite3_bind_int(statement, 10, weaponId);

    // Execute
    returnCode = sqlite3_step(statement);
    if (returnCode != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(database) << endl;
    } else {
        std::cout << "Hero saved successfully with saveNumber = " << newSaveNum << endl;
    }

    // Clean up
    sqlite3_finalize(statement);
}

Hero Database::createHero(string name) {

    const char* sqlCommand = R"(
    INSERT INTO Hero(name) VALUES (?);
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Failed to prepare insert: " << sqlite3_errmsg(database) << endl;
        return Hero();
    }

    // Bind values to ?
    sqlite3_bind_text(statement, 1, name.c_str(), -1, SQLITE_TRANSIENT);

    returnCode = sqlite3_step(statement);
    if (returnCode != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(database) << endl;
    } else {
        std::cout << "Hero created succesfully" << endl;
        return Hero(name, getLatestHeroId());
    }

    sqlite3_finalize(statement);

    return Hero();
}

Hero Database::loadHero(int heroId) {

    const char* sqlCommand = R"(
        SELECT Hero.heroId, Hero.name, Save.level, Save.xp, Save.hp, Save.maxHp, Save.attackPower, Save.gold, Save.durabilityLeft, Weapon.name
        FROM Save, Hero, Weapon
        WHERE Save.heroId = Hero.heroId
        AND Save.weaponId = Weapon.weaponId
        AND Save.heroId = ?
        AND Save.saveId = (SELECT MAX(saveId) FROM Save WHERE Save.heroId = ?);
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Failed to prepare insert: " << sqlite3_errmsg(database) << endl;
        return Hero();
    }

    // Bind values to ?
    sqlite3_bind_int(statement, 1, heroId);
    sqlite3_bind_int(statement, 2, heroId);

    Hero hero;

    returnCode = sqlite3_step(statement);
    if (returnCode == SQLITE_ROW) {
        int id = sqlite3_column_int(statement, 0);
        std::string heroName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        int level = sqlite3_column_int(statement, 2);
        int xp = sqlite3_column_int(statement, 3);
        int hp = sqlite3_column_int(statement, 4);
        int maxHp = sqlite3_column_int(statement, 5);
        int attackPower = sqlite3_column_int(statement, 6);
        int gold = sqlite3_column_int(statement, 7);
        int durabilityLeft = sqlite3_column_int(statement, 8);
        std::string weaponName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 9));

        hero = Hero(heroName, id);
        TravellingMerchant merchant;
        hero.setLevel(level);
        hero.setXP(xp);
        hero.setHealth(hp);
        hero.setMaxHealth(maxHp);
        hero.setAttackPower(attackPower);
        hero.setGold(gold);
        hero.setDurabilityLeft(durabilityLeft);
        hero.setWeapon(merchant.createWeapon(weaponName));
    } else {
        std::cerr << "No hero save found: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(statement);
    return hero;
}

void Database::registrerKill(int heroId, int weaponId) {
    const char* sqlCommand = R"(
    INSERT INTO MonsterKill(heroId, weaponId) VALUES (?, ?);
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Failed to prepare insert: " << sqlite3_errmsg(database) << endl;
        return;
    }

    // Bind values to ?
    sqlite3_bind_int(statement, 1, heroId);
    sqlite3_bind_int(statement, 2, weaponId);

    // Execute
    returnCode = sqlite3_step(statement);
    if (returnCode != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(database) << endl;
    } else {
        std::cout << "Kill registrered succesfully." << endl;
    }

    // Clean up
    sqlite3_finalize(statement);

}

void Database::showHeroSaves() {

    const char* sqlCommand = R"(
        SELECT 
            Hero.heroId, 
            Hero.name, 
            Save.level, 
            Save.xp, 
            Save.hp, 
            Save.attackPower, 
            Save.gold, 
            Weapon.name, 
            Save.savedAt
        FROM 
            Save, 
            Hero, 
            Weapon
        WHERE Save.heroId = Hero.heroId 
            AND Save.weaponId = Weapon.weaponId
            AND Save.savedAt = (
                SELECT MAX(S2.savedAt)
                FROM Save S2
                WHERE S2.heroId = Save.heroId
        );
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Query failed: " << sqlite3_errmsg(database) << endl;
        return;
    }

    cout << "Save File| Hero Name|  level|  xp |    hp| attackPower|    gold|   Weapon| Saved At" << endl;

    while (sqlite3_step(statement) == SQLITE_ROW) {
        int heroId = sqlite3_column_int(statement, 0);
        string heroName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        int level = sqlite3_column_int(statement, 2);
        int xp = sqlite3_column_int(statement, 3);
        int hp = sqlite3_column_int(statement, 4);
        int attackPower = sqlite3_column_int(statement, 5);
        int gold = sqlite3_column_int(statement, 6);
        string weaponName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 7));
        string savedAt = reinterpret_cast<const char*>(sqlite3_column_text(statement, 8));

        cout << heroId << "|    " << heroName << "| " << level << "|    " << xp << "|    " << hp << "|    " << attackPower << "|    " << gold << "|    " << weaponName << "|    " << savedAt << endl;
    }

    sqlite3_finalize(statement);

}

void Database::showHeroesNumerically() {

    const char* sqlCommand = R"(
        SELECT heroId, name
        FROM Hero
        ORDER BY heroId ASC;
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Query failed: " << sqlite3_errmsg(database) << endl;
        return;
    }

    cout << "Hero ID|   Name" << endl;

    while (sqlite3_step(statement) == SQLITE_ROW) {
        int heroId = sqlite3_column_int(statement, 0);
        string heroName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));

        cout << heroId << "     " <<heroName << endl;
    }

    sqlite3_finalize(statement);

}

void Database::showHeroesAlphabetically() {
    const char* sqlCommand = R"(
        SELECT name
        FROM Hero
        ORDER BY name ASC;
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Query failed: " << sqlite3_errmsg(database) << endl;
        return;
    }

    cout << "Name" << endl;

    while (sqlite3_step(statement) == SQLITE_ROW) {
        string heroName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

        cout << heroName << endl;
    }

    sqlite3_finalize(statement);

}

void Database::showHeroKils() {
    const char* sqlCommand = R"(
        SELECT Hero.name, COUNT(MonsterKill.heroId)
        FROM Hero, MonsterKill
        WHERE MonsterKill.heroId = Hero.heroId
        GROUP BY Hero.heroId;
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Query failed: " << sqlite3_errmsg(database) << endl;
        return;
    }

    cout << "Name|  Number Of Kills" << endl;

    while (sqlite3_step(statement) == SQLITE_ROW) {
        string heroName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
        int kills = sqlite3_column_int(statement, 1);

        cout << heroName << "|  " << kills << endl;
    }

    sqlite3_finalize(statement);

}

void Database::showHeroWeaponsKills(int heroId) {
    
    const char* sqlCommand = R"(
        SELECT Weapon.name, COUNT(MonsterKill.weaponId)
        FROM Hero, MonsterKill, Weapon
        WHERE MonsterKill.weaponId = Weapon.weaponId 
        AND MonsterKill.heroId = Hero.heroId 
        AND Hero.heroId = ?
        GROUP BY Weapon.weaponId;
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Failed to prepare insert: " << sqlite3_errmsg(database) << endl;
        return;
    }

    sqlite3_bind_int(statement, 1, heroId);

    cout << "Weapon | Number Of Kills" << endl;

    while ((returnCode = sqlite3_step(statement)) == SQLITE_ROW) {
        std::string weaponName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
        int kills = sqlite3_column_int(statement, 1);

        cout << weaponName << " | " << kills << endl;
    }

    if (returnCode != SQLITE_DONE) {
        std::cerr << "Error while iterating rows: " << sqlite3_errmsg(database) << endl;
    }

    sqlite3_finalize(statement);

}

void Database::showWeaponHighscore() {

    const char* sqlCommand = R"(
        SELECT 
            Weapon.name AS weaponName,
            Hero.name AS heroName,
            Hero.heroId AS heroId,
            COUNT(*) AS killCount
        FROM 
            MonsterKill, Hero, Weapon
        WHERE 
            MonsterKill.heroId = Hero.heroId AND
            MonsterKill.weaponId = Weapon.weaponId AND
            MonsterKill.heroId = (
                SELECT mk2.heroId
                FROM MonsterKill mk2
                WHERE mk2.weaponId = MonsterKill.weaponId
                GROUP BY mk2.heroId
                ORDER BY COUNT(*) DESC
                LIMIT 1
            )
        GROUP BY Weapon.weaponId;
    )";

    sqlite3_stmt* statement;
    int returnCode = sqlite3_prepare_v2(database, sqlCommand, -1, &statement, nullptr);

    if (returnCode != SQLITE_OK) {
        std::cerr << "Query failed: " << sqlite3_errmsg(database) << endl;
        return;
    }

    cout << "Weapon|  Hero Name|    HeroId| Number Of Kills" << endl;

    while (sqlite3_step(statement) == SQLITE_ROW) {
        string weaponName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
        string heroName = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        int heroId = sqlite3_column_int(statement, 2);
        int kills = sqlite3_column_int(statement, 3);

        cout << weaponName << "|    " <<heroName << "|  " << heroId << "|   " << kills << endl;
    }

    sqlite3_finalize(statement);

}

Database::~Database() {
    closeDataBase();
}