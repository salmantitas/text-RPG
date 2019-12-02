#ifndef _CHARCREATE_H_
#define _CHARCREATE_H_
#include <iostream>
#include "player.h"
#include "utils.h"

using namespace std;

class charCreate{

public:
    charCreate(string &inputClass);

    void reselectClass(Player &player);

private:
    void tutorial();

    void selectClass(string &inputClass);
};

#endif // CHARCREATE_H
