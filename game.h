#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <math.h>
#include "player.h"
#include "utils.h"
#include "choice.h"
#include "story.h"

class game
{
private:
    typedef void (game::*statPtr)();
    std::vector<statPtr> statFunctions;

    Choice choiceTree;
    Choice *current;
    bool gameOver = false;

    void createStory();

    void createStatFunctions();

    // Consequences

    void HPBoost(int num);

    void HPDrop(int num);

    void STRBoost();

    void STRDrop();

    void DEFBoost();

    void DEFDrop();

    void AGLBoost();

    void AGLDrop();

    void DEXBoost();

    void DEXDrop();

    void INTBoost();

    void INTDrop();

    void WISBoost();

    void WISDrop();

    void karmaBoost();

    void karmaDrop();

    void condConsHelper(double att, double check, int cond, std::string txt, bool &jump);

    void setCurrent(Choice &choice);

    void setCurrent(Choice* choice);

public:
    Player *thyself; // For comic purposes

    game(Player &player);

    void runGame();

    void createChoices();

    void playChoices();

    void playConsequences();

    void playCondConsequences();
};

#endif // GAME_H
