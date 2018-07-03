#include "choice.h"

using namespace std;


Choice::Choice()
{
    relay = false;
}

void Choice::addText(string str)
{
    this->problems.push_back(str);
}

void Choice::addChoice(Choice &choice)
{
    choices.push_back(choice);
}

void Choice::addConsequence(int num)
{
    consequences.push_back(num);
}

void Choice::addCondCons(int a, double b, int c)
{
    conditionalConsequences.push_back(make_tuple(a,b,c));
}

void Choice::addCondChoice(Choice &choice)
{
    conditionalChoices.push_back(choice);
}

int Choice::numberOfChoices()
{
    return choices.size();
}

int Choice::numberOfCons()
{
    return consequences.size();
}

int Choice::numberOfCondCons()
{
    return conditionalConsequences.size();
}

void Choice::readChoice()
{
    for (string s: problems)
        cout << s << endl;
}

Choice* Choice::choiceAt(int num)
{
    return &choices[num];
}

Choice* Choice::choiceAtCond(int num)
{
    return &conditionalChoices[num];
}

vector<int> Choice::getCons()
{
    return consequences;
}

vector<tuple<int, double, int>> Choice::getCondCons()
{
    return conditionalConsequences;
}

bool Choice::getRelay()
{
    return relay;
}

void Choice::markRelay()
{
    relay = true;
}
