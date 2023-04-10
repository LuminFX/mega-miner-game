// MegaMiner.cpp

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#include "MegaMiner.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Map.h"

using namespace std;

double randomDouble1(){ // randomDouble returns a random double between 0 and 1.
    return double(rand()) / (double(RAND_MAX) + 1.0);
}

MegaMiner::MegaMiner(){ // defualt constructor
    name = "";
    health = 100;
    money = 0;
    fuel = 5;
    miner = Miner();
    matManager = MatManager();
    upgradeManager = UpgradeManager();
    unitsStored = 0;
}
MegaMiner::MegaMiner(string nameIn, int healthIn, int moneyIn, int fuelIn, Miner minerIn, MatManager matManagerIn, UpgradeManager upgradeManagerIn){ // paramatrized constructor
    name = nameIn;
    health = healthIn;
    money = moneyIn;
    fuel = fuelIn;
    miner = minerIn;
    matManager = matManagerIn;
    upgradeManager = upgradeManagerIn;
}

/*
manages movement of the player.

1. switch statement for direction of movement
    2. set the matMined Material to the material that is about to be mined
3. if the material is null return -2
4. if the mining level of the drill is higher than the mining level of the material
    5. call the map move function
    6. set the now mined material on the map to air
    7. if the material "mined" is air, decrement fuel by 0.05
    8. if the material mined is anything else, decrement fuel by 0.1
    9. if fuel is somehow out of the possible range, set it to zero (this catches some errors)
    10. if the chassis level is too low to handle mined stone, decrement health
    11. if the chassis level is too low to handle mined boulders, decrement health
    12. if the size of the mined material is less than the space left in the storage of the miner, add the material to storage and upgrade unitsStored
13. switch for cooling level of miner
    14. if the cooling level isnt sufficient for the level in the ground where player is, decrement health.
*/

int MegaMiner::move(char input){ 

    double moveRand = randomDouble1(); // used to cause random damage

    Material matMined = Material();
    bool spotAvailable = false;
    
    switch (input) // get correct material to be mined based on direction
    {
    case 'w':
        if (map.isOnMap(map.getPlayerRow()-1, map.getPlayerCol())){
            matMined = map.getMaterialAt(map.getPlayerRow()-1, map.getPlayerCol());
        }
        break;
    case 'a':
        if (map.isOnMap(map.getPlayerRow(), map.getPlayerCol()-1)){
            matMined = map.getMaterialAt(map.getPlayerRow(), map.getPlayerCol()-1);
        }
        break;
    case 's':
        if (map.isOnMap(map.getPlayerRow()+1, map.getPlayerCol())){
            matMined = map.getMaterialAt(map.getPlayerRow()+1, map.getPlayerCol());
        }
        break;
    case 'd':
        if (map.isOnMap(map.getPlayerRow(), map.getPlayerCol()+1)){
            matMined = map.getMaterialAt(map.getPlayerRow(), map.getPlayerCol()+1);
        }
        break;
    default:
        break;
    }

    if (matMined.getName() == ""){ // return -2 if material is null
        return -2;
    }

    if (miner.getDrillLevel() >= matMined.getMiningLevel()){ // only allow mining if you have the proper mining level for it.       

        map.move(input);
        map.setMaterialAt(map.getPlayerRow(), map.getPlayerCol(), matManager.getMatList().at(0)); // set mined material to air

        if (matMined.getName() == "Air" && fuel >= 0.05){ // decrease fuel depending on action
            fuel -= 0.05;
        }
        else if (fuel > 0.1){
            fuel -= 0.1;
        }
        else{
            fuel = 0;
        }

        if(matMined.getName() == "Stone" && miner.getChassisLevel() < 2){ // do damage based on chassis level and material mined
            health -= 5;
        }
        if(matMined.getName() == "Boulder" && miner.getChassisLevel() < 4){
            health -= 10;
        }

        if(moveRand < 0.025){ // random chance of hitting something damaging in ground.
            health -= 10;
        }

        if(unitsStored + (matMined.getStorageSize()) < upgradeManager.getStorageModule(miner.getStorageLevel()).getAttribute()){ // store material if there is space
            
            matsStored.push_back(matMined);
            unitsStored += matMined.getStorageSize();

        }


    }
    else{
        return -1;
    }

    switch (miner.getCoolingLevel()) // do damage based on cooling level and depth
    {
    case 0:
        if (map.getPlayerRow() > 30){
            health -= 5;
        }
        break;
    case 1:
        if (map.getPlayerRow() > 50){
            health -= 5;
        }
        break;
    case 2:
        if (map.getPlayerRow() > 65){
            health -= 5;
        }
        break;
    case 3:
        if (map.getPlayerRow() > 70){
            health -= 5;
        }
        break;
    default:
        break;
    }

    return 0;
    

}
void MegaMiner::generateMap(){

    map.genMap(matManager.getMatList()); // generates map

}
void MegaMiner::viewMap(){ // show map and take inputs for looking at different sections of the map

    map.displayMap();

}
void MegaMiner::viewArea(){ // show immediate area around player
    map.displayArea();
}
void MegaMiner::viewStorage(){ // shows storage held in ship

    int coal = 0; // make counter variables for each material
    int iron = 0;
    int silver = 0;
    int gold = 0;
    int saphire = 0;
    int emerald = 0;
    int ruby = 0;
    int diamond = 0;
    int totalValue = 0;

    for (int i=0; i<matsStored.size();i++){ // loop through and count everything

        if (matsStored.at(i).getName() == "Coal"){
            coal++;
        }
        if (matsStored.at(i).getName() == "Iron"){
            iron++;
        }
        if (matsStored.at(i).getName() == "Silver"){
            silver++;
        }
        if (matsStored.at(i).getName() == "Gold"){
            gold++;
        }
        if (matsStored.at(i).getName() == "Saphire"){
            saphire++;
        }
        if (matsStored.at(i).getName() == "Emerald"){
            emerald++;
        }
        if (matsStored.at(i).getName() == "Ruby"){
            ruby++;
        }
        if (matsStored.at(i).getName() == "Diamond"){
            diamond++;
        }

        totalValue += matsStored.at(i).getValue(); // add values to total value count

    }

    // pint out everything that was found

    cout << "Coal: " << coal << " x $" << matManager.getMatList().at(4).getValue() << endl;
    cout << "Iron: " << iron << " x $" << matManager.getMatList().at(5).getValue() << endl;
    cout << "Silver: " << silver << " x $" << matManager.getMatList().at(6).getValue() << endl;
    cout << "Gold: " << gold << " x $" << matManager.getMatList().at(7).getValue() << endl;
    cout << "Saphire: " << saphire << " x $" << matManager.getMatList().at(8).getValue() << endl;
    cout << "Emerald: " << emerald << " x $" << matManager.getMatList().at(9).getValue() << endl;
    cout << "Ruby: " << ruby << " x $" << matManager.getMatList().at(10).getValue() << endl;
    cout << "Diamond: " << diamond << " x $" << matManager.getMatList().at(11).getValue() << endl;
    cout << endl;
    cout << unitsStored << "/" << upgradeManager.getStorageModule(miner.getStorageLevel()).getAttribute() << " Units used." << endl;
    cout << "Total stored value: $" << totalValue << endl;


}
void MegaMiner::viewStats(){ // shows money, health, score, etc
    
    cout << "Your stats are: " << endl << endl << "Name: " << name << endl << "Health: " << health << "/" << 
        upgradeManager.getChassis(miner.getChassisLevel()).getAttribute() << endl << "Storage: " << unitsStored << "/" << upgradeManager.getStorageModule(miner.getStorageLevel()).getAttribute() << " Units" << endl
        << "Fuel: " << fuel << "/" << upgradeManager.getTank(miner.getTankLevel()).getAttribute() << " Liters" << endl << "Money: $" << money << endl;
    
    cout << endl << "Drill: " << upgradeManager.getDrill(miner.getDrillLevel()).getName() << endl;
    cout << "Chassis: " << upgradeManager.getChassis(miner.getChassisLevel()).getName() << endl;
    cout << "Cooler: " << upgradeManager.getCooler(miner.getCoolingLevel()).getName() << endl;
    cout << "Tank: " << upgradeManager.getTank(miner.getTankLevel()).getName() << endl;
    cout << "Storage: " << upgradeManager.getStorageModule(miner.getStorageLevel()).getName() << endl;

}
int MegaMiner::quit(){ //manages game exit, will have options for saving or discarding current data
    
    if (map.getPlayerRow() == 79) // if player is at the win layer, return 0
    {
        return 0;
    }
    else if(fuel <= 0){ // if out of gas return -1
        return 1;
    }
    else{ // if out of health return 2
        return 2;
    }

}
int MegaMiner::loadData(string upgradeData, string materialData){ // loads upgrades and materials from files by calling functions from matManager and 

    ifstream winnersInput;

    string lineStorage; // destination for things gathered from stream

    winnersInput.open("winners.txt"); // open file
    if (!winnersInput.fail()){ // if open add winners to vector.
        
        while(!winnersInput.eof()){

            getline(winnersInput, lineStorage);
            if (!lineStorage.empty()){
                winners.push_back(lineStorage);
            }

        }
    
    }


    int matStatus;
    int upgradeStatus;

    matStatus = matManager.loadMaterials(materialData);
    upgradeStatus = upgradeManager.loadUpgrades(upgradeData);

    if (matStatus == -2 || upgradeStatus == -2){
        return -2;
    }
    if (matStatus == -1 || upgradeStatus == -1){
        return -1;
    }
    
    return 0;

}
void MegaMiner::setName(string nameIn){
    name = nameIn;
}
string MegaMiner::getName(){
    return name;
}
int MegaMiner::getHealth(){
    return health;
}
int MegaMiner::getMoney(){
    return money;
}
void MegaMiner::setMoney(int moneyIn){
    money = moneyIn;
}
double MegaMiner::getFuel(){
    return fuel;
}
void MegaMiner::setFuel(double fuelIn){
    fuel = fuelIn;
}
Miner MegaMiner::getMiner(){
    return miner;
}
MatManager MegaMiner::getMatManager(){
    return matManager;
}
UpgradeManager MegaMiner::getUpgradeManager(){    
    return upgradeManager;
}
void MegaMiner::upgrade(int identifier, int level){ // upgrades miner based on identifier flag and level

    switch (identifier)
    {
    case 1:
        miner.setDrillLevel(level);
        break;
    case 2:
        miner.setChassisLevel(level);
        break;
    case 3:
        miner.setCoolingLevel(level);
        break;
    case 4:
        miner.setTankLevel(level);
        break;
    case 5:
        miner.setStorageLevel(level);
        break;
    default:
        break;
    }

}
double MegaMiner::getUnitsStored(){
    return unitsStored;
}
void MegaMiner::setUnitsStored(double unitsIn){
    unitsStored = unitsIn;
}
int MegaMiner::sellInventory(){ // sums all inventory and sells, adding to money total

    if(map.getPlayerRow() <= 0){

        for (int i = 0; i<matsStored.size(); i++){ // total price of inventory
            money += matsStored.at(i).getValue();
        }
        matsStored.clear(); // clear storeage array
        unitsStored = 0; // reset storage amount
        return 0;
    }
    else{
        return -1;
    }


}
void MegaMiner::printFuelRepairCost(){ // prints cost to refuel and repair

    int cost = 0;

    cout << "Your miner has:" << endl << endl;
    cout << health << "/" << upgradeManager.getChassis(miner.getChassisLevel()).getAttribute() << " HP" << endl;
    cout << fuel << "/" << upgradeManager.getTank(miner.getTankLevel()).getAttribute() << " L" << endl << endl;

    cost += (upgradeManager.getChassis(miner.getChassisLevel()).getAttribute() - health)*30;
    cost += (upgradeManager.getTank(miner.getTankLevel()).getAttribute() - fuel)*20;

    cout << "Refuel/Repair cost: " << cost << endl;
}
int MegaMiner::refuelRepair(){ // refuel and repair if money is sufficient

    int cost = 0;
    cost += (upgradeManager.getChassis(miner.getChassisLevel()).getAttribute() - health)*30;
    cost += (upgradeManager.getTank(miner.getTankLevel()).getAttribute() - fuel)*20;

    if(money < cost){ // if cant afford return -1
        return -1;
    }
    
    money -= cost;
    fuel = upgradeManager.getTank(miner.getTankLevel()).getAttribute(); // fill tank
    health = upgradeManager.getChassis(miner.getChassisLevel()).getAttribute(); // repair chassis

    return 0;

}
int MegaMiner::getDepth(){
    return map.getPlayerRow();
}

/*
The gamble function lets you gamble. lol
1. create a number to store win number
2. generate a random number and subtract bet amount from money
3. if rand is within a certain range, set the winner to the corresponding number
4. if winner = bet id, then player won
    5. switch statement for which bet multiplier was chosen
        6. update money and return money added
5. return 0 for loss.
*/

int MegaMiner::gamble(int betID, int amount){

    int winner = 0;

    if (amount > money){
        return -1;
    }

    money -= amount;

    double rand = randomDouble1();

    if (rand < 0.5){
        winner = 1;
    }
    else if(rand < 0.7){
        winner = 2;
    }
    else if(rand < 0.85){
        winner = 3;
    }
    else if(rand < 0.95){
        winner = 4;
    }
    else{
        winner = 5;
    }

    if(winner == betID){
        switch (betID)
        {
        case 1:
            money += amount*2;
            return amount*2;
            break;
        case 2:
            money += amount*3;
            return amount*3;
            break;
        case 3:
            money += amount*5;
            return amount*5;
            break;
        case 4:
            money += amount*10;
            return amount*10;
            break;
        case 5:
            money += amount*20;
            return amount*20;
            break;
        default:
            break;
        }
    }
    else{
        return 0;
    }

    return -2;

}
void MegaMiner::printWinners(){
    for (int i=0; i<winners.size();i++){
        cout << winners.at(i) << endl;
    }
}
void MegaMiner::addWinner(string winner){
    
    bool alreadyWon = false;

    for(int i=0; i< winners.size();i++){ // doesnt add winner if already won
        if (winners.at(i) == winner){
            alreadyWon = true;
        }
    }
    if(!alreadyWon){
        winners.push_back(winner);
    }

}
void MegaMiner::saveWinners(){ // saves winner vector to file
    if (winners.size() > 0){

        ofstream fileWrite("winners.txt");
        
        for (int i=0; i<winners.size();i++){
            fileWrite << winners.at(i) << "\n";
        }

        fileWrite.close();

    }
}
