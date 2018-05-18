#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <math.h>
#include "player.h"
#include "utils.h"
#include "choice.h"

class game
{
private:
    Choice choiceTree;
    Choice *current;
    bool gameOver = false;

    enum Cons
    {
        STR_BOOST,
        STR_DROP,
        DEF_BOOST,
        DEF_DROP,
        AGL_BOOST,
        AGL_DROP,
        DEX_BOOST,
        DEX_DROP,
        INT_BOOST,
        INT_DROP,
        WIS_BOOST,
        WIS_DROP,
        KARMA_BOOST,
        KARMA_DROP,
        GAME_OVER,
    };

    Choice warriorStoryline();

//    Choice mageStoryline();

//    Choice rogueStoryline();

    Choice endChoice();

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

public:
    Player *thyself; // For comic purposes

    game(Player player);

    void runGame();

    void showStats();

    void createChoices();

    void playChoices();

    void readChoice();

    void playConsequences();

    void playCondConsequences();
};

#endif // GAME_H
