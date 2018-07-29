#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <algorithm>

std::string formatInput();

void quit();

void quitCheck(std::string input);

void printSpace();

void printStat(std::string txt, double num);

void printLine();

void printLine(std::string input);

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

enum Comp
{
    down = 1,
    up = 1,
};

#endif // UTILS_H
