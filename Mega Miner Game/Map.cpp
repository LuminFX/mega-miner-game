// Map.cpp

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#include "Map.h"
#include <iomanip>
#include <vector>

using namespace std;

double randomDouble(){ // randomDouble returns a random double between 0 and 1.
    return double(rand()) / (double(RAND_MAX) + 1.0);
}

Map::Map()
{
    resetMap();
}

/*
resetMap clears the map display array and all the materials stored in the material array
1. set player position (row and column) to default values (top middle of map)
2. loop through amount of rows and columns and set display array to unexplored and material array to default empty material 
 */
void Map::resetMap()
{

    player_position_[0] = 0;
    player_position_[1] = 12;

    for (int i = 0; i < num_rows_; i++)
    {
        for (int j = 0; j < num_cols_; j++)
        {
            map_data_[i][j] = UNEXPLORED;
            map_data_mats[i][j] = Material();
        }
    }
    

}

/*
genMap randomly generates where the ores spawn underground.
1. initialize currProb as 0 and initialize srand
2. loop through first layer of map and set all materials to air. Update display array to air characters.
3. loop through first layer of map and set all materials to Dirt. Update display array to dirt characters.
4. loop through all rows of map
    5. loop through all colums of map
        6. depending on level in map, enter an if statement and assign position to a material randomly, with specific rand values per layer. DONT UPDATE DISPLAY ARRAY HERE, they are not explored yet
*/

int Map::genMap(vector<Material> matsVec){

    double currProb=0;

    for (int j = 0; j < num_cols_; j++) // set first layer to air
    {
        map_data_mats[0][j] = matsVec.at(0);
        map_data_[0][j] = map_data_mats[0][j].getSymbol();
    }

    for (int j = 0; j < num_cols_; j++) // set second layer to dirt
    {
        map_data_mats[1][j] = matsVec.at(1);
        map_data_[1][j] = map_data_mats[1][j].getSymbol();
    }

    for (int i = 2; i < num_rows_; i++) // loop through rows
    {
        for (int j = 0; j < num_cols_; j++) // loop through columnds
        {
            currProb = randomDouble(); // get random int

            if (i<10){ // if statments check for row and generate ores depending on it.
                if(currProb <= 0.10){ // 10% coal
                    map_data_mats[i][j] = matsVec.at(4);
                }
                else if(currProb<= 0.17){ // 2% iron
                    map_data_mats[i][j] = matsVec.at(5);
                }
                else{
                    map_data_mats[i][j] = matsVec.at(1);
                }
            }
            else if (i<20){
                if (currProb <= 0.15){ // 15% coal
                    map_data_mats[i][j] = matsVec.at(4);
                }
                else if(currProb<= 0.25){ // 10% iron
                    map_data_mats[i][j] = matsVec.at(5);
                }
                else if(currProb <= 0.30){ // 5% silver
                    map_data_mats[i][j] = matsVec.at(6);
                }
                else{
                    map_data_mats[i][j] = matsVec.at(1);
                }
            }
            else if (i<30){
                if (currProb <= 0.02){ // 2% boulder
                    map_data_mats[i][j] = matsVec.at(3);
                }
                else if(currProb<= 0.12){ // 10% coal
                    map_data_mats[i][j] = matsVec.at(4);
                }
                else if(currProb <= 0.27){ // 15% Iron
                    map_data_mats[i][j] = matsVec.at(5);
                }
                else if(currProb <= 0.32){ // 5% silver
                    map_data_mats[i][j] = matsVec.at(6);
                }
                else if(currProb <= 0.37){ // 5% Gold
                    map_data_mats[i][j] = matsVec.at(7);
                }
                else if(currProb <= 0.45){ // 7% stone
                    map_data_mats[i][j] = matsVec.at(2);
                }
                else{
                    map_data_mats[i][j] = matsVec.at(1);
                }
            }
            else if (i<40){
                if (currProb <= 0.05){ // 5% boulder
                    map_data_mats[i][j] = matsVec.at(3);
                }
                else if(currProb<= 0.15){ // 10% iron
                    map_data_mats[i][j] = matsVec.at(5);
                }
                else if(currProb <= 0.35){ // 20% Silver
                    map_data_mats[i][j] = matsVec.at(6);
                }
                else if(currProb <= 0.45){ // 10% Gold
                    map_data_mats[i][j] = matsVec.at(7);
                }
                else if(currProb <= 0.50){ // 5% Sapphire
                    map_data_mats[i][j] = matsVec.at(8);
                }
                else if(currProb <= 0.70){ // 20% stone
                    map_data_mats[i][j] = matsVec.at(2);
                }
                else{
                    map_data_mats[i][j] = matsVec.at(1);
                }
            }
            else if (i<50){
                if (currProb <= 0.05){ // 5% boulder
                    map_data_mats[i][j] = matsVec.at(3);
                }
                else if(currProb <= 0.15){ // 10% Silver
                    map_data_mats[i][j] = matsVec.at(6);
                }
                else if(currProb <= 0.35){ // 20% Gold
                    map_data_mats[i][j] = matsVec.at(7);
                }
                else if(currProb <= 0.50){ // 15% Sapphire
                    map_data_mats[i][j] = matsVec.at(8);
                }
                else if(currProb <= 0.52){ // 2% Emerald
                    map_data_mats[i][j] = matsVec.at(9);
                }
                else if(currProb <= 0.72){ // 20% stone
                    map_data_mats[i][j] = matsVec.at(2);
                }
                else{
                    map_data_mats[i][j] = matsVec.at(1);
                }
            }
            else if (i<60){
                if (currProb <= 0.10){ // 20% boulder
                    map_data_mats[i][j] = matsVec.at(3);
                }
                else if(currProb <= 0.15){ // 5% Gold
                    map_data_mats[i][j] = matsVec.at(7);
                }
                else if(currProb <= 0.20){ // 10% Sapphire
                    map_data_mats[i][j] = matsVec.at(8);
                }
                else if(currProb <= 0.35){ // 15% Emerald
                    map_data_mats[i][j] = matsVec.at(9);
                }
                else if(currProb <= 0.40){ // 5% Ruby
                    map_data_mats[i][j] = matsVec.at(10);
                }
                else{
                    map_data_mats[i][j] = matsVec.at(2);
                }
            }
            else if (i<70){
                if (currProb <= 0.20){ // 20% boulder
                    map_data_mats[i][j] = matsVec.at(3);
                }
                else if(currProb <= 0.30){ // 10% Emerald
                    map_data_mats[i][j] = matsVec.at(9);
                }
                else if(currProb <= 0.40){ // 10% Ruby
                    map_data_mats[i][j] = matsVec.at(10);
                }
                else if(currProb <= 0.50){ // 10% Diamond
                    map_data_mats[i][j] = matsVec.at(11);
                }
                else{
                    map_data_mats[i][j] = matsVec.at(2);
                }
            }
            else if (i<76){
                if (currProb <= 0.30){ // 30% boulder
                    map_data_mats[i][j] = matsVec.at(3);
                }
                else if(currProb <= 0.50){ // 20% Ruby
                    map_data_mats[i][j] = matsVec.at(10);
                }
                else if(currProb <= 0.70){ // 20% Diamond
                    map_data_mats[i][j] = matsVec.at(11);
                }
                else{
                    map_data_mats[i][j] = matsVec.at(2);
                }
            }
            else{ // generates boulders in the bottom 4 levels.
                map_data_mats[i][j] = matsVec.at(3);
            }  

        }
    }

    return 0;

}

// return player's row position
int Map::getPlayerRow()
{
    return player_position_[0];
}

// return player's column position
int Map::getPlayerCol()
{
    return player_position_[1];
}

// returns member variable num_rows_
int Map::getNumRows()
{
    return num_rows_;
}

// returns member variable num_cols_
int Map::getNumCols()
{
    return num_cols_;
}

/*
 * @brief Checks if the given (row, col) position is on the map
 *
 * Algorithm:
 *  if 0 <= row < num_rows_ and 0 <= col < num_cols_:
 *      return true
 *  else:
 *      return false
 *
 * Parameters: row (int), col (int)
 * Returns: bool
 */
bool Map::isOnMap(int row, int col)
{
    if (0 <= row && row < num_rows_ && 0 <= col && col < num_cols_)
    {
        return true;
    }
    return false;
}

/*
exploreSpace takes the character data from the generated material map, and displays it to the user by putting it in the display array
 */
void Map::exploreSpace(int row, int col)
{

    map_data_[row][col] = map_data_mats[row][col].getSymbol();

}

/*
 * Algorithm: Make the player move based on the given command
 * if user inputs w and if its not the top row of the map
 *      Move the player up by one row
 * if user inputs s and if its not the bottom row of the map
 *      Move the player down by one row
 * if user inputs a and if its not the leftmost column
 *      Move the player left by one column
 * if user inputs d and if its not the rightmost column
 *      Move the player right by one column
 * if player moved
 *      if new location is an NPC location
 *          mark new location as explored
 *      return true
 * else
 *      return false
 * 
 * loop through nearest 3 spaces on each side of player and explore them
 *
 * Parameters: direction (char)
 * Return: boolean (bool)
 */
int Map::move(char direction)
{
    // check input char and move accordingly
    switch (tolower(direction))
    {
    case 'w': // if user inputs w, move up if it is an allowed move
        if (player_position_[0] > 0)
        {
            player_position_[0] -= 1;
        }
        else
        {
            return -1;
        }
        break;
    case 's': // if user inputs s, move down if it is an allowed move
        if (player_position_[0] < num_rows_ - 1)
        {
            player_position_[0] += 1;
        }
        else
        {
            return -1;
        }
        break;
    case 'a': // if user inputs a, move left if it is an allowed move
        if (player_position_[1] > 0)
        {
            player_position_[1] -= 1;
        }
        else
        {
            return -1;
        }
        break;
    case 'd': // if user inputs d, move right if it is an allowed move
        if (player_position_[1] < num_cols_ - 1)
        {
            player_position_[1] += 1;
        }
        else
        {
            return -1;
        }
        break;
    default:
        return -1;
    }

    
    for (int i=getPlayerRow()-2; i<=getPlayerRow()+2; i++){
        for (int j=getPlayerCol()-2; j<=getPlayerCol()+2; j++){

            if ((i < num_rows_ && i >= 0) && (j<num_cols_ && j >= 0)){
                exploreSpace(i,j);
            }

        }

    }


    return 0;
}

/*
Displays the entire map, shows question marks if something isnt explored.
1. loop through rows
    2. loop through columns
        3. if the targeted position equals the player position, display the player character
        4. else print map data
*/

void Map::displayMap(){
    
    for (int i=0; i<num_rows_; i++){
        for (int j=0; j<num_cols_; j++){
            if (player_position_[0] == i && player_position_[1] == j)
            {
                cout << setw(2) << left << PARTY;
            }
            else{
                cout << setw(2) << left << map_data_[i][j];
            }
        }
        cout << endl;
    }

}

/*
displayArea displays the area immediately around the player in a 7x7 grid.
Main logic:
1. loop through nearest 3 rows on each side
    2. loop through nearest 3 columns on each side
        3. if targeted position equals player position, print player character
        4. else print map data

Exception logic:
if the 7x7 area will go somewhere that is out of the map, adjust the display so it doesnt go out of bounds, and shows the player moving instead.
This is important at the edges of the map so garbage data isn't displayed.
*/

void Map::displayArea(){

    int playerRow = getPlayerRow(); // acounts for clipping at the bottom of the map with weird characters that does not occur at the top.
    if (getPlayerRow() > 76)
    {
        playerRow = 76;
    }
    

    if (getPlayerCol()-3 < 0){
        for (int i=playerRow-3; i<=playerRow+3; i++){
            for (int j=0; j<=6; j++){
                if (player_position_[0] == i && player_position_[1] == j)
                {
                    cout << setw(2) << left << PARTY;
                }
                else{
                    cout << setw(2) << left << map_data_[i][j];
                }
            }
            cout << endl;
        }
    }
    else if (getPlayerCol()+3 > 24){
        for (int i=playerRow-3; i<=playerRow+3; i++){
            for (int j=18; j<=24; j++){
                if (player_position_[0] == i && player_position_[1] == j)
                {
                    cout << setw(2) << left << PARTY;
                }
                else{
                    cout << setw(2) << left << map_data_[i][j];
                }
            }
            cout << endl;
        }
    }
    else{
        for (int i=playerRow-3; i<=playerRow+3; i++){
            for (int j=getPlayerCol()-3; j<=getPlayerCol()+3; j++){
                if (player_position_[0] == i && player_position_[1] == j)
                {
                    cout << setw(2) << left << PARTY;
                }
                else{
                    cout << setw(2) << left << map_data_[i][j];
                }
            }
            cout << endl;
        }
    }

}

// returns the material at a certain spot in the map
Material Map::getMaterialAt(int row, int col){
    return map_data_mats[row][col];
}
// sets the material at a certain spot in the map. Useful for replacing mined materials with air.
void Map::setMaterialAt(int row, int col, Material mat){
    map_data_mats[row][col] = mat;
}


