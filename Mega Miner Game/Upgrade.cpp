// Upgrade.cpp

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#include "Upgrade.h"

using namespace std;

// Upgrade object allows the storage of all the possible upgrades and what their "attribute" is (ex: mining level, cooling level, etc)

Upgrade::Upgrade(){
    name = "";
    attribute = 0;
    price = 0;
}
Upgrade::Upgrade(string nameIn, int attributeIn, int priceIn){
    name = nameIn;
    attribute = attributeIn;
    price = priceIn;
}
string Upgrade::getName(){
    return name;
}
int Upgrade::getAttribute(){
    return attribute;
}
int Upgrade::getPrice(){
    return price;
}