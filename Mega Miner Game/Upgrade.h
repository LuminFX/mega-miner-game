// Upgrade.h

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#ifndef UPGRADE_H
#define UPGRADE_H

#include <iostream>
using namespace std;

// Upgrade object allows the storage of all the possible upgrades and what their "attribute" is (ex: mining level, cooling level, etc)
class Upgrade{
    private: // declares private values
        string name;
        int attribute; //mining level for drill, HP for chassis, size for tank, cooling power for cooler, storage size for storage
        int price;
    public: // declares public functions
        Upgrade();
        Upgrade(string nameIn, int attributeIn, int priceIn);
        string getName();
        int getAttribute();
        int getPrice();
};

#endif