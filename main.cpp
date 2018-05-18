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

    // Cheat codes for skipping character creation
    cout << "Input any key to begin the game" << endl;
    string input = formatInput();
    if (input == "PLW")
        goto PLW;
    if (input == "PLR")
        goto PLR;
    if (input == "PLM")
        goto PLM;

    // Start Character Creation
    {
        charCreate charCreate(inputName, inputClass);
        player.setName(inputName);
        player.setClass(inputClass);
        player.showStatus();
        charCreate.rechoice(player);
        goto GAME;
    }

    // End Character Creation

    // Cheat code cases
    PLW:
        player.setName("Test");
        player.setClass("1");
        goto GAME;

    PLR:
        player.setName("Test");
        player.setClass("2");
        goto GAME;

    PLM:
        player.setName("Test");
        player.setClass("3");

    GAME:
    cout << "Awesome! Your character has been created. You are ready to begin your adventure!" << endl;
    cout << "The game has begun!" << endl;

    game newGame(player);

    while(1);

    quit();
}
