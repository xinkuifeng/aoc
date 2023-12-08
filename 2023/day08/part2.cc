#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>
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

long gcd(long a, long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long lcm(long a, long b) {
    return (a * b) / gcd(a, b);
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
    vector<string> start_pos;
    unordered_set<string> end_pos;
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
            if (vs[0][2] == 'A') {
                start_pos.push_back(vs[0]);
            } else if (vs[0][2] == 'Z') {
                end_pos.insert(vs[0]);
            }
        }
    }

    vector<int> steps;
    for (const auto & s : start_pos) {
        int step = 0;
        auto curr = s;
        int idx = 0;
        while (end_pos.find(curr) == end_pos.end()) {
            ++step;
            char c = inst[idx++];
            if (c == 'R') {
                curr = network[curr].right;
            } else {
                curr = network[curr].left;
            }
            if (idx >= inst.size()) idx = 0;
        }
        steps.push_back(step);
    }

    long res = 1;
    for (int i = 0; i < steps.size(); ++i) {
        res = lcm(res, steps[i]);
    }
    cout << "ans:" << res << endl;

    return 0;
}
