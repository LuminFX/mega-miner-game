// Map.h

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "Material.h"

using namespace std;

class Map
{
private:
    
    const char UNEXPLORED = '?'; // marker for unexplored spaces
    const char PARTY = 'M';      // marker for party position


    static const int num_rows_ = 80; // number of rows in map
    static const int num_cols_ = 25; // number of columns in map
    static const int max_npcs_ = 5;  // max non-player characters
    static const int max_rooms_ = 5; // max number of rooms

    int player_position_[2];              // player position (row,col)
    int dungeon_exit_[2];                 // exit location of the dungeon
    int npc_positions_[max_npcs_][3];     // stores the (row,col) positions of NPCs present on map and if they have been found
    int room_positions_[max_rooms_][2];   // stores the (row,col) positions of rooms present on map
    char map_data_[num_rows_][num_cols_]; // stores the character that will be shown at a given (row,col)
    Material map_data_mats[num_rows_][num_cols_]; // stores materials for map

    int npc_count_;  // stores number of misfortunes currently on map
    int room_count_; // stores number of sites currently on map
public:

    Map();

    void resetMap();

    // getters
    int getPlayerRow();
    int getPlayerCol();
    int getNumRows();
    int getNumCols();
    bool isOnMap(int row, int col);
    bool isExplored(int row, int col);

    // setters
    void setPlayerPosition(int row, int col);
    void setDungeonExit(int row, int col);

    // other
    void displayMap();
    void displayArea();
    int genMap(vector<Material>);
    Material getMaterialAt(int row, int col);
    void setMaterialAt(int row, int col, Material mat);
    int move(char);
    void exploreSpace(int row, int col);
};

#endif
