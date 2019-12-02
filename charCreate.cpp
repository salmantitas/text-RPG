#include "charCreate.h"

charCreate::charCreate(string &inputClass)
{
    tutorial();
    selectClass(inputClass);
}

void charCreate::tutorial()
{
	string input;

        TOP:
	printLine("For new players, the game starts with a tutorial. Press:");
	printLine("[Y] For tutorial.");
	printLine("[N] Otherwise");

    input = formatInput();
    if (input == "N") {
        return;
    } else if (input == "Y") {
            TUTORIAL:

        printLine("The game is entirely text based, and moves forward based on the choices of the player - YOU");
        printLine("Every turn, the player will be given a prompt, which explains the current situation, and choices.");
        printLine("To make a choice, simply input the corresponding number.");
        printLine();

        printLine("When you start the game, you will be given an opportunity to select a class or get one randomly.");
        printLine("Your class determines your starting stats.");
        printLine("Your stats determine the success of your choices.");
        printLine();

        printLine("You are a young person from a tiny village, with eyes full of dreams.");
        printLine("While others may be content with farming or crafting, you know you were destined for bigger things");
        printLine("So you spent your early days training in whatever manner you could.");
        printLine("You knew that one day, a chance would come.");
        printLine("A chance to prove your worth.");
        printLine();

            CONFIRM_TUTORIAL:
        printLine("Would you like to see the tutorial again? Press:");
        printLine("[Y] for yes.");
        printLine("[N] for no.");

        input = formatInput();
        if (input == "Y") {
            goto TUTORIAL;
        } else if (input == "N") {
            return;
        } else {
            invalidInput();
            printLine();
            goto CONFIRM_TUTORIAL;
        }
    } else {
        invalidInput();
        printLine();
        goto TOP;
    }
}

void charCreate::selectClass(string &inputClass) {
    string input;
    CLASS:
    cout <<"It's time to choose a class:" << endl;
    cout <<"Press [1] for Warrior" << endl;
    cout <<"Press [2] for Rogue" << endl;
    cout <<"Press [3] for Mage" << endl;
    cout <<"You chosen class is: ";
    input = formatInput();
    if (input == "1" || input == "2" || input == "3")
    {
	    inputClass = input;
	    string text;
	    if (inputClass == "1") {
	        text = "Warrior";
        } else if (inputClass == "2") {
            text = "Rogue";
        } else {
            text = "Mage";
        }
	    CONFIRM_CLASS:
	    cout << "You have chosen class: " << text << endl;
	    cout << "Are you sure you want to be in this class?" << endl;
	    cout << "Keep in mind that class choice is permanent." << endl;
	    cout << "If you are sure about this class, press [Y]." << endl;
	    cout << "If you would like to reselect class, press [N]" << endl;
	    input = formatInput();
	    if (input == "Y")
            {

            }
        else if (input == "N")
        {
            cout << endl;
            goto CLASS;
        }
        else
        {
            cout << endl;
            invalidInput();
            printLine();
            goto CONFIRM_CLASS;
        }
    }
    else
    {
        cout << endl;
    	invalidInput();
        printLine();
    	goto CLASS;
    }
}

void charCreate::reselectClass(Player &player)
{
    string input;
    selectClass(input);
    player.setClass(input);
}
