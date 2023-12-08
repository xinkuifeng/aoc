#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

struct Pair {
    string left;
    string right;

    Pair() : left(""), right("") {}
    Pair(string l, string r) : left(l), right(r) {}

    void display(std::ostream & os) const {
        os << "(" << left << "," << right << ")";
    }
};

std::ostream & operator<<(std::ostream & os, const Pair & p) {
    p.display(os);
    return os;
}

int main(int argc, char ** argv)
{
    if (argc != 2) {
        cout << "usage: ./a.out FILE_NAME" << endl;
        return -1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cout << "failed to open " << argv[1] << endl;
        return -1;
    }

    string inst;
    getline(file, inst);
    unordered_map<string, Pair> network;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            vector<string> vs;
            regex r(R"(\w{3})");
            smatch sm;
            while (regex_search(line, sm, r))
            {
                vs.push_back(sm.str());
                line = sm.suffix();
            }

            network[vs[0]] = Pair(vs[1], vs[2]);
        }
    }

    int step = 0;
    int idx = 0;
    string current = "AAA";
    while (current != "ZZZ") {
        ++step;

        char c = inst[idx++];
        if (c == 'R') {
            current = network[current].right;
        } else {
            current = network[current].left;
        }
        if (idx >= inst.size()) idx = 0;
    }

    cout << "ans:" << step << endl;

    return 0;
}
