// Miner.h

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#ifndef MINER_H
#define MINER_H

#include <iostream>
using namespace std;

// miner class stores information about the miner. its level, etc. most functions are self explanatory

class Miner{
    private: // declares private values
        int drillLevel;
        int chassisLevel;
        int coolingLevel;
        int tankLevel;
        int storageLevel;
    public: // declares public functions
        Miner();
        Miner(int drillLevelIn, int chassisLevelIn, int coolingLevelIn, int tankLevelIn, int storageLevelIn);
        int getDrillLevel();
        void setDrillLevel(int drillLevelIn);
        int getChassisLevel();
        void setChassisLevel(int chassisLevelIn);
        int getCoolingLevel();
        void setCoolingLevel(int coolingLevelIn);
        int getTankLevel();
        void setTankLevel(int tankLevelIn);
        int getStorageLevel();
        void setStorageLevel(int storageLevelIn);
};

#endif