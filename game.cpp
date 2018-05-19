#include "game.h"

using namespace std;

string unfinished = "Unfinished storyline. Press [1] to end game.";
Choice fin;

game::game(Player player)
{
    thyself = &player;
    runGame();
}

void game::runGame()
{
    fin = endChoice();
    createChoices();

	string input;
	TOP:
    cout << "Press button to continue" << endl;
    input = formatInput();

    if (input == "Q")
    {
        quit();
    }

    else if (input == "S")
    {
        thyself->showStatus();
        goto TOP;
    }

    else playChoices();

    quit();
}

void game::createChoices()
{
    choiceTree = warriorStoryline();
    current = &choiceTree;
}

Choice game::warriorStoryline()
{
    vector<string> rootStr;
    rootStr.push_back("Ever since you were a child, you have aspired to be a warrior.");
    rootStr.push_back("You've seen how great warriors are respected and you have trained from a tender age to be just like them.");
    rootStr.push_back("And then one day, your village is attacked by bandits.");
    rootStr.push_back("On one hand, you feel the thrill of finally proving your mettle. You know that this is the chance you've been waiting for all your life.");
    rootStr.push_back("On the other, you realize that you've never been in a real fight before. A wrong move could get you killed.");
    rootStr.push_back("Your choices will determine the fate of the ones around you... and of yourself.");
    rootStr.push_back("Press [1] to stay and fight!");
    rootStr.push_back("Press [2] to run.");
    Choice root(rootStr);
    Choice fightPath = warriorFightPath();
    Choice runPath = warriorRunPath();
    root.choices.push_back(warriorFightPath());
    root.choices.push_back(warriorRunPath());
    return root;
}

Choice game::warriorFightPath()
{
    vector<string> defendVillageStr;
    defendVillageStr.push_back("You decide to stay and fight, for honour and for glory.");
    defendVillageStr.push_back("Should you prevail, you will have saved everyone you know and cared for.");
    defendVillageStr.push_back("And should you fail, you know you will have died for a good cause.");
    defendVillageStr.push_back("At the sight of danger, you enter a battle frenzy, effectively applying all your training in the fight.");
    defendVillageStr.push_back("After a long and arduous battle, you heroicly slay a lot of bandits.");
    defendVillageStr.push_back("The villagers are impressed by your feats. Many are calling you a great hero.");
    defendVillageStr.push_back("Most of the attackers escape, but you manage to capture one. The general opinion is to have him killed.");
    defendVillageStr.push_back("But some of the villagers believe that he should be questioned to reveal their hideout.");
    defendVillageStr.push_back("Before the village council is involved, they turn to you - the hero of the battle - to decide.");
    defendVillageStr.push_back("Press [1] to kill the bandit.");
    defendVillageStr.push_back("Press [2] to question the bandit.");
    Choice defendVillage(defendVillageStr);
    defendVillage.consequences.push_back(STR_BOOST);
    defendVillage.consequences.push_back(KARMA_BOOST);

    vector<string> killBanditStr;
    killBanditStr.push_back("You decide that because of the crime commited against your people, this bandit has no right to live.");
    killBanditStr.push_back(unfinished);
    Choice killBandit(killBanditStr);
    killBandit.choices.push_back(fin);
    killBandit.consequences.push_back(INT_DROP);

    vector<string> questionBanditStr;
    questionBanditStr.push_back("You ask the bandit about the whereabouts of his fellow criminals. However, the bandit remains silent.");
    questionBanditStr.push_back("You consider your options. You could torture the bandit until he speaks. Or you could offer him a better deal.");
    questionBanditStr.push_back("[1] Torture.");
    questionBanditStr.push_back("[2] Deal.");
    Choice questionBandit(questionBanditStr);

    vector<string> tortureBanditStr;
    tortureBanditStr.push_back("You torture the bandit. After a certain point, he breaks and tells you the whereabouts of their last hideout.");
    tortureBanditStr.push_back(unfinished);
    Choice tortureBandit(tortureBanditStr);
    tortureBandit.choices.push_back(fin);
    tortureBandit.consequences.push_back(KARMA_DROP);

    vector<string> dealBanditStr;
    dealBanditStr.push_back("You offer deal. He happy.");
    dealBanditStr.push_back(unfinished);
    Choice dealBandit(dealBanditStr);
    dealBandit.choices.push_back(fin);
    dealBandit.consequences.push_back(KARMA_BOOST);
    dealBandit.consequences.push_back(WIS_BOOST);

    questionBandit.choices.push_back(tortureBandit);
    questionBandit.choices.push_back(dealBandit);

    defendVillage.choices.push_back(killBandit);
    defendVillage.choices.push_back(questionBandit);

    return defendVillage;
}

Choice game::warriorRunPath()
{
    vector<string> abandonVillageStr;
    abandonVillageStr.push_back("You grab your belongings and run.");
    abandonVillageStr.push_back("The screams of those being butchered fill the air, but you keep running.");
    abandonVillageStr.push_back("You keep running until you are sure that you are safe.");
    abandonVillageStr.push_back("Night has fallen. You are too tired to continue. You must rest for the night.");
    abandonVillageStr.push_back("[1] Sleep beside the road.");
    abandonVillageStr.push_back("[2] Sleep in the forest.");
    Choice abandonVillage(abandonVillageStr);
    abandonVillage.consequences.push_back(KARMA_DROP);

    vector<string> sleepRoadStr;
    sleepRoadStr.push_back("You spend the night beside the road.");
    sleepRoadStr.push_back(unfinished);
    Choice sleepRoad(sleepRoadStr);
    sleepRoad.choices.push_back(fin);

    vector<string> sleepForestStr;
    sleepForestStr.push_back("You are sleeping on the forest floor.");
    sleepForestStr.push_back(unfinished);
    Choice sleepForest(sleepForestStr);
    sleepForest.choices.push_back(fin);

    vector<string> wolfDeathStr;
    wolfDeathStr.push_back("Wolves eat you.");
    Choice wolfDeath(wolfDeathStr);

    sleepForest.conditionalConsequences.push_back(make_tuple(STR_DROP, 0.5, 0));
    sleepForest.conditionalChoices.push_back(wolfDeath);


    abandonVillage.choices.push_back(sleepRoad);
    abandonVillage.choices.push_back(sleepForest);
    return abandonVillage;
}

void game::playChoices()
{
    // Base Case
    if (current->choices.size() == 0)
        {
            readChoice();
            cout << "End of the line." << endl;
            string input;
            input = formatInput();
            quit();
        }
    // if list empty, read problem
    // else, read problem, take input and recurse
//    if (current->choices.size == 0)
//        gameOver = true;
    else
    {
        readChoice();
        playCondConsequences();
        playConsequences();
        goto NEXT;
        TOP:
            readChoice();
        NEXT:
            string input;
            input = formatInput();
            if (input == "Q")
                quit();
            if (input == "S")
            {
                thyself->showStatus();
                goto TOP;
            }

        int intIn;

        try {
            intIn = stoi(input, nullptr, 10);
        }
        catch (std::invalid_argument iaex)
        {
            cout << "Invalid Input. Please try again" << endl;
            cout << endl;
            goto TOP;
        }

        if (intIn == 0 || intIn > current->choices.size())
        {
            cout << "Invalid Input. Please try again" << endl;
            cout << endl;
            goto TOP;
        }
        else
        {
            current = &current->choices[intIn-1];
            cout << endl;
            playChoices();
        }
    }
}

void game::readChoice()
{
    for(string s: current->problems)
        cout << s << endl;
}

// Helpers//

Choice game::endChoice()
{
    vector<string> endStr;
    endStr.push_back("");
    Choice end(endStr);
    return end;
}

void game::playConsequences()
{
    if (current->consequences.size() != 0)
    {
        for (int i: current->consequences)
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


void game::condConsHelper(double att, double check, int cond, string txt)
{
    if (cond < 0)
    {
        if (att < check)
        {
            cout << "Your " << txt << " was too low." << endl;
        }
    }
    else
    {
        if (att > check)
        {
            cout << "Your " << txt << " was enough." << endl;
        }
    }

}


// if condition is true, change current to something
void game::playCondConsequences()
{
    if (current->conditionalConsequences.size() != 0)
    {
        for (tuple<int, double, int> i : current->conditionalConsequences)
        {
            double num = get<1>(i);
            switch(get<0>(i))
            {
            case STR_DROP:
                condConsHelper(thyself->getSTR(), num, -1, "strength");
                goto CONSEQUENCE;
            case STR_BOOST:
                condConsHelper(thyself->getSTR(), num, 1, "strength");
                goto CONSEQUENCE;
            case DEF_DROP:
                condConsHelper(thyself->getDEF(), num, -1, "defense");
                goto CONSEQUENCE;
            case DEF_BOOST:
                condConsHelper(thyself->getDEF(), num, 1, "defense");
                goto CONSEQUENCE;
            case AGL_DROP:
                condConsHelper(thyself->getAGL(), num, -1, "agility");
                goto CONSEQUENCE;
            case AGL_BOOST:
                condConsHelper(thyself->getAGL(), num, 1, "agility");
                goto CONSEQUENCE;
            case DEX_DROP:
                condConsHelper(thyself->getDEX(), num, -1, "dexterity");
                goto CONSEQUENCE;
            case DEX_BOOST:
                condConsHelper(thyself->getDEX(), num, 1, "dexterity");
                goto CONSEQUENCE;
            case INT_DROP:
                condConsHelper(thyself->getINT(), num, -1, "intelligence");
                goto CONSEQUENCE;
            case INT_BOOST:
                condConsHelper(thyself->getINT(), num, 1, "intelligence");
                goto CONSEQUENCE;
            case WIS_DROP:
                condConsHelper(thyself->getWIS(), num, -1, "wisdom");
                goto CONSEQUENCE;
            case WIS_BOOST:
                condConsHelper(thyself->getWIS(), num, 1, "wisdom");
                goto CONSEQUENCE;
            case KARMA_DROP:
                condConsHelper(thyself->getKarma(), num*100, -1, "karma");
                goto CONSEQUENCE;
            case KARMA_BOOST:
                condConsHelper(thyself->getKarma(), num*100, 1, "karma");
            CONSEQUENCE:
                current = &current->conditionalChoices[get<2>(i)];
                playChoices();
            }
        }
    }
}

// Consequences

// HP
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

double consHelper(double fna, int num, string str)
{
    double curr = fna*10 + num;
    int newNum;
    string other;
    if (num > 0)
    {
        newNum = min((int) curr, 10);
        other = " increased ";
    }
    else
    {
        newNum = max((int) curr, 1);
        other = " decreased ";
    }
    double finNum = ((double) newNum)/10;
    cout << str << other << "to: " << finNum << endl;
    return finNum;
}

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
    thyself->setWIS(consHelper(thyself->getWIS(), 1, "Wisdom"));
}

void game::karmaBoost()
{
    thyself->setKarma(karmaHelper(thyself->getKarma(), 10, "Karma"));
}

void game::karmaDrop()
{
    thyself->setKarma(karmaHelper(thyself->getKarma(), -10, "Karma"));
}
