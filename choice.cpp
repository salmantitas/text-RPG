#include "choice.h"

using namespace std;

Choice::Choice(vector<string> problems) {
    this->problems = problems;
}

void Choice::addText(string str)
{
    problems.push_back(str);
}

void Choice::addChoice(Choice choice)
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

void Choice::addCondChoice(Choice choice)
{
    conditionalChoices.push_back(choice);
}

void Choice::readChoice()
{
    for (string s: problems)
        cout << s << endl;
}
