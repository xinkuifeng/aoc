#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

// Guest - Host
// A: Rock
// B: Paper
// C: Scissors
unordered_map<string, int> g_rules = {
    {"AA", 3},
    {"AB", 6},
    {"AC", 0},
    {"BA", 0},
    {"BB", 3},
    {"BC", 6},
    {"CA", 6},
    {"CB", 0},
    {"CC", 3},
};

unordered_map<string, string> g_prediction = {
    {"AX", "AC"},
    {"AY", "AA"},
    {"AZ", "AB"},
    {"BX", "BA"},
    {"BY", "BB"},
    {"BZ", "BC"},
    {"CX", "CB"},
    {"CY", "CC"},
    {"CZ", "CA"},
};

int value(char c)
{
    return c - 'A' + 1;
}

string parse(string line) {
    stringstream ss(line);
    char a, b;
    ss >> a >> b;

    string str;
    str += a;
    str += b;
    return g_prediction.at(str);
}

int main(int argc, char ** argv)
{
    cout << "Hello, World!" << endl;

    if (argc != 2) {
        cout << "usage: ./a.out FILE_NAME" << endl;
        return -1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cout << "failed to open " << argv[1] << endl;
        return -1;
    }

    int score = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto str = parse(line);
            score += g_rules.at(str);
            score += value(str[1]);
        }
    }

    cout << "ans: " << score << endl;

    return 0;
}
