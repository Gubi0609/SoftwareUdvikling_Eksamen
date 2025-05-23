#include "Game.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <filesystem>

using namespace std;

Game::Game() {
    currentLevel = 1;
    gameOver = false;
}

/// --- FUNCTIONS FOR HANDLING GAME ---
void Game::topMenu() {
    // Loads the top menu and lets the player choose new or preexisting hero.
    
    int choice;

    cout << "Welcome to the Game!" << endl;
    cout << "(1) Create New Hero" << endl;
    cout << "(2) Load Existing Hero" << endl;
    cout << "(3) Show Overall Stats" << endl;
    cout << "(4) Quit" << endl;
    cout << "Choose an option: ";
    string input;
    cin >> input;

    if (all_of(input.begin(), input.end(), ::isdigit)) {
        choice = stoi(input);
    } else {
        cout << "Invalid choice. Please try again." << endl;
        topMenu();
    }

    string heroName;
    string path = "../heros/";

    switch (choice) {
        case 1:
            cout << "Enter hero name: ";
            cin.ignore();
            getline(cin, heroName);
            hero = database.createHero(heroName);
            startGame();
            break;
        case 2:
            while (true) {
                cout << "Preexisting heros: " << endl;

                database.showHeroSaves();

                cout << "Please enter the Save file of the hero you want to load or 'b' to go back: ";

                string input;
                int heroId;

                cin >> input;

                if (all_of(input.begin(), input.end(), ::isdigit)) {
                    if (heroId <= 0 || heroId > database.getLatestHeroId()) {
                        cout << "Invalid ID. Please try again." << endl;
                    } else {
                        hero = database.loadHero(heroId);
                        break;
                    }
                } else if (input == "b" || input == "B") {
                    cout << "Going back to main menu..." << endl;
                    topMenu();
                }
            }

            startGame();
            break;
        case 3:
            showOverallStats();
            break;
        case 4:
            cout << "Quiting game..." << endl;
            exit(0);
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            topMenu();
            break;
    }
}

void Game::startGame() {
    // Handles the main loop, that keeps the game running while gameOver is false.

    cout << "Starting game with hero: " << hero.getName() << endl;
    cout << "--------------------------------" << endl;

    while (!gameOver) {
        currentLevel = hero.getLevel();
        if (currentLevel < 12) {
            cout << "Current Level: \033[1;34m" << currentLevel << "\033[0m" << endl;
            loadLevel(currentLevel);
        } else {
            cout << "You have defeated the final enemy, and can now retire in peace." << endl;
            gameOver = true;
        }
    }

    cout << "\033[1;31m--- GAME OVER ---\033[0m" << endl;

}

void Game::showOverallStats() {

    int choice;

    while (true) {

        cout << "Choose what stats to display." << endl;
        cout << "(1) Show all heroes in alphabetical order." << endl;
        cout << "(2) Show how many monsters each hero has killed." << endl;
        cout << "(3) Show how many monsters each weapon has killed for a given hero." << endl;
        cout << "(4) Show the name and ID of the hero that has defeated most monsters with a weapon for all used weapons." << endl;
        cout << "(5) Go back to menu." << endl;
        cout << "Please choose an option: ";
        string input;
        cin >> input;

        if (all_of(input.begin(), input.end(), ::isdigit)) {
            choice = stoi(input);
        } else {
            cout << "Invalid choice. Please try again." << endl;
            showOverallStats();
            return;
        }

        int heroIdChoice;
        string heroIdInput;

        switch (choice) {
        case 1:
            database.showHeroesAlphabetically();
            break;
        case 2:
            database.showHeroKils();
            break;
        case 3:

            while (true) {
                database.showHeroesNumerically();
                cout << "Please choose a hero by their ID: ";
                cin >> heroIdInput;

                if (all_of(heroIdInput.begin(), heroIdInput.end(), ::isdigit)) {
                    heroIdChoice = stoi(heroIdInput);

                    if (heroIdChoice <= 0 || heroIdChoice > database.getLatestHeroId()) {
                        cout << "Invalid ID. Please try again." << endl;
                        continue;
                    } else {
                        break;
                    }
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                    continue;
                }
            }
            
            database.showHeroWeaponsKills(heroIdChoice);
            break;
        case 4:
            database.showWeaponHighscore();
            break;
        case 5:
            topMenu();
        default:
            cout << "Invalid choice. Please try again." << endl;
            showOverallStats();
            break;
        }
    }
}

/// --- FUNCTIONS FOR HANDLING DUNGEONS AND ENEMIES --- 
void Game::loadLevel(int level){
    // Loads a list of 4 random dungeons.

    bool validDungeon = false;

    generateDungeonList(level);

    while (!validDungeon) {

        cout << "Available dungeons:" << endl;
        displayDungeonList();

        cout << "Choose a dungeon, 'd' to DISPLAY Hero's STATS, 's' to SAVE or 'q' to EXIT: ";
        string dungeonChoice;
        cin >> dungeonChoice;

        if (all_of(dungeonChoice.begin(), dungeonChoice.end(), ::isdigit)) { // If input is a digit, convert to int.
            
            int choiceIndex = stoi(dungeonChoice);
            
            if (choiceIndex < 0 || choiceIndex > dungeonList.size()) { // If digit is out of range, choice is invalid.
                cout << "Invalid choice. Please try again." << endl;
                continue; // Skips rest of the code in the loop, and loops again.
            }

            if (choiceIndex < dungeonList.size()) {
                currentDungeon = dungeonList[choiceIndex];
                currentDungeonIndex = choiceIndex;

                if (dungeonOptions()) {
                    cout << "\n";
                    cout << "You have chosen to enter a " << currentDungeon->getName() << endl;
                } else {
                    continue;
                }
            } else {
                cout << "You have chosen to interact with " << merchant.getName() << endl;
                loadMerchant();
                continue;
            }

        } else if (dungeonChoice == "d" || dungeonChoice == "D") { // Displays hero stats.
            hero.displayDetails();
            continue;
        } else if (dungeonChoice == "q" || dungeonChoice == "Q") {

            cout << "This will end the game. Any unsaved progress will be lost." << endl;
            cout << "Are you sure you want to quit? (y/n): ";
            string confirmQuit;
            cin >> confirmQuit;

            if (confirmQuit == "y" || confirmQuit == "Y") {
                cout << "Exiting game..." << endl;
                topMenu();
            } else {
                cout << "Continuing game..." << endl;
                continue;
            }
 
        } else if (dungeonChoice == "s" || dungeonChoice == "S") {
            cout << "Are you sure you would like to save your current process? (y/n): ";
            string confirmSave;
            cin >> confirmSave;

            if (confirmSave == "y" || confirmSave == "Y") {
                cout << "Saving process. Please don't close the program while saving..." << endl;
                database.saveHero(hero.getHeroId(), hero.getLevel(), hero.getXP(), hero.getHealth(), hero.getMaxHealth(), hero.getAttackPower(), hero.getGold(), hero.getDurrabilityLeft(), hero.getWeapon()->getWeaponId());
                continue;
            } else {
                cout << "Continuing game..." << endl;
                continue;
            }
        }
        else if (dungeonChoice == "drgn") { // Cheat code for Dragon Dungeon
            hero.setLevel(11);
            hero.setHealth(100);
            hero.setAttackPower(10);
            return;
        } else if (dungeonChoice == "lvlup") { // Cheat code to level up
            hero.gainXP(hero.getLevel()*1000);
            return;
        } else if (dungeonChoice == "lotsofgold") {
            hero.earnGold(1000000);
            return;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        validDungeon = true;

    }
    
    loadCurrentDungeon(); // Loads the current dungeon.

}

void Game::loadCurrentDungeon() {
    // Loads the current dungeon.

    generateEnemyList(currentLevel);
    currentDungeonGold = currentDungeon->getGold();

    cout << "Gold to be earned: \033[1;33m" << currentDungeonGold << " g\033[0m" << endl;
    cout << "--------------------------------" << endl;

    while (enemyList.size() > 0) {

        bool validEnemy = false;

        while (!validEnemy) {

            cout << "Enemies in this dungeon:" << endl;
            displayEnemyList();
    
            cout << "Choose an enemy to battle, 'r' to RUN, or 'q' to EXIT: ";
            string enemyChoice;
            cin >> enemyChoice;
    
            if (all_of(enemyChoice.begin(), enemyChoice.end(), ::isdigit)) { // If input is a digit, convert to int.
                
                int choiceIndex = stoi(enemyChoice);
                
                if (choiceIndex < 0 || choiceIndex >= enemyList.size()) { // If digit is out of range, choice is invalid.
                    cout << "Invalid choice. Please try again." << endl;
                    continue; // Skips rest of the code in the loop, and loops again.
                }
    
                currentEnemy = enemyList[choiceIndex];
                
                if (enemyOptions()) {
                    modifyEnemyList(choiceIndex); // Deletes enemy from list of enemies.
        
                    cout << "\n";
                    cout << "You have chosen to battle a " << currentEnemy->getName() << endl;
                } else {
                    continue;
                }

            } else if (enemyChoice == "q" || enemyChoice == "Q") {
    
                cout << "This will end the game. Any unsaved progress will be lost." << endl;
                cout << "Are you sure you want to quit? (y/n): ";
                string confirmQuit;
                cin >> confirmQuit;
    
                if (confirmQuit == "y" || confirmQuit == "Y") {
                    cout << "Exiting game..." << endl;
                    exit(0);
                } else {
                    cout << "Continuing game..." << endl;
                    continue;
                }
                
            } else if (enemyChoice == "r" || enemyChoice == "R") {
    
                cout << "Running from current dungeon..." << endl;
                return;
    
            } else {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
    
            validEnemy = true;
        }
    
        battle(hero, *currentEnemy);
    }

    modifyDungeonList(currentDungeonIndex);
    cout << "--------------------------------" << endl;
    cout << "You have defeated all enemies in this dungeon." << endl;
    cout << "You earned \033[1;33m" << currentDungeonGold << " g\033[0m!" << endl;
    hero.earnGold(currentDungeonGold);

}

void Game::loadMerchant() {
    
    Weapon* chosenWeapon;
    
    while (true) {
        cout << "Your current gold: \033[1;33m" << hero.getGold() << " g\033[0m." << endl;
        cout << "-------------------------" << endl;

        cout << merchant.getName() << "'s stock: " << endl;
        
        for (int i = 0; i < merchant.getStockList().size(); i++) {
            cout << "(" << i << ") " << merchant.getStockList()[i] << endl;
        }

        string choice;
        cout << "Please choose a stock item or 'r' to go back: ";
        cin >> choice;

        if (all_of(choice.begin(), choice.end(), ::isdigit)) {
            int choiceIndex = stoi(choice);

            if (choiceIndex < 0 || choiceIndex >= merchant.getStockList().size()) {
               cout<< "Invalid choice. Please try again." << endl;
               continue;
            }

            chosenWeapon = merchant.createWeapon(merchant.getStockList()[choiceIndex]);

            cout << "Price of " << chosenWeapon->getName() << ": \033[1;33m" << chosenWeapon->getPrice() << " g\033[0m" << endl;
            cout << "Description: " << chosenWeapon->getDescription() << endl;
            cout << "Damage: \033[1;31m" << chosenWeapon->getAttackPower()+(currentLevel*chosenWeapon->getStrengthModifier()) << "\033[0m. Damage changes as you grow in level." << endl;
            cout << "Durability: " << chosenWeapon->getDurability() << endl;
            cout << "-------------------------" << endl;

            string purchaseChoice;
            cout << "This will replace your current weapon (" << hero.getWeapon()->getName() << ") Do you wish to purchase it? (y/n): ";
            cin >> purchaseChoice;

            if (purchaseChoice == "y" || purchaseChoice == "Y") {
                if (hero.getGold() >= chosenWeapon->getPrice()) {
                    cout << "You purchased the " << chosenWeapon->getName() << endl;
                    hero.spendGold(chosenWeapon->getPrice());
                    hero.obtainWeapon(chosenWeapon);
                    return;
                } else {
                    cout << "You have insufficient funds for this purchase." << endl;
                }
            } else {
                continue;
            }

        } else if (choice == "r" || choice == "R") {
            cout << "Walking away from " << merchant.getName() << endl;
            return;
        } else {
            cout<< "Invalid choice. Please try again." << endl;
        }
    }
}

void Game::battle(Hero& hero, Enemy& enemy) {
    // Starts a battle sequence between Hero and chossen enemy.

    cin.ignore(); // Discard any leftover newline character in the input buffer

    while (!gameOver){

        cout << "Hero: " << hero.getName() << " (Health: \033[1;32m" << hero.getHealth() << "\033[0m)" << endl;
        cout << "Enemy: " << enemy.getName() << " (Health: \033[1;32m" << enemy.getHealth() << "\033[0m)" << endl;
        cout << "Press Enter to attack..." << endl;
        cin.ignore();

        enemy.takeDamage(hero.attackEnemy());

        if (enemy.getHealth() <= 0) {
            cout << enemy.getName() << " has been defeated!" << endl;
            database.registrerKill(hero.getHeroId(), hero.getWeapon()->getWeaponId());
            hero.gainXP(enemy.getXP());
            break;
        }

        cout << "Enemy attacks!" << endl;
        hero.takeDamage(enemy.attackHero());

        if (hero.getHealth() <= 0) {
            cout << hero.getName() << " has been defeated!" << endl;
            gameOver = true;
            break;
        }
    }

    cout << "Hero Health: \033[1;32m" << hero.getHealth() << "\033[0m" << endl;
    cout << "Hero XP: \033[1;36m" << hero.getXP() << "\033[0m" << endl;
    cout << "--------------------------------" << endl;
    currentEnemy = nullptr; // Reset current enemy after battle

}


/// --- FUNCTIONS FOR HANDLING DUNGEONLIST ---
bool Game::dungeonOptions() {
    // Displays options for the current dungeon.
    
    while(true) {
        cout << "Choose what to do ('i' for info, 'e' to enter, 'b' to go back): ";
        string option;
        cin >> option;
        if (option == "i" || option == "I") {
            currentDungeon->showDescription();
        } else if (option == "e" || option == "E") {
            return true; // Enter the dungeon
        } else if (option == "b" || option == "B") {
            cout << "Going back to dungeon list..." << endl;
            return false; // Go back to dungeon list
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

void Game::generateDungeonList(int level) {
    // Generates a list of dungeons based on the current level.

    dungeonList = dungeonFactory.generateDungeonList(level);

}

void Game::displayDungeonList() {
    // Displays the list of dungeons.

    for (int i = 0; i < dungeonList.size(); i++) {
        cout << "(" << i << ") " << dungeonList[i]->getName() << endl;
    }

    cout << "(" << dungeonList.size() << ") " << merchant.getName() << endl;

}

void Game::modifyDungeonList(int position) {
    // Modifies the list of dungeons.
    if (position >= 0 && position < dungeonList.size()) {
        dungeonList.erase(dungeonList.begin() + position);
    } else {
        cout << "Invalid position!" << endl;
    }
}

// --- FUNCTIONS FOR HANDLING ENEMYLIST ---
bool Game::enemyOptions() {
    // Displays options for the current enemy.

    while(true) {
        cout << "Choose what to do ('i' for info, 'a' to attack, 'b' to go back): ";
        string option;
        cin >> option;
        if (option == "i" || option == "I") {
            currentEnemy->displayDetails();
        } else if (option == "a" || option == "A") {
            return true; // Attack the enemy
        } else if (option == "b" || option == "B") {
            cout << "Going back to enemy list..." << endl;
            return false; // Go back to enemy list
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

void Game::generateEnemyList(int level) {
    enemyList = currentDungeon->generateEnemyList(level); // Generates a list of enemies based on the current level.
}

void Game::displayEnemyList() {

    for (int i = 0; i < enemyList.size(); i++) {
        cout << "(" << i << ") " << enemyList[i]->getName() << endl;
    }

}

void Game::modifyEnemyList(int position) {
    currentDungeon->modifyEnemyList(position);
    enemyList = currentDungeon->getEnemyList();
}
