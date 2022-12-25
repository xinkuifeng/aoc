#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

long decode(string line) {
    long res = 0;
    for (const auto & c : line) {
        res *= 5;
        int n = 0;
        if (isdigit(c)) {
            n = c - '0';
        } else if (c == '=') {
            n = -2;
        } else if (c == '-') {
            n = -1;
        } else {
            cout << "unknown char " << c << endl;
            throw "panic!";
        }
        res += n;
    }
    return res;
}

string encode(long n) {
    stack<char> st;

    while (n > 0) {
        char c;
        auto m = n % 5;
        if (m <= 2) {
            c = '0' + m;
        } else {
            m = m - 5;
            if (m == -2) {
                c = '=';
            } else if (m == -1) {
                c = '-';
            } else {
                cout << "expect a negative number: " << m << endl;
                throw "panic!";
            }
        }
        st.push(c);
        n -= m;
        n /= 5;
    }

    string res;
    while (!st.empty()) {
        auto c = st.top();
        st.pop();

        res += c;
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

    ifstream file(argv[1]);
    if (!file) {
        cout << "failed to open " << argv[1] << endl;
        return -1;
    }

    long sum = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto n = decode(line);
            sum += n;
        }
    }

    cout << "ans: " << sum << endl;

    string res = encode(sum);
    cout << "ans (encoded): " << res << endl;

    return 0;
}
