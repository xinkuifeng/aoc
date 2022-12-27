#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solve(string line) {
    vector<int> table(26, -1);

    int start = 0;
    int cnt = 0;
    for (int i = 0; i < line.size(); ++i) {
        char c = line[i];
        int idx = c - 'a';
        // this char is repeated
        if (table[idx] >= start) {
            // not good => restart
            start = table[idx] + 1;
            cnt = i - start;
        }
        table[idx] = i;
        ++cnt;
        if (cnt == 14) {
            break;
        }
    }
    return start + cnt;
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

    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            int pos = solve(line);
            cout << line << " -> " << pos << endl;
        }
    }

    return 0;
}
