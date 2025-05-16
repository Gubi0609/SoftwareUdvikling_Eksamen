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
    cout << "(3) Exit" << endl;
    cout << "Choose an option: ";
    string input;
    cin >> input;

    if (all_of(input.begin(), input.end(), ::isdigit)) {
        choice = stoi(input);
    } else {
        cout << "Invalid choice. Please try again." << endl;
        topMenu();
        return;
    }

    string heroName;
    string path = "../heros/";

    switch (choice) {
        case 1:
            cout << "Enter hero name: ";
            cin >> heroName;
            hero = Hero(heroName);
            startGame();
            break;
        case 2:
            cout << "Preexisting heros: " << endl;

            // List existing heroes here
            for (const auto & entry : filesystem::directory_iterator(path))
                cout << entry.path().stem() << endl;

            cout << "Enter hero name to load: ";
            cin >> heroName;
            loadHero(heroName);
            startGame();
            break;
        case 3:
            cout << "Exiting game..." << endl;
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
            cout << "Current Level: " << currentLevel << endl;
            loadLevel(currentLevel);
        } else {
            gameOver = true;
            cout << "You have defeated the final enemy, and can now retire in peace." << endl;
        }
    }

    cout << "--- GAME OVER ---" << endl;

}

/// --- FUNCTIONS FOR HANDLING DUNGEONS AND ENEMIES --- 
void Game::loadLevel(int level){
    // Loads a list of 4 random dungeons.

    bool validDungeon = false;

    generateDungeonList(level);

    while (!validDungeon) {

        cout << "Available dungeons:" << endl;
        displayDungeonList();

        cout << "Choose a dungeon, 'd' to display Hero's stats or 'q' to quit: ";
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
                exit(0);
            } else {
                cout << "Continuing game..." << endl;
                continue;
            }

        } else if (dungeonChoice == "drgn") { // Cheat code for Dragon Dungeon
            hero.setLevel(11);
            hero.setHealth(100);
            hero.setAttackPower(10);
            return;
        } else if (dungeonChoice == "lvlup") { // Cheat code to level up
            hero.gainXP(hero.getLevel()*1000);
            return;
        } else {
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

    cout << "Gold to be earned: " << currentDungeonGold<< endl;
    cout << "--------------------------------" << endl;

    while (enemyList.size() > 0) {

        bool validEnemy = false;

        while (!validEnemy) {

            cout << "Enemies in this dungeon:" << endl;
            displayEnemyList();
    
            cout << "Choose an enemy to battle, 'r' to run, or 'q' to quit: ";
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
    cout << "You earned " << currentDungeonGold << " gold!" << endl;
    hero.earnGold(currentDungeonGold);

}

void Game::loadMerchant() {
    
    Weapon* chosenWeapon;
    
    while (true) {
        cout << "Your current gold: " << hero.getGold() << " g." << endl;
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

            cout << "Price of " << chosenWeapon->getName() << ": " << chosenWeapon->getPrice() << " g" << endl;
            cout << "Description: " << chosenWeapon->getDescription() << endl;
            cout << "Damage: " << chosenWeapon->getAttackPower()+(currentLevel*chosenWeapon->getStrengthModifier()) << ". Damage changes as you grow in level." << endl;
            cout << "Durability: " << chosenWeapon->getDurability() << endl;
            cout << "-------------------------" << endl;

            string purchaseChoice;
            cout << "This will replace your current weapon (" << hero.getWeapon()->getName() << ") Do you wish to purchase it? (y/n): ";
            cin >> purchaseChoice;

            if (purchaseChoice == "y" || purchaseChoice == "Y") {
                if (hero.getGold() >= chosenWeapon->getPrice()) {
                    cout << "You purchased the " << chosenWeapon->getName() << endl;
                    hero.spendGold(chosenWeapon->getPrice());
                    hero.setWeapon(chosenWeapon);
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

        cout << "Hero: " << hero.getName() << " (Health: " << hero.getHealth() << ")" << endl;
        cout << "Enemy: " << enemy.getName() << " (Health: " << enemy.getHealth() << ")" << endl;
        cout << "Press Enter to attack..." << endl;
        cin.ignore();

        enemy.takeDamage(hero.attackEnemy());

        if (enemy.getHealth() <= 0) {
            cout << enemy.getName() << " has been defeated!" << endl;
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

    cout << "Hero Health: " << hero.getHealth() << endl;
    cout << "Hero XP: " << hero.getXP() << endl;
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

/// --- FUNCTIONS FOR HANDLING HERO ---
void Game::loadHero(string filename) {
    // Load hero from file or database

    ifstream file("../heros/"+filename+".txt"); // Opens hero-file based on filename

    if (file.is_open()) {

        string name;
        int level, health, attackPower, xp;

        string line;

        while(getline(file, line)) { /// Read line by line from file

            if (line.find("Name:") != string::npos) { // If line contains name, read name from line
                name = line.substr(line.find(":") + 1);

            } else if (line.find("Health:") != string::npos) { // If line contains health, read health from line
                health = stoi(line.substr(line.find(":") + 1));

            }else if (line.find("attackPower:") != string::npos) { // If line contains attackPower, read attackPower from line
                attackPower = stoi(line.substr(line.find(":") + 1));

            } else if (line.find("XP:") != string::npos) { // If line contains XP, read XP from line
                xp = stoi(line.substr(line.find(":") + 1));

            } else if (line.find("Level:") != string::npos) { // If line contains level, read level from line
                level = stoi(line.substr(line.find(":") + 1));

            }
        }

        cout << "Current Hero stats: " << endl;
        cout << "Name: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Attack Power: " << attackPower << endl;
        cout << "XP: " << xp << endl;
        cout << "Level: " << level << endl;

        cout << "--------------------------------" << endl;
        cout << "Do you want to continue with the current hero? (y/n): ";
        string confirmLoad;
        cin >> confirmLoad;

        if (confirmLoad == "y" || confirmLoad == "Y") {
            cout << "Continuing with the current hero..." << endl;

            // Create hero from given arguments
            hero = Hero(name);
            hero.setLevel(level);
            hero.setHealth(health);
            hero.setAttackPower(attackPower);
            hero.setXP(xp);

        } else {
            cout << "Returning to main menu..." << endl;
            topMenu();
        }

        file.close();
    } else { // If file didn't open
        cout << "Error loading hero from file." << endl;
        topMenu();
    }

}