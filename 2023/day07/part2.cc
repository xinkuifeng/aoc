#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const vector<char> order = {
    'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'
};

int get_idx(const char & c) {
    for (int i = 0; i < order.size(); ++i) {
        if (c == order[i]) {
            return i;
        }
    }
    return INT_MAX;
}

int compute_type(const unordered_map<char, int> & m) {
    int pairs = 0;
    int j = 0;
    int max = 0;
    for (const auto & p : m) {
        if (p.first == 'J') {
            j = p.second;
            continue;
        }
        if (p.second == 2) {
            ++pairs;
        }
        if (p.second > max) {
            max = p.second;
        }
    }
    if (max + j > 3) return max + j + 1;
    if (max + j < 3) return pairs + j;
    if (j == 0) return max + pairs;
    return max + j + std::max(0, pairs - 1);
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

    using pair_t = std::pair<int, string>;
    auto rule = [](const pair_t & p1, const pair_t & p2) {
        if (p1.first != p2.first) {
            return p1.first > p2.first;
        } else {
            const auto & str1 = p1.second;
            const auto & str2 = p2.second;
            for (int i = 0; i < str1.size(); ++i) {
                const auto & c1 = str1[i];
                const auto & c2 = str2[i];
                if (c1 != c2) {
                    return get_idx(c1) < get_idx(c2);
                }
            }
            throw runtime_error("Error! Two cards are the same.");
            return true;
        }
    };

    int sum = 0;
    unordered_map<string, int> hands;
    priority_queue<pair_t, vector<pair_t>, decltype(rule)> pq(rule);
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto pos = line.find(" ");
            auto cards = line.substr(0, pos);
            auto bid = line.substr(pos + 1);
            hands[cards] = stoi(bid);
            unordered_map<char, int> m;
            for (const auto & c : cards) {
                ++m[c];
            }
            int prio = compute_type(m);
            pq.push({prio, cards});
        }
    }

    int rank = 0;
    while (!pq.empty()) {
        ++rank;
        auto p = pq.top();
        pq.pop();
        int bid = hands[p.second];
        sum += rank * hands[p.second];
    }

    cout << "ans:" << sum << endl;

    return 0;
}
