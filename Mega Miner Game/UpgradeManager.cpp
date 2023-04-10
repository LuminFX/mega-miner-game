// UpgradeManger.cpp

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#include "UpgradeManager.h"
#include <fstream>
#include <iostream>

using namespace std;

/*
VecSplit is the vector adaptation of the Split function we coded back in (i believe) homework 5
1. clear vector
2. declare variables for keeping track of start and index
3. loop through the length of the input string
    4. if the current character is the seperator char
        5. add current segment of string to vector.
        6. update start flag
        7. increment index
8. add current string to vector (catches exceptions and last value)
9. return size of vector.
*/

int vecSplit1(string inputString, char seperator, vector<string>& vector){ // split function using vector instead of array
    vector.clear();
    int start = 0, index = 0; // declare indexes for tracking
    for (int i=0; i<inputString.length(); i++){
        if (inputString[i] == seperator){ // when it finds the seperator
            vector.push_back(inputString.substr(start,(i-start))); //set the array index to the substring found.
            start = i+1;
            index++;
        }
    }
    vector.push_back(inputString.substr(start,(inputString.length()-start))); // last catch case, assign last part of the string to the array

    return vector.size();
}

UpgradeManager::UpgradeManager(){ // basic constructor, nothing needs to be set but vectors are cleared for good measure.
    drillUpgrades.clear();
    chassisUpgrades.clear();
    coolingUpgrades.clear();
    tankUpgrades.clear();
    storageUpgrades.clear();
}

/*
loadUpgrades reads upgrades from a file and puts them in the correct storage vectors.
1. declare necesary variables and open file. If fail, return -1.
2. while the file hasnt ended
    3. get the next line.
    4. if it is a new line identifier, update the loading phase
    5. if the END flag is found, return 0.
    6. if no phase is set, there is an issue with the file. return -2.
    7. switch based on phase
        8. depending on phase, split line from file and put it in appropriate vector
*/

int UpgradeManager::loadUpgrades(string upgradeData){ // reads upgrade data from file

    vector<string> data;
    char splitter = ',';

    ifstream upgradeInput;

    string lineStorage; // destination for things gathered from stream

    upgradeInput.open(upgradeData); // open file
    if (upgradeInput.fail()){ // if open failed, return corresponding value.
        return -1;
    }

    int phase = -1;

    while(!upgradeInput.eof()){

        getline(upgradeInput, lineStorage);

        if (lineStorage == "drill:"){
            phase = 0;
            getline(upgradeInput, lineStorage);
        }
        else if (lineStorage == "chassis:"){
            phase = 1;
            getline(upgradeInput, lineStorage);
        }
        else if (lineStorage == "cooler:"){
            phase = 2;
            getline(upgradeInput, lineStorage);
        }
        else if (lineStorage == "tank:"){
            phase = 3;
            getline(upgradeInput, lineStorage);
        }
        else if (lineStorage == "storage:"){
            phase = 4;
            getline(upgradeInput, lineStorage);
        }
        else if (lineStorage == "END"){
            return 0;
        }

        if(phase == -1 || lineStorage.empty() || vecSplit1(lineStorage, splitter, data) != 3){
            return -2;
        }

        switch (phase)
        {
        case 0:
            drillUpgrades.push_back(Upgrade(data.at(0), stoi(data.at(1)), stoi(data.at(2))));
            break;
        case 1:
            chassisUpgrades.push_back(Upgrade(data.at(0), stoi(data.at(1)), stoi(data.at(2))));
            break;
        case 2:
            coolingUpgrades.push_back(Upgrade(data.at(0), stoi(data.at(1)), stoi(data.at(2))));
            break;
        case 3:
            tankUpgrades.push_back(Upgrade(data.at(0), stoi(data.at(1)), stoi(data.at(2))));
            break;
        case 4:
            storageUpgrades.push_back(Upgrade(data.at(0), stoi(data.at(1)), stoi(data.at(2))));
            break;
        default:
            break;
        }

    }

    return 0;

}
Upgrade UpgradeManager::getDrill(int level){
    return drillUpgrades.at(level);
}
Upgrade UpgradeManager::getChassis(int level){
    return chassisUpgrades.at(level);
}
Upgrade UpgradeManager::getCooler(int level){
    return coolingUpgrades.at(level);
}
Upgrade UpgradeManager::getTank(int level){
    return tankUpgrades.at(level);
}
Upgrade UpgradeManager::getStorageModule(int level){
    return storageUpgrades.at(level);
}