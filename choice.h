#ifndef CHOICE_H
#define CHOICE_H
#include <iostream>
#include <vector>
#include <tuple>

class Choice{
private:
    bool played = false;
    std::vector<std::string> problems;

public:
    std::vector<Choice> choices;
    std::vector<Choice> conditionalChoices;
    std::vector<int> consequences;
    std::vector<std::tuple<int, double, int>> conditionalConsequences;

    Choice() {};//: choices(NULL), problems(NULL) {};
    Choice(std::vector<std::string> problems);

    void addText(std::string str);

    void addChoice(Choice choice);

    void addConsequence(int num);

    void addCondCons(int a, double b, int c);

    void addCondChoice(Choice choice);

    int numberOfChoices();

    void readChoice();
};

#endif // CHOICE_H
