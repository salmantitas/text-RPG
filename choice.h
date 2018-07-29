#ifndef CHOICE_H
#define CHOICE_H
#include <iostream>
#include <vector>
#include <tuple>

class Choice{
private:
    bool relay;
    std::vector<std::string> problems;
    std::vector<Choice> choices;
    std::vector<Choice> conditionalChoices;
    std::vector<int> consequences;
    std::vector<std::tuple<int, double, int>> conditionalConsequences; // tuple<int enum, double requiredStat, int indexOfConditionalChoice>

public:
    Choice();

    void addText(std::string str);

    void addChoice(Choice &choice);

    void addConsequence(int num);

    void addCondCons(int id, double requiredStat, int indexOfConditionalChoice); 

    void addCondChoice(Choice &choice);

    int numberOfChoices();

    int numberOfCons();

    int numberOfCondCons();

    void readChoice();

    Choice* choiceAt(int num);

    Choice* choiceAtCond(int num);

    std::vector<int> getCons();

    std::vector<std::tuple<int, double, int>> getCondCons();

    bool getRelay();

    void markRelay();
};

#endif // CHOICE_H
