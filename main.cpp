#include <iostream>
#include "charCreate.h"
#include "player.h"
#include "utils.h"
#include "game.h"

using namespace std;

// Runs the game, initializing character creation and gameplay
int main()
{
    string inputClass;
    Player player;

    printLine("Input any key to begin the game");
    printLine("At any point, in game, you may press [Q] to quit.");

    string input = formatInput();

    // Start Character Creation

    charCreate charCreate(inputClass);
    player.setClass(inputClass);

    CLASS:

    player.showStatus();
    printLine("Would you like to stick to this class?");

    input = formatInput();
    if (input == "Y") {
        charCreate.reselectClass(player);
        goto CLASS;
    }

    // End Character Creation

    printLine("Awesome! Your character has been created. You are ready to begin your adventure!");
    printLine("The game has begun!");

    game newGame(player);

    // In case the game manages to break out of the loop without quitting
    quit();
}
