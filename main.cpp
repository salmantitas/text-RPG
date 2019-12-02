#include <iostream>
#include "charCreate.h"
#include "player.h"
#include "utils.h"
#include "game.h"

using namespace std;

// Runs the game, initializing character creation and gameplay
int main()
{
    string inputName;
    string inputClass;
    Player player;

    printLine("Input any key to begin the game");
    printLine("At any point, in game, you may press [Q] to quit.");

    string input = formatInput();

    // Start Character Creation
    {
        charCreate charCreate(inputName, inputClass);
        player.setClass(inputClass);
        player.showStatus();
        goto GAME;
    }

    // End Character Creation

    GAME:
    printLine("Awesome! Your character has been created. You are ready to begin your adventure!");
    printLine("The game has begun!");

    game newGame(player);

    while(1);

    quit();
}
