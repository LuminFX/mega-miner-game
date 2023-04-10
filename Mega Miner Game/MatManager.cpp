// MatManager.cpp

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#include "MatManager.h"
#include "Material.h"
#include <fstream>

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

int vecSplit(string inputString, char seperator, vector<string>& vector){ // split function but using vector instead of array
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

MatManager::MatManager(){ //default constructor, not much to set up so vector is cleared for good measure.
    matList.clear();
}

/*
loadMaterials reads the material file and adds everything to the material vector.
1. create a vector and a split character, as well as an ifstream object and a storage string
2. open the file of inputted name, and return -1 if it failed
3. while it isnt the end of the file
    4. get the next line from the file, split it, and add it to the material if it split properly.
*/
int MatManager::loadMaterials(string materialData){ //load all data from the material data file

    vector<string> data;
    char splitter = ',';

    ifstream materialInput;

    string lineStorage; // destination for things gathered from stream

    materialInput.open(materialData); // open file
    if (materialInput.fail()){ // if open failed, return corresponding value.
        return -1;
    }

    while(!materialInput.eof()){

        getline(materialInput, lineStorage);
        if(lineStorage.empty() || vecSplit(lineStorage, splitter, data) != 5){ // if there is nothing in the line or the split function returns an incorrect value return fail flag
            return -2;
        }
        else{
            matList.push_back(Material(data.at(0),stoi(data.at(1)),stoi(data.at(2)),stoi(data.at(3)),data.at(4)[0])); // add all split data to material list
        }

    }
    return 0;
}

vector<Material> MatManager::getMatList(){ // returns the vector list of materials
    return matList;
}