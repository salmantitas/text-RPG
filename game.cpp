#include "game.h"

using namespace std;

vector<string> emptyVtr;

game::game(Player &player)
{
    thyself = &player;
    runGame();
}

// Creates the choices and initiates the game
void game::runGame()
{
    createStory();

	string input;
	TOP:
    printLine("Press button to continue");
    input = formatInput();

    quitCheck(input);

    if (input == "S")
    {
        thyself->showStatus();
        goto TOP;
    }

    else playChoices();

    quit();
}

void game::createStory() {
    int plc = stoi(thyself->getClass(), nullptr, 10); // Gets integer

    Story story;

    switch(plc)
    {
    case 1:
        choiceTree = story.warriorStoryline();
        break;
    case 2:
        choiceTree = story.rogueStoryline();
        break;
    case 3:
        choiceTree = story.mageStoryline();
        break;
    }
    current = &choiceTree;
}

// The inner loop which runs the game
void game::playChoices()
{
    while (!gameOver)
    {
    	// If the choice is a relay, apply the associated consequences and then move onto the next choice
        if (current->getRelay())
            {
                current->readChoice();
                playConsequences();
                setCurrent(current->choiceAt(0));
            }
        // If the choices has any conditional consequences, play them first.
        else
            {
                playCondConsequences();

                // check again for relay, in case the conditional consequences change the current pointer to another relay choice.
                if (current->getRelay())
	            {
	                current->readChoice();
	                playConsequences();
	                setCurrent(current->choiceAt(0));
	            }

	            // if there are no relays and no conditional choices, read the choice, apply consequences and receive input from
	            // the user
	            else
	            {

                current->readChoice();
                playConsequences();
                goto NEXT;

                // read the choice again if the input is invalid
                TOP:
                    current->readChoice();
                NEXT:
                    string input;
                    input = formatInput();
                    if (input == "S")
                    {
                        thyself->showStatus();
                        goto TOP;
                    }

                int intIn;

                // If input is not a number, try again.
                try {
                    intIn = getIntFromString(input);
                }
                catch (std::invalid_argument iaex)
                {
                    invalidInput();
                    cout << endl;
                    goto TOP;
                }

                // If input number is less than 0 or greater than number of available choices, try again
                if (intIn == 0 || intIn > current->numberOfChoices())
                {
                    invalidInput();
                    cout << endl;
                    goto TOP;
                }

                // else, in which case the input is valid, change the pointer.
                else
                {
                    setCurrent(current->choiceAt(intIn - 1));
                    cout << endl;
                }
            }
        }
            gameOver = (current->numberOfChoices() == 0);
    }

    current->readChoice();
    quit();
}

/***********
 * Helpers *
 ***********/

// Apply consequences from the choices
void game::playConsequences()
{
	// if there are consequences to apply
    if (current->numberOfCons() != 0)
    {
        vector<int> temp = current->getCons();
        for (int i: temp)
        {
            switch (i)
            {
            case STR_BOOST:
                STRBoost();
                break;
            case STR_DROP:
                STRDrop();
                break;
            case DEF_BOOST:
                DEFBoost();
                break;
            case DEF_DROP:
                DEFDrop();
                break;
            case AGL_BOOST:
                AGLBoost();
                break;
            case AGL_DROP:
                AGLDrop();
                break;
            case DEX_BOOST:
                DEXBoost();
                break;
            case DEX_DROP:
                DEXDrop();
                break;
            case INT_BOOST:
                INTBoost();
                break;
            case INT_DROP:
                INTDrop();
                break;
            case WIS_BOOST:
                WISBoost();
                break;
            case WIS_DROP:
                WISDrop();
                break;
            case KARMA_BOOST:
                karmaBoost();
                break;
            case KARMA_DROP:
                karmaDrop();
                break;
            }
        }
    }
}

// if conditional consequences apply, change the current pointer to the appropriate choice
void game::playCondConsequences()
{
    if (current->numberOfCondCons() != 0)
    {
        auto temp = current->getCondCons();
        for (tuple<int, double, int> i : temp) // tuple<int enum, double requiredStat, int indexOfConditionalChoice>
        {
        	// conditionSatisfied is set to true if any of the conditions for conditional consequences are satisfied.
            bool conditionSatisfied = false;
            double num = get<1>(i);
            switch(get<0>(i))
            {
            case STR_DROP:
                condConsHelper(thyself->getSTR(), num, -1, "strength", conditionSatisfied);
                goto CONSEQUENCE;
            case STR_BOOST:
                condConsHelper(thyself->getSTR(), num, 1, "strength", conditionSatisfied);
                goto CONSEQUENCE;
            case DEF_DROP:
                condConsHelper(thyself->getDEF(), num, -1, "defense", conditionSatisfied);
                goto CONSEQUENCE;
            case DEF_BOOST:
                condConsHelper(thyself->getDEF(), num, 1, "defense", conditionSatisfied);
                goto CONSEQUENCE;
            case AGL_DROP:
                condConsHelper(thyself->getAGL(), num, -1, "agility", conditionSatisfied);
                goto CONSEQUENCE;
            case AGL_BOOST:
                condConsHelper(thyself->getAGL(), num, 1, "agility", conditionSatisfied);
                goto CONSEQUENCE;
            case DEX_DROP:
                condConsHelper(thyself->getDEX(), num, -1, "dexterity", conditionSatisfied);
                goto CONSEQUENCE;
            case DEX_BOOST:
                condConsHelper(thyself->getDEX(), num, 1, "dexterity", conditionSatisfied);
                goto CONSEQUENCE;
            case INT_DROP:
                condConsHelper(thyself->getINT(), num, -1, "intelligence", conditionSatisfied);
                goto CONSEQUENCE;
            case INT_BOOST:
                condConsHelper(thyself->getINT(), num, 1, "intelligence", conditionSatisfied);
                goto CONSEQUENCE;
            case WIS_DROP:
                condConsHelper(thyself->getWIS(), num, -1, "wisdom", conditionSatisfied);
                goto CONSEQUENCE;
            case WIS_BOOST:
                condConsHelper(thyself->getWIS(), num, 1, "wisdom", conditionSatisfied);
                goto CONSEQUENCE;
            case KARMA_DROP:
                condConsHelper(thyself->getKarma(), num, -1, "karma", conditionSatisfied);
                goto CONSEQUENCE;
            case KARMA_BOOST:
                condConsHelper(thyself->getKarma(), num, 1, "karma", conditionSatisfied);

            CONSEQUENCE:
            	// if the condition has been satisfied, the pointer will be changed.
                if (conditionSatisfied)
                {
                    setCurrent(current->choiceAtCond(get<2>(i)));
                }
            }
        }
    }
}

void game::condConsHelper(double att, double check, int cond, string txt, bool &jump)
{
	// if cond is negative, checks whether the attribute is less than the required.
    if (cond < 0)
    {
        if (att < check)
        {
            cout << "Your " << txt << " was too low." << endl;
            // sets this to true so that playCondConsequences knows whether the condition has been satisfied
            jump = true;
        }
    }
    // else checks whether the attribute is more than the required.
    else
    {
        if (att >= check)
        {
            cout << "Your " << txt << " was enough." << endl;
            jump = true;
        }
    }
}

void game::setCurrent(Choice &choice)
{
    current = &choice;
}

void game::setCurrent(Choice* choice)
{
    current = choice;
}

// Consequences

// HP -- as of now, there has been no use of the HP attribute. Might delete this if I cannot figure out a way to implement this ingame.
void game::HPBoost(int num)
{
    int newHP = min(thyself->getHP()+num, thyself->getMaxHP());
    thyself->setHP(newHP);
}

void game::HPDrop(int num)
{
    int newHP = max(thyself->getHP()-num, 0);
    thyself->setHP(newHP);
}

// calculates the change to the player's stat and returns the updated number
double consHelper(double fna, int num, string str)
{
    double curr = fna*10 + num; // multiplies attribute with 10 so that 1 can be added or subtracted.
    int newNum;
    string other;
    if (num > 0)
    {
        newNum = min((int) curr, 10); // prevents the stat from going above 10
        other = " increased ";
    }
    else
    {
        newNum = max((int) curr, 1); // prevents the stat from going below 1
        other = " decreased ";
    }
    double finNum = ((double) newNum)/10; // brings it down to a decimal
    cout << str << other << "to: " << finNum << endl; // reconstructs the text
    return finNum;
}

// Behaves in the same manner as consHelper
int karmaHelper(int fna, int num, string str)
{
    int curr = fna + num;
    int newNum;
    string other;
    if (num > 0)
    {
        newNum = min((int) curr, 100);
        other = " increased ";
    }
    else
    {
        newNum = max((int) curr, 0);
        other = " decreased ";
    }
    //double finNum = ((double) newNum)/10;
    cout << str << other << "to: " << newNum << endl;
    return newNum;
}

// STR
void game::STRBoost()
{
    thyself->setSTR(consHelper(thyself->getSTR(), 1, "Strength"));
}

void game::STRDrop()
{
    thyself->setSTR(consHelper(thyself->getSTR(), -1, "Strength"));
}

// DEF
void game::DEFBoost()
{
    thyself->setDEF(consHelper(thyself->getDEF(), 1, "Defense"));
}

void game::DEFDrop()
{
    thyself->setDEF(consHelper(thyself->getDEF(), -1, "Defense"));
}

// AGL
void game::AGLBoost()
{
    thyself->setAGL(consHelper(thyself->getAGL(), 1, "Agility"));
}

void game::AGLDrop()
{
    thyself->setAGL(consHelper(thyself->getAGL(), -1, "Agility"));
}

// DEX
void game::DEXBoost()
{
    thyself->setDEX(consHelper(thyself->getDEX(), 1, "Dexterity"));
}

void game::DEXDrop()
{
    thyself->setAGL(consHelper(thyself->getAGL(), -1, "Dexterity"));
}

// INT
void game::INTBoost()
{
    thyself->setINT(consHelper(thyself->getINT(), 1, "Intelligence"));
}

void game::INTDrop()
{
    thyself->setINT(consHelper(thyself->getINT(), -1, "Intelligence"));
}

// WIS
void game::WISBoost()
{
    thyself->setWIS(consHelper(thyself->getWIS(), 1, "Wisdom"));
}

void game::WISDrop()
{
    thyself->setWIS(consHelper(thyself->getWIS(), -1, "Wisdom"));
}

void game::karmaBoost()
{
    thyself->setKarma(karmaHelper(thyself->getKarma(), 10, "Karma"));
}

void game::karmaDrop()
{
    thyself->setKarma(karmaHelper(thyself->getKarma(), -10, "Karma"));
}

void game::createStatFunctions()
{
    statFunctions.push_back(STRBoost);
    statFunctions.push_back(STRDrop);
    statFunctions.push_back(DEFBoost);
    statFunctions.push_back(DEFDrop);
    statFunctions.push_back(AGLBoost);
    statFunctions.push_back(AGLDrop);
    statFunctions.push_back(DEXBoost);
    statFunctions.push_back(DEXDrop);
    statFunctions.push_back(INTBoost);
    statFunctions.push_back(INTDrop);
    statFunctions.push_back(WISBoost);
    statFunctions.push_back(WISDrop);
    statFunctions.push_back(karmaBoost);
    statFunctions.push_back(karmaDrop);
}
