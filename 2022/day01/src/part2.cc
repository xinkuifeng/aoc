#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

    vector<int> vec;
    while (!file.eof()) {
        int current = 0;
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            current += stoi(line);
        }
        vec.push_back(current);
    }

    sort(vec.begin(), vec.end(), std::greater<int>());
    int top3 = 0;
    for (int i = 0; i < vec.size() && i < 3; ++i) {
        top3 += vec[i];
    }

    cout << "ans: " << top3 << endl;

    return 0;
}
