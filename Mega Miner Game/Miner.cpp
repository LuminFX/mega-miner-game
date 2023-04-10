// Miner.cpp

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#include "Miner.h"
#include <iostream>

using namespace std;

// miner class stores information about the miner. its level, etc. most functions are self explanatory

Miner::Miner(){
    drillLevel = 0;
    chassisLevel = 0;
    coolingLevel = 0;
    tankLevel = 0;
    storageLevel = 0;
}
Miner::Miner(int drillLevelIn, int chassisLevelIn, int coolingLevelIn, int tankLevelIn, int storageLevelIn){
    drillLevel = drillLevelIn;
    chassisLevel = chassisLevelIn;
    coolingLevel = coolingLevelIn;
    tankLevel = tankLevelIn;
    storageLevel = storageLevelIn;
}
int Miner::getDrillLevel(){
    return drillLevel;
}
void Miner::setDrillLevel(int drillLevelIn){
    drillLevel = drillLevelIn;
}
int Miner::getChassisLevel(){
    return chassisLevel;
}
void Miner::setChassisLevel(int chassisLevelIn){
    chassisLevel = chassisLevelIn;
}
int Miner::getCoolingLevel(){
    return coolingLevel;
}
void Miner::setCoolingLevel(int coolingLevelIn){
    coolingLevel = coolingLevelIn;
}
int Miner::getTankLevel(){
    return tankLevel;
}
void Miner::setTankLevel(int tankLevelIn){
    tankLevel = tankLevelIn;
}
int Miner::getStorageLevel(){
    return storageLevel;
}
void Miner::setStorageLevel(int storageLevelIn){
    storageLevel = storageLevelIn;
}