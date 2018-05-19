#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

// The player class containing player's name, class and attributes.
class Player
{
    private:
        string name;
        string playerClass;

        int maxHP;
        int HP;
        double STR; // determines the damage the player deals
        double DEF; // determines the damage the player takes
        double AGL; // determines the likelihood of taking damage
        double DEX; // determines the likelihood of dealing damage
        double INT; // determines the likelihood of spells working
        double WIS; // determines the effectiveness of spells
        int karma;

    public:
        Player() : name(""), maxHP(-1), HP(-1), playerClass("") {}

        Player(string inputName, string inputClass);

        string getName();

        void setName(string inputName);

        int getMaxHP();

        void setMaxHP(int num);

        int getHP();

        void setHP(int num);

        double getSTR();

        void setSTR(double num);

        double getDEF();

        void setDEF(double num);

        double getAGL();

        void setAGL(double num);

        double getDEX();

        void setDEX(double num);

        double getINT();

        void setINT(double num);

        double getWIS();

        void setWIS(double num);

        int getKarma();

        void setKarma(int num);

        string getClass();

        string getClassName();

        void setClass(string inputClass);

        void showStatus();

        string showKarma();
};

#endif // PLAYER_H
