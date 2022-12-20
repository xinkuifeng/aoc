#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode * prev;
    ListNode * next;

    ListNode() : val(0), prev(nullptr), next(nullptr) {}
    ListNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};

void move_right(ListNode * node) {
    if (!node) {
        cout << "node is null" << endl;
        throw "panic";
    }

    ListNode * prev = node->prev;
    ListNode * next = node->next;
    if (!prev || !next) {
        cout << "The curr node (" << node->val << ")'s prev or next is null" << endl;
        throw "panic";
    }

    node->next = next->next;
    next->next->prev = node;

    node->prev = next;
    next->next = node;

    prev->next = next;
    next->prev = prev;
}

void move_left(ListNode * node) {
    if (!node) {
        cout << "node is null" << endl;
        throw "panic";
    }

    ListNode * prev = node->prev;
    ListNode * next = node->next;
    if (!prev || !next) {
        cout << "The curr node (" << node->val << ")'s prev or next is null" << endl;
        throw "panic";
    }

    node->prev = prev->prev;
    prev->prev->next = node;

    node->next = prev;
    prev->prev = node;

    prev->next = next;
    next->prev = prev;
}

void move(ListNode * node, int right) {
    if (right == 0) return;

    if (right > 0) {
        while (right--) {
            move_right(node);
        }
    } else {
        right = std::abs(right);
        while (right--) {
            move_left(node);
        }
    }
}

void print_list(ListNode * node, int size) {
    if (!node) return;

    ListNode * curr = node;
    while (size--) {
        cout << curr->val;
        if (size) cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
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

    ListNode * head = nullptr;
    ListNode * tail = nullptr;
    ListNode * curr = nullptr;
    ListNode * prev = nullptr;
    ListNode * zero = nullptr;
    vector<ListNode *> vec;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            int n = stoi(line);
            curr = new ListNode(n);
            if (!head) {
                head = curr;
            }
            if (!prev) {
                prev = curr;
            } else {
                prev->next = curr;
                curr->prev = prev;
                prev = curr;
            }
            vec.push_back(curr);
            if (n == 0) zero = curr;
        }
    }
    tail = curr;
    tail->next = head;
    head->prev = tail;

    int size = vec.size();
    print_list(head, size);
    int n = 10;
    long big = 811589153;
    while (n--) {
        for (int i = 0; i < vec.size(); ++i) {
            ListNode * node = vec[i];
            long x = (long)node->val * big;
            x %= (size - 1);
            move(node, x);
        }
    }
    print_list(head, size);

    curr = zero;
    long n1k = 0, n2k = 0, n3k = 0;
    for (int i = 0; i <= 3000; ++i) {
        if (i == 1000) n1k = (long)curr->val * big;
        if (i == 2000) n2k = (long)curr->val * big;
        if (i == 3000) n3k = (long)curr->val * big;
        curr = curr->next;
    }
    cout << "1000th: " << n1k << endl;
    cout << "2000th: " << n2k << endl;
    cout << "3000th: " << n3k << endl;

    cout << "ans: " << n1k + n2k + n3k << endl;
    return 0;
}
