#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

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

int solve(const vector<string> lines) {
    if (lines.size() < 3) {
        cout << "not enough lines: " << lines.size() << endl;
        throw "panic";
    }
    unordered_set<char> first(lines[0].begin(), lines[0].end());
    unordered_set<char> second(lines[1].begin(), lines[1].end());
    for (const auto & c : lines[2]) {
        if (first.find(c) != first.end() && second.find(c) != second.end()) {
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
        vector<string> vec;
        while (getline(file, line)) {
            if (line.empty()) break;

            vec.push_back(line);
            if (vec.size() == 3) {
                score += solve(vec);
                vec.clear();
            }
        }
    }

    cout << "ans: " << score << endl;

    return 0;
}
