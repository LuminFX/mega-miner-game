// MegaMiner.h

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#ifndef MEGAMINER_H
#define MEGAMINER_H

#include <iostream>
#include "Miner.h"
#include "MatManager.h"
#include "UpgradeManager.h"
#include "Map.h"
using namespace std;

class MegaMiner{
    private: // declares private values
        string name;
        int health;
        int money;
        double fuel;
        Miner miner;
        MatManager matManager;
        UpgradeManager upgradeManager;
        Map map = Map();
        vector<Material> matsStored;
        double unitsStored;
        vector<string> winners;
        
    public: // declares public functions
        MegaMiner(); // starts regular game and initializes all values
        MegaMiner(string nameIn, int healthIn, int moneyIn, int fuelIn, Miner minerIn, MatManager matManagerIn, UpgradeManager upgradeManagerIn);
        void generateMap(); // randomly generates map
        int move(char input); // moves
        void viewMap(); // shows maps and allows navivation of levels
        void viewArea(); // shows immediate area around player
        void viewStorage(); // shows storage
        void viewStats(); // shows stats
        int quit(); // quits
        int loadData(string upgradeData, string materialData); // load data from files for materials and upgrades
        string getName();
        void setName(string nameIn);
        int getHealth();
        int getMoney();
        void setMoney(int moneyIn);
        double getFuel();
        void setFuel(double fuelIn);
        Miner getMiner();
        MatManager getMatManager();
        UpgradeManager getUpgradeManager();
        double getUnitsStored();
        void setUnitsStored(double unitsIn);
        void upgrade(int identifier, int level);
        int sellInventory();
        void printFuelRepairCost();
        int refuelRepair();
        int getDepth();
        int gamble(int betID, int amount);
        void printWinners();
        void addWinner(string winner);
        void saveWinners();
};

#endif