// Material.h

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
using namespace std;

/*
The material class stores data for the materials used in the game. Materials are made for Coal, Iron, Dirt, etc.
*/

class Material{
    private: // declares private values
        string name;
        int miningLevel; // level of drill required to mine material
        int value; // sell price of material
        int storageSize; // how much space the material takes up in storage
        char symbol; // display material on map
    public: // declares public functions
        Material();
        Material(string nameIn, int miningLevelIn, int valueIn, int storageSizeIn, char symbolIn);
        string getName();
        int getMiningLevel();
        int getValue();
        int getStorageSize(); 
        char getSymbol();
};

#endif