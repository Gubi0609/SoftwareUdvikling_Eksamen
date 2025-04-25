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

void Game::topMenu() {
    // Loads the top menu and lets the player choose new or preexisting hero.
    
    int choice;

    cout << "Welcome to the Game!" << endl;
    cout << "1. Create New Hero" << endl;
    cout << "2. Load Existing Hero" << endl;
    cout << "3. Exit" << endl;
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
    string path = "./heros/";

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
        cout << "Current Level: " << currentLevel << endl;
        loadLevel(currentLevel);
    }

}

void Game::loadLevel(int level){
    // Loads a list of 4 random enemies based on the heros level.

    bool validEnemy = false;

    if (enemyList.size() <= 0) { // If all enemies are defeated, generate a new list.
        getEnemyList(level);
    }

    while (!validEnemy) {

        cout << "Available enemies:\n";
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

            currentEnemy = createEnemy(enemyList[choiceIndex]);
            modifyEnemyList(choiceIndex); // Deletes enemy from list of enemies.

            cout << "\n";
            cout << "You have chosen to battle a " << currentEnemy->getName() << endl;

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

            cout << "Running from current enemies..." << endl;
            enemyList.clear();
            loadLevel(level);

        } else {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        validEnemy = true;
    }

    battle(hero, *currentEnemy); // Starts a battle sequence with chossen enemy.
}

void Game::getEnemyList(int level) {
    // Generates a random enemy list of size 4 based on heros level.

    vector<string> possibleEnemies;

    if (level <= 1) {
        possibleEnemies = {"Wolf", "Small Troll", "Troll"};
    } else if (level <= 3) {
        possibleEnemies = {"Weak Goblin", "Goblin", "Goblin Guard"};
    } else if (level == 4) {
        possibleEnemies = {"Goblin King"}; // Boss fight
    } else if (level <= 5) {
        possibleEnemies = {"Weak Goblin", "Goblin", "Goblin Guard"};
    } else if (level == 6) {
        possibleEnemies = {"Gollum"}; // Boss fight
    } else if (level <= 7) {
        possibleEnemies = {"Wolf", "Small Troll", "Troll", "Weak Goblin", "Goblin"};
    } else if (level <= 9) {
        possibleEnemies = {"Spider", "Giant Spider", "Wolf"};
    } else if (level <= 10) {
        possibleEnemies = {"Wolf", "Small Troll", "Troll"};
    } else if (level == 11) {
        possibleEnemies = {"Dragon"}; //Boss fight
    } else {
        possibleEnemies = {"Wolf", "Small Troll", "Troll", "Weak Goblin", "Goblin", "Goblin Guard", "Spider", "Giant Spider"}; // All non-boss enemies
    }

    if (possibleEnemies.size() > 1) { // If more than one enemy in list of possible enemies (not a boss fight), randomize choice.

        random_device rd; // Seed for random number generator
        mt19937 g(rd());  // Mersenne Twister random number generator
        uniform_int_distribution<> dist(0, possibleEnemies.size() - 1);

        enemyList.clear();

        for (int i = 0; i < 4; ++i) {
            int randomIndex = dist(g);
            enemyList.push_back(possibleEnemies[randomIndex]);
        }

    } else {
        enemyList = possibleEnemies; // Boss fight
    }
}

void Game::displayEnemyList() {

    for (int i = 0; i < enemyList.size(); i++) {
        cout << enemyList[i] << "(" << i << ")\n";
    }

}

void Game::modifyEnemyList(int position) {
    enemyList.erase(enemyList.begin() + position);
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

}

void Game::loadHero(string filename) {
    // Load hero from file or database

    ifstream file("./heros/"+filename+".txt"); // Opens hero-file based on filename

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

Enemy* Game::createEnemy(string enemyType) {
    // Create enemy from given type

    if (enemyType == "Wolf") {
        return new Wolf();
    } else if (enemyType == "Small Troll") {
        return new SmallTroll();
    } else if (enemyType == "Troll") {
        return new Troll();
    } else if (enemyType == "Weak Goblin") {
        return new WeakGoblin();
    } else if (enemyType == "Goblin") {
        return new Goblin();
    } else if (enemyType == "Goblin Guard") {
        return new GoblinGuard();
    } else if (enemyType == "Goblin King") {
        return new GoblinKing();
    } else if (enemyType == "Gollum") {
        return new Gollum();
    } else if (enemyType == "Spider") {
        return new Spider();
    } else if (enemyType == "Giant Spider") {
        return new GiantSpider();
    } else if (enemyType == "Dragon") {
        return new Dragon();
    }
    return nullptr;
}