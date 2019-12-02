#ifndef _CHARCREATE_H_
#define _CHARCREATE_H_
#include <iostream>
#include "player.h"
#include "utils.h"

class charCreate{

public:
    charCreate(std::string &inputName, std::string &inputClass);

    void tutorial();

    void selectClass(std::string &inputClass);

    //void showStatus(Player player);

    void rechoice(Player &player);

private:

    void reselectName(Player &player);

    void reselectClass(Player &player);
};

#endif // CHARCREATE_H
