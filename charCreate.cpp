#include "charCreate.h"

charCreate::charCreate(string &inputName, string &inputClass)
{
    selectName(inputName);
    selectClass(inputClass);
}

void charCreate::selectName(string &inputName)
{
	NAME:
	string input;
	cout << "Write your name: ";
    input = formatInput();
    if (input == "Q")
    	quit();
    else
    {
    	inputName = input;
    	CONFIRM_NAME:
    	cout << "You have chosen the name: " << inputName<< endl;
	    cout << "Are you sure you want this to be your name?" << endl;
	    cout << "Keep in mind that name is permanent." << endl;
	    cout << "If you are sure about this name, press [Y]." << endl;
	    cout << "If you would like to reselect name, press [N]" << endl;
	    input = formatInput();
	    if (input == "Q")
	    	quit();
	    else if (input == "Y")
        {

        }
        else if (input == "N")
        {
        	cout << endl;
        	goto NAME;
        }
        else
        {
            cout << "Invalid input. Please try again." << endl;
            cout << endl;
            goto CONFIRM_NAME;
        }
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
    if (input == "Q")
    	quit();
    else if (input == "1" || input == "2" || input == "3")
    {
	    inputClass = input;
	    CONFIRM_CLASS:
	    cout << "You have chosen class " << inputClass << endl;
	    cout << "Are you sure you want to be in this class?" << endl;
	    cout << "Keep in mind that class choice is permanent." << endl;
	    cout << "If you are sure about this class, press [Y]." << endl;
	    cout << "If you would like to reselect class, press [N]" << endl;
	    input = formatInput();
	    if (input == "Q") {
            quit();
        }
        else if (input == "Y")
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
            goto CONFIRM_CLASS;
        }
    }
    else
    {
        cout << endl;
    	cout << "Invalid choice. Please try again.";
    	cout << endl;
    	goto CLASS;
    }
}

//void charCreate::showStatus(Player player){
//   cout << "You are " << player.getName() << endl;
//   cout << "Your Maximum and current HP is " << player.getMaxHP() << endl;
//   cout << "Your have chosen class " << player.getClass() << endl;
//}

void charCreate::rechoice(Player &player)
{
    TOP:
    string input;
    cout << "If you are not happy with any of the choices, this is the last chance!" << endl;
    cout << "Press [N] to reselect name" << endl;
    cout << "Press [C] to reselect class" << endl;
    cout << "Press [Y] to continue." << endl;
    input = formatInput();
    if (input == "Q")
    {
        quit();
    }
    if (input == "N")
        {
            reselectName(player);
            goto TOP;
        }
    if (input == "C")
        {
            reselectClass(player);
            goto TOP;
        }
    if (input == "Y")
    {
        return;
    }
}

void charCreate::reselectName(Player &player)
{
    string input;
    selectName(input);
    player.setName(input);
}

void charCreate::reselectClass(Player &player)
{
    string input;
    selectClass(input);
    player.setClass(input);
}
