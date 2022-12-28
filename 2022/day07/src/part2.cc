#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "AocUtils.h"

using namespace fxk;
using namespace std;

struct TreeNode {
    string name;
    size_t size;
    bool file;
    vector<TreeNode *> children;
    TreeNode * parent;

    TreeNode(string str, size_t n = 0, bool f = false) :
        name(str), size(n), file(f), parent(nullptr)
    {}
};

// full path -> node
unordered_map<string, TreeNode *> g_dirs;

string full_path(const vector<string> & dirs) {
    stringstream ss;
    for (const auto & dir : dirs) {
        ss << dir << "/";
    }
    return ss.str();
}

string full_path(TreeNode * node) {
    if (!node) return "";

    string res = full_path(node->parent);
    res += node->name + "/";
    return res;
}

std::ostream & operator<<(std::ostream & os, const TreeNode & node) {
    string pname;
    if (node.parent) {
        pname = full_path(node.parent);
    }
    bool is_dir = node.file == false;
    os << node.name << "(s:" << node.size << "; d:" << is_dir << "; p:" << pname << ")";
    return os;
}

bool exist(const unordered_map<string, TreeNode *> & table, const string & path) {
    return table.find(path) != table.end();
}

TreeNode * parse(const vector<string> & lines) {
    TreeNode * curr = new TreeNode("/");
    g_dirs["/"] = curr;
    vector<string> dirs;
    for (const auto & line : lines) {
        auto input = split(line, ' ');

        if (input[0] == "$") {
            const auto & cmd = input[1];
            if (cmd == "cd") {
                const auto & dir = input[2];
                if (dir == "/") {
                    curr = g_dirs.at(dir);
                    dirs.clear();
                    dirs.push_back(dir);
                } else if (dir == "..") {
                    dirs.pop_back();
                    curr = curr->parent;
                } else {
                    dirs.push_back(dir);
                    string cwd = full_path(dirs);
                    curr = g_dirs.at(cwd);
                }
            } else if (cmd == "ls") {
                // do nothing
            }
        } else {
            // make entries
            if (input[0] == "dir") {
                string path = full_path(dirs) + input[1] + "/";
                if (!exist(g_dirs, path)) {
                    TreeNode * node = new TreeNode(input[1]);
                    node->parent = curr;
                    curr->children.push_back(node);
                    g_dirs[path] = node;
                }
            } else {
                auto size = stol(input[0]);
                TreeNode * file = new TreeNode(input[1], size, true);
                file->parent = curr;
                curr->children.push_back(file);
            }
        }
    }

    return g_dirs.at("/");
}

void debug(TreeNode * root) {
    if (!root) return;

    int level = 0;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            auto node = q.front();
            q.pop();

            cout << "level " << level << ": " << *node << endl;

            for (auto & c : node->children) {
                q.push(c);
            }
        }
        ++level;
    }
}

size_t get_size(TreeNode * node) {
    if (!node) return 0;

    if (node->size) return node->size;

    size_t sum = 0;
    for (auto & ptr : node->children) {
        sum += get_size(ptr);
    }
    node->size = sum;
    return sum;
};

// returns the sizes of directories
vector<size_t> solve(TreeNode * root) {
    if (!root) return {};

    vector<size_t> res;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            auto node = q.front();
            q.pop();

            if (!node->file) {
                auto n = get_size(node);
                res.push_back(n);
            }

            for (auto & c : node->children) {
                q.push(c);
            }
        }
    }
    return res;
}

int main(int argc, char ** argv)
{
    cout << "Hello, World!" << endl;

    if (argc != 2) {
        cout << "usage: ./a.out FILE_NAME" << endl;
        return -1;
    }

    vector<string> lines;
    ifstream file(argv[1]);
    if (!file) {
        cout << "failed to open " << argv[1] << endl;
        return -1;
    }

    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            lines.push_back(line);
        }
    }

    TreeNode * root = parse(lines);
    auto sizes = solve(root);
    debug(root);

    size_t free = 70000000 - get_size(root);
    size_t need = 30000000 - free;

    vector<size_t> res;
    for (const auto & s : sizes) {
        if (s >= need) res.push_back(s);
    }
    sort(res.begin(), res.end());

    cout << "ans: " << res[0] << endl;

    return 0;
}
