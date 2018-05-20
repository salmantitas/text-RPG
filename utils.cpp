#include "utils.h"

using namespace std;

string formatInput()
{
    string input;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}

void quit()
{
    cout << "The Game Is Over";
    exit(EXIT_SUCCESS);
}

void quitCheck(string input)
{
    if (input == "Q")
        quit();
}

