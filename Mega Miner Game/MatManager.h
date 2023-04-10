// MatManager.h

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#ifndef MATMAN_H
#define MATMAN_H

#include <iostream>
#include <vector>
#include "Material.h"
using namespace std;

/*
MatManager manages the materials in the Game by keeping them in a vector. It doesnt have a lot of functions, but the included ones are very useful.
*/
class MatManager{
    private: // declares private values
        vector<Material> matList; // vector to store materials
    public: // declares public functions
        MatManager();
        int loadMaterials(string materialData); // reads data from text file and puts materials into array
        vector<Material> getMatList();
};

#endif