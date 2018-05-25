#include "game.h"

using namespace std;

string unfinished = "Unfinished storyline. Press [1] to end game.";
Choice fin;
vector<string> emptyVtr;

game::game(Player &player)
{
    thyself = &player;
    runGame();
}

// Creates the choices and initiates the game
void game::runGame()
{
    fin = endChoice();
    createChoices();

	string input;
	TOP:
    cout << "Press button to continue" << endl;
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

// Creates appropriate storyline based on the player's class
void game::createChoices()
{
    int plc = stoi(thyself->getClass(), nullptr, 10);
    switch(plc)
    {
    case 1:
        choiceTree = warriorStoryline();
        break;
    case 2:
        choiceTree = rogueStoryline();
        break;
    case 3:
        choiceTree = mageStoryline();
        break;
    }
    current = &choiceTree;
}

// Warrior Storyline
Choice game::warriorStoryline()
{
    Choice root(emptyVtr);
    root.addText("Ever since you were a child, you have aspired to be a warrior.");
    root.addText("You've seen how great warriors are respected and you have trained from a tender age to be just like them.");
    root.addText("And then one day, your village is attacked by bandits.");
    root.addText("On one hand, you feel the thrill of finally proving your mettle.");
    root.addText("You know that this is the chance you've been waiting for all your life.");
    root.addText("On the other, you realize that you've never been in a real fight before. A wrong move could get you killed.");
    root.addText("Your choices will determine the fate of the ones around you... and of yourself.");
    root.addText("Press [1] to stay and fight!");
    root.addText("Press [2] to run");
    Choice fightPath = warriorFightPath();
    Choice runPath = warriorRunPath();
    root.addChoice(fightPath);
    root.addChoice(runPath);
    return root;
}

// Warrior Path 1: Defend The Village
Choice game::warriorFightPath()
{
    Choice defendVillage(emptyVtr);
    defendVillage.addText("You decide to stay and fight, for honour and for glory.");
    defendVillage.addText("Should you prevail, you will have saved everyone you know and cared for.");
    defendVillage.addText("And should you fail, you know you will have died for a good cause.");
    defendVillage.addText("At the sight of danger, you enter a battle frenzy, effectively applying all your training in the fight.");
    defendVillage.addText("After a long and arduous battle, you heroicly slay a lot of bandits.");
    defendVillage.addText("The villagers are impressed by your feats. Many are calling you a great hero.");
    defendVillage.addText("Most of the attackers escape, but you manage to capture one. The general opinion is to have him killed.");
    defendVillage.addText("But some of the villagers believe that he should be questioned to reveal their hideout.");
    defendVillage.addText("Before the village council is involved, they turn to you - the hero of the battle - to decide.");
    defendVillage.addText("Press [1] to kill the bandit.");
    defendVillage.addText("Press [2] to question the bandit.");
    defendVillage.addConsequence(STR_BOOST);
    defendVillage.addConsequence(DEF_BOOST);
    defendVillage.addConsequence(AGL_BOOST);
    defendVillage.addConsequence(KARMA_BOOST);

    Choice killBandit(emptyVtr);
    killBandit.addText("You decide that because of the crime commited against your people, this bandit has no right to live.");
    killBandit.addText("Your decision angers the entire village.");
    killBandit.addText("People start panicking as they realize that you destroyed their only source of information.");
    killBandit.addText("You realize that you will be attacked soon.");
    killBandit.addText("[1] Run before you are attacked.");
    killBandit.addText("[2] Draw your sword in warning.");
    killBandit.addText("[3] Kill anyone who stands before you.");
    killBandit.addConsequence(WIS_DROP);

    Choice relayRunVillage(emptyVtr);
    relayRunVillage.addText("You tell yourself that it's not worth getting into a fight.");
    relayRunVillage.markRelay();
    relayRunVillage.addConsequence(AGL_BOOST);

    Choice drawSword(emptyVtr);
    drawSword.addText("You draw your sword and stand menacingly, challenging any who would dare to attack you.");
    drawSword.addText("After a moment, it becomes very clear that no one wants to make an enemy of you.");
    drawSword.addText("[1] Leave the village.");
    drawSword.addText("[2] Vent your rage and kill everyone around you.");
    drawSword.addConsequence(INT_BOOST);
    drawSword.addConsequence(DEF_BOOST);

    Choice relayLeaveVillage(emptyVtr);
    relayLeaveVillage.addText("You realize that a village where you aren't valued has no meaning to you. So you leave.");
    relayLeaveVillage.markRelay();

    Choice massacreVillage(emptyVtr);
    massacreVillage.addText("Suddenly you charge yourself on the nearest person, stabbing your sword into him.");
    massacreVillage.addText("Who he was does not really matter. What matters is that you were challenged.");
    massacreVillage.addText("After the initial onslaught, it becomes clear there are only so many that you can kill.");
    massacreVillage.addText("The villagers retaliate and you sustain an injury.");
    massacreVillage.addText("[1] Continue fighting.");
    massacreVillage.addText("[2] Run away from the village");
    massacreVillage.addConsequence(STR_BOOST);
    massacreVillage.addConsequence(KARMA_DROP);
    massacreVillage.addConsequence(KARMA_DROP);
    massacreVillage.addChoice(fin);

    Choice questionBandit(emptyVtr);
    questionBandit.addText("You ask the bandit about the whereabouts of his fellow criminals. However, the bandit remains silent.");
    questionBandit.addText("You consider your options. You could torture the bandit until he speaks. Or you could offer him a better deal.");
    questionBandit.addText("[1] Torture.");
    questionBandit.addText("[2] Deal.");

    Choice tortureBandit(emptyVtr);
    tortureBandit.addText("You torture the bandit. After a certain point, he breaks and tells you the whereabouts of their last hideout.");
    tortureBandit.addText("You decide it's time to take the fight to them.");
    tortureBandit.addText("[1] Attack alone.");
    tortureBandit.addText("[2] Attempt to raise an army for the attack.");
    tortureBandit.addConsequence(KARMA_DROP);
    tortureBandit.addConsequence(STR_BOOST);
    tortureBandit.addConsequence(WIS_BOOST);

    Choice dealBandit(emptyVtr);
    dealBandit.addText("You offer the bandit a deal. That his past transgressions will be forgiven and will be offered a piece of land.");
    dealBandit.addText("The offer pleases him. Overjoyed, he gives up the location of his past compatriots.");
    dealBandit.addText("[1] Attack alone.");
    dealBandit.addText("[2] Raise an army.");
    dealBandit.addConsequence(KARMA_BOOST);
    dealBandit.addConsequence(INT_BOOST);
    dealBandit.addConsequence(WIS_BOOST);

    Choice attackAlone(emptyVtr);
    attackAlone.addText("You make your way to the bandit's hideout and attack alone.");
    attackAlone.addText("You emerge victorious as you slaughter every last one of them.");
    attackAlone.addText("After the fight, as the battle lust ebbs away, you realize you are a force to be reckoned with.");
    attackAlone.addText("You could return to your village or you could move forward, see what fate has in store.");
    attackAlone.addText("[1] Return to the village.");
    attackAlone.addText("[2] Head out for adventure.");
    attackAlone.addConsequence(STR_BOOST);
    attackAlone.addConsequence(AGL_BOOST);

    Choice banditDeath(emptyVtr);
    banditDeath.addText("The bandits overpower you and kill you.");
    attackAlone.addCondCons(STR_DROP, 0.5, 0);
    attackAlone.addCondChoice(banditDeath);

    Choice raiseArmy(emptyVtr);
    raiseArmy.addText("You raise an army consisting of the able-bodied men and women from the village.");
    raiseArmy.addText("The might of your attack takes the wounded and injured bandits by surprise.");
    raiseArmy.addText("Now that an enemy so close to home has been neutralized, you realize there are necessary things at hand.");
    raiseArmy.addText("[1] Secure this outpost and fortify it to protect the village from future attacks.");
    raiseArmy.addText("[2] Return to the village to recount the events.");
    raiseArmy.addText("[3] Heed the call of the adventurer in you and head out on a journey.");
    raiseArmy.addCondCons(KARMA_DROP, 90, 0);
    raiseArmy.addConsequence(STR_BOOST);
    raiseArmy.addConsequence(DEF_BOOST);

    Choice relayAttackAlone(emptyVtr);
    relayAttackAlone.addText("No one heeds your call to arms.");
    relayAttackAlone.addText("Frustrated at their lack of faith, you decide to do the only thing that's left.");
    relayAttackAlone.markRelay();

    Choice secureOutpost(emptyVtr);
    secureOutpost.addText("You secure the outpost.");
    secureOutpost.addText(unfinished);
    secureOutpost.addChoice(fin);

    Choice returnVillage(emptyVtr);
    returnVillage.addText("You return to the village to deliver the news of the outpost.");
    returnVillage.addText("Yet, it appears that not everything will pass as smoothly as you had expected.");
    returnVillage.addText("The elders are not pleased with how the decisions were made without their presence.");
    returnVillage.addText("For that matter, they've decided to blame you for defying their authority.");
    returnVillage.addText("[1] Surrender to fate and await judgement.");
    returnVillage.addText("[2] Challenge the authority of the council.");
    returnVillage.addText("[3] Run away before they have a chance of confronting you.");
    returnVillage.addText("[4] Kill all the elders.");

    Choice surrenderVillage(emptyVtr);
    surrenderVillage.addText("You've surrendered to the village elders.");
    surrenderVillage.addText(unfinished);
    surrenderVillage.addChoice(fin);

    Choice challengeElders(emptyVtr);
    challengeElders.addText("You have challenged the authority of the elders.");
    challengeElders.addText(unfinished);
    challengeElders.addChoice(fin);

    Choice runAway(emptyVtr);
    runAway.addText("You run away!");
    runAway.addText(unfinished);
    runAway.addChoice(fin);

    Choice killElders(emptyVtr);
    killElders.addText("You kill the elders.");
    killElders.addText(unfinished);
    killElders.addChoice(fin);

    returnVillage.addChoice(surrenderVillage);
    returnVillage.addChoice(challengeElders);
    returnVillage.addChoice(runAway);
    returnVillage.addChoice(killElders);

    Choice outAdventure(emptyVtr);
    outAdventure.addText("You head out into the world for adventure.");
    outAdventure.addText(unfinished);
    outAdventure.addChoice(fin);

    attackAlone.addChoice(returnVillage);
    attackAlone.addChoice(outAdventure);

    relayRunVillage.addChoice(outAdventure);

    relayAttackAlone.addChoice(attackAlone);

    relayLeaveVillage.addChoice(outAdventure);

    drawSword.addChoice(relayLeaveVillage);
    drawSword.addChoice(massacreVillage);

    killBandit.addChoice(relayRunVillage);
    killBandit.addChoice(drawSword);
    killBandit.addChoice(massacreVillage);

    raiseArmy.addChoice(secureOutpost);
    raiseArmy.addChoice(returnVillage);
    raiseArmy.addChoice(outAdventure);
    raiseArmy.addCondChoice(relayAttackAlone);

    dealBandit.addChoice(attackAlone);
    dealBandit.addChoice(raiseArmy);

    tortureBandit.addChoice(attackAlone);
    tortureBandit.addChoice(raiseArmy);

    questionBandit.addChoice(tortureBandit);
    questionBandit.addChoice(dealBandit);

    defendVillage.addChoice(killBandit);
    defendVillage.addChoice(questionBandit);

    return defendVillage;
}

// Warrior Path 2: Run Away from the conflict
Choice game::warriorRunPath()
{
    Choice abandonVillage(emptyVtr);
    abandonVillage.addText("You grab your belongings and run.");
    abandonVillage.addText("The screams of those being butchered fill the air, but you keep running.");
    abandonVillage.addText("You keep running until you are sure that you are safe.");
    abandonVillage.addText("Night has fallen. You are too tired to continue. You must rest for the night.");
    abandonVillage.addText("[1] Sleep beside the road.");
    abandonVillage.addText("[2] Sleep in the forest.");
    abandonVillage.addConsequence(KARMA_DROP);

    Choice sleepRoad(emptyVtr);
    sleepRoad.addText("You spend the night beside the road.");
    sleepRoad.addText(unfinished);
    sleepRoad.addChoice(fin);

    Choice sleepForest(emptyVtr);
    sleepForest.addText("You are sleeping on the forest floor.");
    sleepForest.addText(unfinished);
    sleepForest.addChoice(fin);

    Choice wolfDeath(emptyVtr);
    wolfDeath.addText("While you slept defenseless and weak, wolves descend upon you.");
    wolfDeath.addText("You scream as they take you by surprise. Your attempts so defend yourself are in vain.");
    wolfDeath.addText("In the end, you feel life ebb away and welcome death.");
    wolfDeath.addText("It seems as if that would be better than the pain.");

    sleepForest.addCondCons(STR_DROP, 0.5, 0);
    sleepForest.addCondChoice(wolfDeath);

    abandonVillage.addChoice(sleepRoad);
    abandonVillage.addChoice(sleepForest);
    return abandonVillage;
}

Choice game::rogueStoryline()
{
    vector<string> rootStr;
    rootStr.push_back(unfinished);
    Choice root(rootStr);
    return root;
}

Choice game::mageStoryline()
{
    return rogueStoryline(); // stub
}

void game::playChoices()
{
    // Base Case: Checks whether it's the end of the path/tree
    if (current->numberOfChoices() == 0)
        {
            current->readChoice();
            quit();
        }

    // Case 1: If the Choice is a relay choice, read the text, apply consequences, change the pointer and self recurse to continue game
    else if (current->getRelay())
    {
        current->readChoice();
        playConsequences();
        setCurrent(current->choices[0]);
        playChoices();
    }

    // Case 3: Continue game. If there are any conditional consequences, play them. Else read the text, apply consequences and change
    //         the pointer according to user input.
    else
    {
        playCondConsequences();
        current->readChoice();
        playConsequences();
        goto NEXT;
        TOP:
            current->readChoice();
        NEXT:
            string input;
            input = formatInput();
            quitCheck(input);
            if (input == "S")
            {
                thyself->showStatus();
                goto TOP;
            }

        int intIn;

        // If input is not a number, try again.
        try {
            intIn = stoi(input, nullptr, 10);
        }
        catch (std::invalid_argument iaex)
        {
            cout << "Invalid Input. Please try again" << endl;
            cout << endl;
            goto TOP;
        }

        // If input number is > 0 or < number of available choices, try again
        if (intIn == 0 || intIn > current->numberOfChoices())
        {
            cout << "Invalid Input. Please try again" << endl;
            cout << endl;
            goto TOP;
        }
        // Case: Valid input
        else
        {
            setCurrent(current->choices[intIn-1]);
            cout << endl;
            playChoices();
        }
    }
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





// if condition is true, change current to something
void game::playCondConsequences()
{
    if (current->conditionalConsequences.size() != 0)
    {
        for (tuple<int, double, int> i : current->conditionalConsequences)
        {
            bool jump = false;
            double num = get<1>(i);
            switch(get<0>(i))
            {
            case STR_DROP:
                condConsHelper(thyself->getSTR(), num, -1, "strength", jump);
                goto CONSEQUENCE;
            case STR_BOOST:
                condConsHelper(thyself->getSTR(), num, 1, "strength", jump);
                goto CONSEQUENCE;
            case DEF_DROP:
                condConsHelper(thyself->getDEF(), num, -1, "defense", jump);
                goto CONSEQUENCE;
            case DEF_BOOST:
                condConsHelper(thyself->getDEF(), num, 1, "defense", jump);
                goto CONSEQUENCE;
            case AGL_DROP:
                condConsHelper(thyself->getAGL(), num, -1, "agility", jump);
                goto CONSEQUENCE;
            case AGL_BOOST:
                condConsHelper(thyself->getAGL(), num, 1, "agility", jump);
                goto CONSEQUENCE;
            case DEX_DROP:
                condConsHelper(thyself->getDEX(), num, -1, "dexterity", jump);
                goto CONSEQUENCE;
            case DEX_BOOST:
                condConsHelper(thyself->getDEX(), num, 1, "dexterity", jump);
                goto CONSEQUENCE;
            case INT_DROP:
                condConsHelper(thyself->getINT(), num, -1, "intelligence", jump);
                goto CONSEQUENCE;
            case INT_BOOST:
                condConsHelper(thyself->getINT(), num, 1, "intelligence", jump);
                goto CONSEQUENCE;
            case WIS_DROP:
                condConsHelper(thyself->getWIS(), num, -1, "wisdom", jump);
                goto CONSEQUENCE;
            case WIS_BOOST:
                condConsHelper(thyself->getWIS(), num, 1, "wisdom", jump);
                goto CONSEQUENCE;
            case KARMA_DROP:
                condConsHelper(thyself->getKarma(), num, -1, "karma", jump);
                goto CONSEQUENCE;
            case KARMA_BOOST:
                condConsHelper(thyself->getKarma(), num, 1, "karma", jump);
            CONSEQUENCE:
                if (jump)
                {
                    setCurrent(current->conditionalChoices[get<2>(i)]);
                    playChoices();
                }
            }
        }
    }
}

void game::condConsHelper(double att, double check, int cond, string txt, bool &jump)
{
    if (cond < 0)
    {
        if (att < check)
        {
            cout << "Your " << txt << " was too low." << endl;
            jump = true;
        }
    }
    else
    {
        if (att > check)
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
