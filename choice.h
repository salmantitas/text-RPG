#ifndef CHOICE_H
#define CHOICE_H
#include <iostream>
#include <vector>
#include <tuple>

class Choice{
//private:
public:
    std::vector<std::string> problems;
    std::vector<Choice> choices;
    std::vector<Choice> conditionalChoices;
    std::vector<int> consequences;
    std::vector<std::tuple<int, double, int>> conditionalConsequences;

    Choice() {};//: choices(NULL), problems(NULL) {};
    Choice(std::vector<std::string> problems);

    // Consequence Functions

//    Choice(std::string problem);
};

#endif // CHOICE_H
