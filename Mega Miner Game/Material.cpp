// Material.cpp

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#include <iostream>
#include "Material.h"

using namespace std;

Material::Material(){ // default constructor, sets everything to blank or zero.
    name = "";
    miningLevel = 0;
    value = 0;
    storageSize = 0;
    symbol = '.';
}
Material::Material(string nameIn, int miningLevelIn, int valueIn, int storageSizeIn, char symbolIn){ // paramatrized constructor, takes input values for all
    name = nameIn;
    miningLevel = miningLevelIn;
    value = valueIn;
    storageSize = storageSizeIn;
    symbol = symbolIn;
}
string Material::getName(){
    return name;
}
int Material::getMiningLevel(){
    return miningLevel;
}
int Material::getValue(){
    return value;
}
int Material::getStorageSize(){
    return storageSize;
}
char Material::getSymbol(){
    return symbol;
}