#include "choice.h"

using namespace std;


Choice::Choice()
{
//
}

Choice::Choice(vector<string> problems) {
    this->problems = problems;
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

void Choice::readChoice()
{
    for (string s: problems)
        cout << s << endl;
}

Choice* Choice::choiceAt(int num)
{
    Choice* ptr = &choices[num];
    return ptr;
}

bool Choice::getRelay()
{
    return relay;
}

void Choice::markRelay()
{
    relay = true;
}
