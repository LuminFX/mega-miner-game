// UpgradeManager.h

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#ifndef UPGMAN_H
#define UPGMAN_H

#include <iostream>
#include <vector>
#include "Upgrade.h"
using namespace std;

// UpgradeManager manages the upgrades read from the upgrades file. Keeps them in easy access for use in the MegaMiner class.
class UpgradeManager{
    private: // declares private values, all vectors that store each type of upgrade
        vector<Upgrade> drillUpgrades;
        vector<Upgrade> chassisUpgrades;
        vector<Upgrade> coolingUpgrades;
        vector<Upgrade> tankUpgrades;
        vector<Upgrade> storageUpgrades;
    public: // declares public functions, basic getters and setters
        UpgradeManager();
        int loadUpgrades(string upgradeData); // loads upgrades from file
        Upgrade getDrill(int level);
        Upgrade getChassis(int level);
        Upgrade getCooler(int level);
        Upgrade getTank(int level);
        Upgrade getStorageModule(int level);
};

#endif