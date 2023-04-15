# mega-miner-game

This is my final project for CSCI 1300: Starting Computing, which I took during my first semester of Freshman year at CU Boulder. I chose the "create your own" path for this project, and I elected to recreate [Mega Miner](https://www.silvergames.com/en/mega-miner), a browser game I played a lot when I was younger. With flash being discontinued, it is very difficult to play the original game, so I thought making my own version would be fun and nostalgic.

## Prerequisites

There are no prerequisites to download and play, but a compiler is needed to recompile. [g++](https://www.geeksforgeeks.org/compiling-with-g-plus-plus/) was used in development.

## Running the game

1. In the Mega Miner Game folder enter 
```
./MegaMinerGame
```

2. If you would like to recompile first, in the workspace folder enter 
```
g++ -std=c++17 MatManager.cpp Miner.cpp Map.cpp MegaMiner.cpp UpgradeManager.cpp Material.cpp Upgrade.cpp Game_MegaMiner.cpp -o MegaMinerGame
```
Then enter the run command.

## Playing the game

The goal of my version of Mega Miner is the successfully mine through the bottom of the map. In order to do so, you must manage your fuel, health, and component levels (drill, hull, etc.) by purchasing upgrades and covering maintenance costs at the surface. Money is made by mining materials and selling them (or gambling).
If you run out of fuel, the game is over, so be careful!

## Additional information

A more in depth explanation and demo of this project can be found [here](https://www.youtube.com/watch?v=QYFAikeYlk4)
