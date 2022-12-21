#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    char op;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
    string name;
    string lname;
    string rname;

    TreeNode() : val(0), op(0), left(nullptr), right(nullptr), parent(nullptr),
        name(""), lname(""), rname("")
    {}
};

std::ostream & operator<<(std::ostream & os, const TreeNode & node) {
    os << "name:" << node.name << "; val:" << node.val << "; op:" << node.op << endl;
    os << "l:" << node.lname << "; r:" << node.rname << endl;
    return os;
}

TreeNode * parse(string line) {
    auto pos = line.find(":");
    string name = line.substr(0, pos);
    line = line.substr(pos + 2);
    int val = 0;
    string lname, rname;
    char op = 0;
    TreeNode * node = new TreeNode();
    node->name = name;
    if (line.size() < 10) {
        val = stoi(line);
        node->val = val;
    } else {
        stringstream ss(line);

        ss >> lname >> op >> rname;
        node->lname = lname;
        node->rname = rname;
        node->op = op;
    }
    return node;
}

long calculate(TreeNode * node) {
    if (!node) {
        cout << "node is null." << endl;
        throw "panic!";
    }

    if (node->op == 0) {
        return node->val;
    }

    long left = calculate(node->left);
    long right = calculate(node->right);
    switch (node->op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        default: break;
    }

    cout << "unknown op " << node->op << endl;
    throw "panic!";
}

long reverse_calculate(TreeNode * node, long target, unordered_set<string> & st) {
    if (!node) {
        cout << "node is null." << endl;
        throw "panic!";
    }

    st.erase(node->name);
    if (st.empty()) {
        if (node->name == "humn") return target;
        cout << "the last unknown node is: " << node->name << endl;
        throw "panic!";
    }

    if (st.find(node->lname) != st.end() && st.find(node->rname) != st.end()) {
        cout << "both left subtree and right subtree are unknown." << endl;
        throw "panic!";
    }
    if (st.find(node->lname) == st.end() && st.find(node->rname) == st.end()) {
        cout << "both left subtree and right subtree are known." << endl;
        throw "panic!";
    }

    TreeNode * next = nullptr;
    if (st.find(node->lname) == st.end()) {
        // left subtree is well known
        long left = calculate(node->left);
        // go right
        next = node->right;
        st.erase(node->right->name);
        switch (node->op) {
            case '+': return reverse_calculate(next, target - left, st);
            case '-': return reverse_calculate(next, left - target, st);
            case '*': return reverse_calculate(next, target / left, st);
            case '/': return reverse_calculate(next, left / target, st);
            default: break;
        }
    } else {
        long right = calculate(node->right);
        // go left
        next = node->left;
        st.erase(node->left->name);
        switch (node->op) {
            case '+': return reverse_calculate(next, target - right, st);
            case '-': return reverse_calculate(next, right + target, st);
            case '*': return reverse_calculate(next, target / right, st);
            case '/': return reverse_calculate(next, right * target, st);
            default: break;
        }
    }

    cout << "unknown op " << node->op << endl;
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

    vector<TreeNode *> vec;
    unordered_map<string, TreeNode *> dict;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto ptr = parse(line);
            if (ptr->name == "humn") {
                ptr->val = -1;
            }
            dict[ptr->name] = ptr;
            vec.push_back(ptr);
        }
    }

    for (auto & p : vec) {
        if (!p->lname.empty()) {
            p->left = dict.at(p->lname);
            p->left->parent = p;
        }
        if (!p->rname.empty()) {
            p->right = dict.at(p->rname);
            p->right->parent = p;
        }
    }

    unordered_set<string> unknown;
    TreeNode * node = dict.at("humn");
    while (node) {
        unknown.insert(node->name);
        node = node->parent;
    }

    TreeNode * root = dict.at("root");
    unknown.erase("root");
    long ans = 0;
    if (unknown.find(root->lname) != unknown.end()) {
        long right = calculate(root->right);
        ans = reverse_calculate(root->left, right, unknown);
    } else {
        long left = calculate(root->left);
        ans = reverse_calculate(root->right, left, unknown);
    }
    cout << "ans: " << ans << endl;
    return 0;
}
