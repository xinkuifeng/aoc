#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int value(char c)
{
    int score = 0;
    if (isupper(c)) {
        score += 26;
        c = tolower(c);
    }
    return c - 'a' + 1 + score;
}

int solve(string line) {
    string first = line.substr(0, line.size() / 2);
    string second = line.substr(line.size() / 2);
    unordered_set<char> seen(first.begin(), first.end());
    for (const auto & c : second) {
        if (seen.find(c) != seen.end()) {
            return value(c);
        }
    }
    cout << "cannot find repeated char." << endl;
    throw "panic!";
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

            score += solve(line);
        }
    }

    cout << "ans: " << score << endl;

    return 0;
}
