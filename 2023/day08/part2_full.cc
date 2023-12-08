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
    int inst_sz = inst.size();
    inst += inst;
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

    cout << "start positions: " << endl;
    for (const auto & node : start_pos) {
        cout << node << " = " << network[node] << endl;
    }

    vector<vector<int>> steps_of_nodes;
    for (int i = 0; i < start_pos.size(); ++i) {
        auto curr_pos = start_pos[i];
        unordered_set<string> visited;
        int step = 0;
        int idx = 0;
        vector<int> steps;
        string key = curr_pos + inst.substr(idx, inst_sz);
        while (visited.find(key) == visited.end()) {
            visited.insert(key);
            ++step;
            char c = inst[idx++];
            if (c == 'R') {
                curr_pos = network[curr_pos].right;
            } else {
                curr_pos = network[curr_pos].left;
            }
            if (end_pos.find(curr_pos) != end_pos.end()) {
                steps.push_back(step);
            }
            if (idx >= inst_sz) idx = 0;
            key = curr_pos + inst.substr(idx, inst_sz);
        }
        steps_of_nodes.push_back(steps);
    }

    for (int i = 0; i < steps_of_nodes.size(); ++i) {
        cout << start_pos[i] << ": ";
        for (auto n : steps_of_nodes[i]) {
            cout << n << ", ";
        }
        cout << endl;
    }

    unordered_set<long> prev(steps_of_nodes[0].begin(), steps_of_nodes[0].end());
    for (int i = 1; i < steps_of_nodes.size(); ++i) {
        auto & curr = steps_of_nodes[i];
        unordered_set<long> tmp;
        for (auto a : prev) {
            for (auto b : curr) {
                tmp.insert(lcm(a, b));
            }
        }
        swap(prev, tmp);
    }

    long ans = LONG_MAX;
    for (auto n : prev) {
        if (n < ans) ans = n;
    }
    cout << "ans:" << ans << endl;

    return 0;
}
