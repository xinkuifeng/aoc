#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "AocUtils.h"

using namespace fxk;
using namespace std;

struct Item {
    int id;
    int init;

    Item(int i, int v) : id(i), init(v) {}
};

std::ostream & operator<<(std::ostream & os, const Item & item) {
    os << item.id << "(" << item.init << ")";
    return os;
}

struct Monkey {
    int id;
    deque<Item> items;
    char op;
    int x;
    int div;
    int next_if_true;
    int next_if_false;

    void display(std::ostream & os) const {
        os << "Monkey " << id << ": ";
        for (const auto & val : items) {
            os << val << " ";
        }
    }
};

std::ostream & operator<<(std::ostream & os, const Monkey & m) {
    m.display(os);
    return os;
}

Monkey * make_monkey(const vector<string> & lines) {
    static int cnt = 0;
    if (lines.empty()) return nullptr;

    Monkey * ptr = new Monkey();
    for (const auto & line : lines) {
        if (line.find("Monkey") != string::npos) {
            auto numbers = parse_int(line);
            ptr->id = numbers[0];
        } else if (line.find("Starting") != string::npos) {
            auto numbers = parse_int(line);
            for (const auto & n : numbers) {
                ptr->items.push_back(Item(cnt++, n));
            }
        } else if (line.find("Operation") != string::npos) {
            if (line.find("*") != string::npos) {
                ptr->op = '*';
            } else {
                ptr->op = '+';
            }
            auto numbers = parse_int(line);
            if (numbers.empty()) {
                ptr->x = 0;
            } else {
                ptr->x = numbers[0];
            }
        } else if (line.find("Test") != string::npos) {
            auto numbers = parse_int(line);
            ptr->div = numbers[0];
        } else if (line.find("true") != string::npos) {
            auto numbers = parse_int(line);
            ptr->next_if_true = numbers[0];
        } else if (line.find("false") != string::npos) {
            auto numbers = parse_int(line);
            ptr->next_if_false = numbers[0];
        }
    }
    return ptr;
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

    vector<Monkey *> monkeys;
    while (!file.eof()) {
        string line;
        vector<string> lines;
        while (getline(file, line)) {
            if (line.empty()) break;

            lines.push_back(line);
        }
        Monkey * ptr = make_monkey(lines);
        monkeys.push_back(ptr);
    }

    // init worry level
    vector<vector<int>> worry;
    for (auto m : monkeys) {
        for (const auto & item : m->items) {
            vector<int> w = vector<int>(monkeys.size(), item.init);
            worry.push_back(w);
        }
    }

    int round = 0;
    vector<long> cnt(monkeys.size(), 0);
    while (round < 10000) {
        ++round;

        for (auto src : monkeys) {
            while (!(src->items).empty()) {
                cnt[src->id]++;
                auto item = src->items.front();
                src->items.pop_front();
                auto & vec = worry[item.id];
                if (src->x != 0) {
                    switch (src->op) {
                        case '+':
                            for (auto & x : vec) {
                                x += src->x;
                            }
                            break;
                        case '*':
                            for (auto & x : vec) {
                                x *= src->x;
                            }
                            break;
                        default: break;
                    }
                } else {
                    for (auto & x : vec) {
                        x *= x;
                    }
                }
                // manage the worry level
                for (int i = 0; i < monkeys.size(); ++i) {
                    vec[i] %= monkeys[i]->div;
                }
                auto dst = (vec[src->id] % src->div) ?
                    monkeys[src->next_if_false] : monkeys[src->next_if_true];
                dst->items.push_back(item);
            }
        }
    }

    sort(cnt.begin(), cnt.end(), std::greater<long>());
    cout << "ans: " << cnt[0] * cnt[1] << endl;

    return 0;
}
