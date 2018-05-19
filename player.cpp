#include "player.h"

Player::Player(string inputName, string inputClass)
{
    setName(inputName);
    setClass(inputClass);
}

string Player::getName() {return name;};

void Player::setName(string inputName)
{
    name = inputName;
}

int Player::getMaxHP() {return maxHP;};

void Player::setMaxHP(int num)
{
    maxHP = num;
}

int Player::getHP() {return HP;};

void Player::setHP(int num)
{
    HP = num;
}

double Player::getSTR() {return STR;};

void Player::setSTR(double num)
{
    STR = num;
}

double Player::getDEF() {return DEF;};

void Player::setDEF(double num)
{
    DEF = num;
}

double Player::getAGL() {return AGL;};

void Player::setAGL(double num)
{
    AGL = num;
}

double Player::getDEX() {return DEX;};

void Player::setDEX(double num)
{
    DEX = num;
}

double Player::getINT() {return INT;};

void Player::setINT(double num)
{
    INT = num;
}

double Player::getWIS() {return WIS;};

void Player::setWIS(double num)
{
    WIS = num;
}

int Player::getKarma() {return karma;};

void Player::setKarma(int num)
{
    karma = num;
}

string Player::getClass() {return playerClass;}

string Player::getClassName()
    {
        string ret;
        if (playerClass == "1")
            ret = "Warrior";
        if (playerClass == "2")
            ret = "Rogue";
        if (playerClass == "3")
            ret = "Mage";
        return ret;
    }

void Player::setClass(string inputClass)
{
    if (inputClass == "1")
    {
        HP = 100; maxHP = 100;
        STR = 0.3;
        DEF = 0.3;
        AGL = 0.1;
        DEX = 0.2;
        INT = 0.3;
        WIS = 0.2;
    }
    if (inputClass == "2")
    {
        HP = 75; maxHP = 75;
        STR = 0.2;
        DEF = 0.2;
        AGL = 0.3;
        DEX = 0.3;
        INT = 0.2;
        WIS = 0.1;
    }
    if (inputClass == "3")
    {
        HP = 50; maxHP = 50;
        STR = 0.1;
        DEF = 0.1;
        AGL = 0.1;
        DEX = 0.1;
        INT = 0.5;
        WIS = 0.5;
    }
    playerClass = inputClass;
}

void Player::showStatus(){
   cout << "You are " << name << endl;
   cout << "Your HP is " << HP << "/" << maxHP << endl;
   cout << "You have chosen class " << getClassName() << endl;
   cout << "Attributes" << endl;
   cout << "Strength:     " << STR << endl;
   cout << "Defense:      " << DEF << endl;
   cout << "Agility:      " << AGL << endl;
   cout << "Dexterity:    " << DEX << endl;
   cout << "Intelligence: " << INT << endl;
   cout << "Wisdom:       " << WIS << endl;
   cout << "Your karma is " << showKarma() << ": " << karma << endl;
}

string Player::showKarma()
{
    string ret;
    if (karma == 50)
        return "neutral";
    if (karma > 50)
        return "good";
    else return "bad";
}
