#include "utils.h"

using namespace std;

string formatInput()
{
    string input;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    quitCheck(input);
    return input;
}

void quit()
{
    cout << "The Game Is Over. Press any key to exit." << endl;
    exit(EXIT_SUCCESS);
}

void quitCheck(string input)
{
    if (input == "Q")
        quit();
}

void printSpace()
{
    cout << endl;
}

void printStat(string txt, double num)
{
    cout << txt << num << "      |" << endl;
}

void printLine()
{
    cout << "--------------------------" << endl;
}

void printLine(string input)
{
    cout << input << endl;
}

int getIntFromString(std::string str) {
    return stoi(str, nullptr, 10);
}

void invalidInput() {
    printLine("Invalid input. Please try again.");
}
