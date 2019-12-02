#ifndef STORY_H
#define STORY_H

#include "choice.h"
#include "utils.h"

using namespace std;

class Story{

public:
    Story();

    Choice warriorStoryline();

    Choice warriorFightPath();

    Choice warriorRunPath();

    Choice mageStoryline();

    Choice rogueStoryline();

    Choice endChoice();

private:
    string unfinished;
    Choice fin;

};

#endif
