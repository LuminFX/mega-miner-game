// Game_MegaMiner.cpp

// CSCI 1300 Fall 2022
// Author: Tyler Schmitz
// Recitation: 306 – Zachary Atkins
// Project 3

#include <iostream>
#include "Map.h"
#include "Material.h"
#include "MatManager.h"
#include "Miner.h"
#include "Upgrade.h"
#include "UpgradeManager.h"
#include "MegaMiner.h"

using namespace std;

/*
validIntInput checks if the input string is an integer between the low and high bounds.
1. first check if everything in the string is an integer, if not return false
2. convert string to integer
3. check if integer is within range
4. return result
*/
bool validIntInput(string input, int low, int high){
    
    bool digit = false;

    for (int i=0; i<input.length(); i++){
        if (!isdigit(input[i])){
            return false;
        }
    }

    int inputInt = stoi(input);

    if (inputInt <= high && inputInt >= low){
        return true;
    }
    return false;
}

/*
isValidMovement checks if an input is a valid w a s d input.
1. check if string length is greater than one, if it is return x
2. check if the first character of string is w a s or d, if not return x
3. return the input as a character
*/
char isValidMovement(string input){
    if (input.length() > 1){
        return 'x';
    }
    if (input[0] != 'w' && input[0] != 'a' && input[0] != 's' && input[0] != 'd'){
        return 'x';
    }
    return input[0];
}

/*
isValidYN checks if the input is a valid 'y' or 'n' response
1. check if the string length is greater than 1, if so return x
2. checks if the first character of the string is y or n, if not return x
3. return the input as a character.
*/
char isValidYN(string input){
    if (input.length() > 1){
        return 'x';
    }
    if (input[0] != 'y' && input[0] != 'n'){
        return 'x';
    }
    return input[0];
}

/*
This is the main function that runs the megaminer game. Almost all user input is managed here, and the interface then interacts with the back-end from the MegaMiner class.
The basic idea is that this is a bunch of nested menues, which each correspond to the menu options presented.
*/
int main(){

    srand(time(0));

    string materialData = "materials.txt";
    string upgradeData = "upgrades.txt";

    system("clear"); // clears the console so the player has a clean experience in the terminal.
    bool playing = true; // declaring all values for managing input
    string input;
    int returnVal;
    string dummy;
    int upgradeIdentifier = 0;
    int gambleSelector = 0;
    bool gambleValidation = false;

    MegaMiner game = MegaMiner(); // instance of back-end game object
    returnVal = game.loadData(upgradeData, materialData); // loads material and upgrade data from upgrades.txt and materials.txt

    if (returnVal == -1){ // if the data did not load properly print an appropriate failure message
        cout << "There was an issue opening essential game data. Please verify files and try again." << endl;
        return 0;
    }
    else if (returnVal == -2){
        cout << "There was an issue reading essential game data. Please verify contents and try again." << endl;
        return 0;
    }

    system("clear"); 
    cout << "Welcome to MegaMiner!" << endl << endl << "The goal of this game is to mine through the bottom of the map." << endl <<  // first menu that explains game and prompts for name
    "You won't be able to do this right off the bat, so sell materials and upgrade your ship to prepare!" << endl 
    << "Upgrade your drill to dig through more, your chassis to have more health and take less damage," << endl << "your tank to store more fuel, your storage to hold more ore, and your cooling system to dig deeper without taking damage. "
    << endl << endl << "Please enter your name: " << endl;

    fflush(stdin);
    getline(cin, input);

    game.setName(input);
    game.generateMap(); // randomly generates the ores underground for game

    // DEV TESTING SECTION- COMMENT OUT FOR DEFAULT GAME

    // game.upgrade(1,4);
    // game.upgrade(2,4);
    // game.upgrade(3,4);
    // game.upgrade(4,4);
    // game.upgrade(5,4);
    // game.setMoney(3000000);

    // END DEV SECTION


    system("clear");

    do // main do while loop for prompting user for actions
    {
        cout << "Player: " << game.getName() << endl;
        cout << "Health: " << game.getHealth() << "/" << game.getUpgradeManager().getChassis(game.getMiner().getChassisLevel()).getAttribute() << endl;
        cout << "Fuel: " << game.getFuel() << "/" << game.getUpgradeManager().getTank(game.getMiner().getTankLevel()).getAttribute() << " L" << endl;
        cout << "Storage: " << game.getUnitsStored() << "/" << game.getUpgradeManager().getStorageModule(game.getMiner().getStorageLevel()).getAttribute() << " U" << endl;
        cout << "Money: $" << game.getMoney() << endl << endl;

        // print map around player
        game.viewArea();
        // print stats below map
        cout << endl << "Would you like to: " << endl << "1. Move" << endl << "2. Open map" << endl << "3. View Storage" << endl << "4. Refuel/Repair" << endl << 
        "5. Open Market" << endl << "6. Gamble" << endl << "7. View stats" << endl << "8. Quit" << endl;
        cin >> input;

        if (!validIntInput(input, 1,8)){ // input validation
            system("clear");
            cout << "Please enter a valid input." << endl;
        }
        else{
            switch (stoi(input))
            {
            case 1: // MOVE LOGIC

                returnVal = 0;
                do
                {                    
                    system("clear");
                    
                    if (returnVal == -1){
                        cout << "You need a better drill to mine this." << endl << endl;
                    }

                    cout << "Health: " << game.getHealth() << "/" << game.getUpgradeManager().getChassis(game.getMiner().getChassisLevel()).getAttribute() << endl; // prints HUD
                    cout << "Fuel: " << game.getFuel() << "/" << game.getUpgradeManager().getTank(game.getMiner().getTankLevel()).getAttribute() << " L" << endl;
                    cout << "Storage: " << game.getUnitsStored() << "/" << game.getUpgradeManager().getStorageModule(game.getMiner().getStorageLevel()).getAttribute() << " U" << endl;

                    cout << "Use wasd to control movement. Type anything else to stop moving." << endl << endl;
                    game.viewArea();
                    cout << endl << "Depth: " << game.getDepth() << endl;

                    cin >> input; // input for movement

                    if(isValidMovement(input) != 'x' && game.getFuel() > 0 && game.getHealth() > 0 && game.getDepth() < 79){ // ends move loop when invalid input or any game ending conditions are met
    
                        returnVal = game.move(isValidMovement(input));

                    }

                    if(game.getFuel() < 0.05 || game.getFuel() > game.getUpgradeManager().getTank(game.getMiner().getTankLevel()).getAttribute()){ // hotfix for a fuel bug I can't find
                        game.setFuel(0);
                    }

                } while (isValidMovement(input) != 'x' && game.getFuel() > 0 && game.getHealth() > 0 && game.getDepth() < 79);
                system("clear");

                break;
            case 2: // SHOW FULL MAP LOGIC
                system("clear");
                cout << "Current map: " << endl;
                game.viewMap();
                cout << endl << "Type anything to continue" << endl;
                fflush(stdin); // flushes instream so getline works properly, any input continues
                getline(cin, dummy);
                system("clear");
                break;
            case 3: // SHOW STORAGE LOGIC, WITH OPTIONS FOR SELLING INVENTORY
                system("clear");
                game.viewStorage();

                cout << endl << "Would you like to sell your storage?(y/n)" << endl;
                
                do
                {
                    cin >> input;
                    if (isValidYN(input) == 'x'){
                        cout << "Invalid input" << endl;
                    }

                } while (isValidYN(input) == 'x');  

                if(isValidYN(input) == 'y'){

                    returnVal = game.sellInventory();
                    if(returnVal == -1){
                        system("clear");
                        cout << "You must be on the surface to sell your items." << endl << endl;
                    }
                    else{
                        system("clear");
                    }
                }

                break;
            case 4: // REPAIR/REFUEL LOGIC

                if(game.getDepth() == 0){ // only works if on surface

                    system("clear");

                    game.printFuelRepairCost();

                    cout << "Repair?(y/n)" << endl;

                    do
                    {
                        cin >> input;
                        if (isValidYN(input) == 'x'){
                            cout << "Invalid input" << endl;
                        }
                    } while (isValidYN(input) == 'x');  

                    if(isValidYN(input) == 'y'){

                        returnVal = game.refuelRepair();

                        if (returnVal == -1){
                            system("clear");
                            cout << "You cant afford this!" << endl;
                        }
                        else{
                            system("clear");
                        }
                        
                    }
                    else{
                        system("clear");
                    }

                }
                else{
                    system("clear");
                    cout << "You must be on the surface to do this!" << endl;
                }
                
                break;
            case 5: // UPGRADE SHOP LOGIC
                if(game.getDepth() != 0){ // shop only works if on surface
                    system("clear");
                    cout << "You must be on the surface to shop!" << endl;
                }
                else{

                    do // prints stats and prompts user for which part they want to upgrade
                    {
                        upgradeIdentifier = 0;
                        system("clear");
                        cout << "Your current miner has the following parts:" << endl;
                        cout << endl << "1. Drill: " << game.getUpgradeManager().getDrill(game.getMiner().getDrillLevel()).getName() << endl;
                        cout << "2. Chassis: " << game.getUpgradeManager().getChassis(game.getMiner().getChassisLevel()).getName() << endl;
                        cout << "3. Cooler: " << game.getUpgradeManager().getCooler(game.getMiner().getCoolingLevel()).getName() << endl;
                        cout << "4. Tank: " << game.getUpgradeManager().getTank(game.getMiner().getTankLevel()).getName() << endl;
                        cout << "5. Storage: " << game.getUpgradeManager().getStorageModule(game.getMiner().getStorageLevel()).getName() << endl;

                        cout << endl << "Type the number of the item you would like to upgrade, or 6 to exit." << endl;
                        cin >> input;

                        if (!validIntInput(input,1,6))
                        {
                            system("clear");
                            cout << endl << "Please enter a valid input" << endl;   
                        }

                    } while (!validIntInput(input, 1,6));

                    system("clear");
                    cout << "Your balance is: $" << game.getMoney() << endl << endl;

                    switch (stoi(input)) // switch that prints upgrades depending on what user chose
                    {
                    case 1:
                        upgradeIdentifier = 1;
                        cout << "You currently have: " << game.getUpgradeManager().getDrill(game.getMiner().getDrillLevel()).getName() << " drill" << endl;
                        cout << "The available upgrades are:" << endl << endl;  
                        for (int i=game.getMiner().getDrillLevel()+1; i<5; i++){
                            cout << game.getUpgradeManager().getDrill(i).getName() << " drill - $" << game.getUpgradeManager().getDrill(i).getPrice() << endl;
                        }
                        break;
                    case 2:
                        upgradeIdentifier =2;
                        cout << "You currently have: " << game.getUpgradeManager().getChassis(game.getMiner().getChassisLevel()).getName() << " chassis" << endl;
                        cout << "The available upgrades are:" << endl << endl;  
                        for (int i=game.getMiner().getChassisLevel()+1; i<5; i++){
                            cout << game.getUpgradeManager().getChassis(i).getName() << " chassis - $" << game.getUpgradeManager().getChassis(i).getPrice() << endl;
                        }
                        break;
                    case 3:
                        upgradeIdentifier = 3;
                        cout << "You currently have: " << game.getUpgradeManager().getCooler(game.getMiner().getCoolingLevel()).getName() << endl;
                        cout << "The available upgrades are:" << endl << endl;  
                        for (int i=game.getMiner().getCoolingLevel()+1; i<5; i++){
                            cout << game.getUpgradeManager().getCooler(i).getName() << " - $" << game.getUpgradeManager().getCooler(i).getPrice() << endl;
                        }
                        break;
                    case 4:
                        upgradeIdentifier = 4;
                        cout << "You currently have: " << game.getUpgradeManager().getTank(game.getMiner().getTankLevel()).getName() << " tank" << endl;
                        cout << "The available upgrades are:" << endl << endl;  
                        for (int i=game.getMiner().getTankLevel()+1; i<5; i++){
                            cout << game.getUpgradeManager().getTank(i).getName() << " tank - $" << game.getUpgradeManager().getTank(i).getPrice() << endl;
                        }
                        break;
                    case 5:
                        upgradeIdentifier = 5;
                        cout << "You currently have: " << game.getUpgradeManager().getStorageModule(game.getMiner().getStorageLevel()).getName() << " storage" << endl;
                        cout << "The available upgrades are:" << endl << endl;  
                        for (int i=game.getMiner().getStorageLevel()+1; i<5; i++){
                            cout << game.getUpgradeManager().getStorageModule(i).getName() << " storage - $" << game.getUpgradeManager().getStorageModule(i).getPrice() << endl;
                        }
                        break;
                    default:
                        break;
                    }

                        if(upgradeIdentifier != 0){

                        cout << endl << "Upgrade to next level? (y/n)" << endl;

                        do
                        {
                            cin >> input;
                            if (isValidYN(input) == 'x'){
                                cout << "Invalid input" << endl;
                            }
                        } while (isValidYN(input) == 'x');
                    
                        if (isValidYN(input) == 'y'){

                            switch (upgradeIdentifier) // handles all upgrading if user chose to
                            {
                            case 1:
                                
                                if(game.getMiner().getDrillLevel() == 4) // if level is maxxed there can't be an upgrade
                                {
                                    system("clear");
                                    cout << "There are no further upgrades." << endl;
                                }
                                else if(game.getMoney() < game.getUpgradeManager().getDrill(game.getMiner().getDrillLevel()+1).getPrice()){
                                    system("clear");
                                    cout << "You can't afford that." << endl;
                                }
                                else{// upgrade logic
                                    game.setMoney(game.getMoney() - game.getUpgradeManager().getDrill(game.getMiner().getDrillLevel() + 1).getPrice());
                                    game.upgrade(upgradeIdentifier, game.getMiner().getDrillLevel() + 1);
                                    system("clear");
                                    cout << "Your drill has been upgraded!" << endl;
                                }
                                break;
                            case 2:
                                
                                if (game.getMiner().getChassisLevel() == 4)// if level is maxxed there can't be an upgrade
                                {
                                    system("clear");
                                    cout << "There are no further upgrades." << endl;
                                }
                                else if(game.getMoney() < game.getUpgradeManager().getChassis(game.getMiner().getChassisLevel()+1).getPrice()){
                                    system("clear");
                                    cout << "You can't afford that." << endl;
                                }
                                else{// upgrade logic
                                    game.setMoney(game.getMoney() - game.getUpgradeManager().getChassis(game.getMiner().getChassisLevel() + 1).getPrice());
                                    game.upgrade(upgradeIdentifier, game.getMiner().getChassisLevel() + 1);
                                    system("clear");
                                    cout << "Your chassis has been upgraded!" << endl;
                                }
                                break;
                            case 3:
                                
                                if (game.getMiner().getCoolingLevel() == 4)// if level is maxxed there can't be an upgrade
                                {
                                    system("clear");
                                    cout << "There are no further upgrades." << endl;
                                }
                                else if(game.getMoney() < game.getUpgradeManager().getCooler(game.getMiner().getCoolingLevel()+1).getPrice()){
                                    system("clear");
                                    cout << "You can't afford that." << endl;
                                }
                                else{// upgrade logic
                                    game.setMoney(game.getMoney() - game.getUpgradeManager().getCooler(game.getMiner().getCoolingLevel() + 1).getPrice());
                                    game.upgrade(upgradeIdentifier, game.getMiner().getCoolingLevel() + 1);
                                    system("clear");
                                    cout << "Your Cooling has been upgraded!" << endl;
                                }
                                break;
                            case 4:
                                
                                if (game.getMiner().getTankLevel() == 4)// if level is maxxed there can't be an upgrade
                                {
                                    system("clear");
                                    cout << "There are no further upgrades." << endl;
                                }
                                else if(game.getMoney() < game.getUpgradeManager().getTank(game.getMiner().getTankLevel()+1).getPrice()){
                                    system("clear");
                                    cout << "You can't afford that." << endl;
                                }
                                else{// upgrade logic
                                    game.setMoney(game.getMoney() - game.getUpgradeManager().getTank(game.getMiner().getTankLevel() + 1).getPrice());
                                    game.upgrade(upgradeIdentifier, game.getMiner().getTankLevel() + 1);
                                    system("clear");
                                    cout << "Your Tank has been upgraded!" << endl;
                                }
                                break;
                            case 5:
                                
                                if (game.getMiner().getStorageLevel() == 4)// if level is maxxed there can't be an upgrade
                                {
                                    system("clear");
                                    cout << "There are no further upgrades." << endl;
                                }
                                else if(game.getMoney() < game.getUpgradeManager().getStorageModule(game.getMiner().getStorageLevel()+1).getPrice()){
                                    system("clear");
                                    cout << "You can't afford that." << endl;
                                }
                                else{ // upgrade logic
                                    game.setMoney(game.getMoney() - game.getUpgradeManager().getStorageModule(game.getMiner().getStorageLevel() + 1).getPrice());
                                    game.upgrade(upgradeIdentifier, game.getMiner().getStorageLevel() + 1);
                                    system("clear");
                                    cout << "Your Storage has been upgraded!" << endl;
                                }
                                break;
                            
                            default:
                                break;
                            }

                        }
                        else{
                            system("clear");
                        }
                    }

                }

                break;
            case 6: // GAMBLE LOGIC

                if (game.getDepth() == 0){
                    
                    system("clear");

                    gambleValidation = true; // to keep track of input validation and selected options
                    gambleSelector = 0;

                    cout << "Welcome to Spin2Win!" << endl;
                    cout << "Your current balance is: $" << game.getMoney() << endl << endl;

                    cout << "What number multiplier would you like to put your money on? Or press 6 to quit." << endl;
                    cout << "1. 1 - 50%" << endl;
                    cout << "2. 3 - 20%" << endl;
                    cout << "3. 5 - 15%" << endl;
                    cout << "4. 10 - 10%" << endl;
                    cout << "5. 20 - 5%" << endl;

                    do
                    {

                        cin >> input;
                        if (!validIntInput(input,1,5)){
                            cout << "Invalid input." << endl;
                        }

                    } while (!validIntInput(input,1,6));

                    gambleSelector = stoi(input); // set chosen value for later

                    if (gambleSelector != 6){ // if quit is chosen dont run

                        cout << "How much would you like to bet?" << endl;
                        cout << "Your current balance is: $" << game.getMoney() << endl;

                        do
                        {
                            cin >> input;

                            for (int i=0; i<input.length();i++){
                                if (!isdigit(input[i])){
                                    gambleValidation = false;
                                }
                            }

                        } while (!gambleValidation);

                        returnVal = game.gamble(gambleSelector, stoi(input)); // use the gamble function in game

                        switch (returnVal)
                        {
                        case -1:
                            system("clear");
                            cout << "You don't have enough money to place that bet!" << endl;
                            break;
                        case 0:
                            system("clear");
                            cout << "You did not win. $" << input << " has been subtracted from your balance." << endl;
                            break;
                        default:
                            system("clear");
                            cout << "You won. $" << returnVal << " has been added to your balance." << endl;
                            break;
                        }
                        
                    }
                    else{
                        system("clear");
                    }

                }
                else{
                    system("clear");
                }


                break;
            case 7: // show stats logic
                system("clear");
                game.viewStats();
                cout << endl << "Type anything to continue" << endl;
                fflush(stdin);
                getline(cin, dummy);
                system("clear");
                break;
            case 8: // quit logic
                playing = false;
                break;
            default:
                break;
            }
        }
    } while (playing == true && game.getHealth() > 0 && game.getFuel() > 0 && game.getDepth() < 79);
    

    if(playing == true){

        returnVal = game.quit();

        switch (returnVal)
        {
        case 0:
            cout << "Congrats! You completed Mega Miner, and your name has been added to the list of players who finished." << endl;

            cout << "These players are:" << endl;

            game.addWinner(game.getName());
            game.printWinners();

            break;
        case 1:
            cout << "GAME OVER" << endl << "You ran out of fuel! Better luck next time!" << endl;
            break;
        case 2:
            cout << "GAME OVER" << endl << "You ran out of health! Better luck next time!" << endl;
            break;
        default:
            break;
        }

        cout << endl << "Would you like to see a map and statistics from your game?(y/n)" << endl;
        do
        {
            cin >> input;
            if (isValidYN(input) == 'x'){
                cout << "Invalid input" << endl;
            }
        } while (isValidYN(input) == 'x');  

        if(isValidYN(input) == 'y'){

            game.viewMap();
            game.viewStats();
            cout << endl;

        }

    }
    
    cout << "Thank you for playing Mega Miner!" << endl;

    game.saveWinners();

    return 0;

}

// compile command: 
// g++ -std=c++17 MatManager.cpp Miner.cpp Map.cpp MegaMiner.cpp UpgradeManager.cpp Material.cpp Upgrade.cpp Game_MegaMiner.cpp