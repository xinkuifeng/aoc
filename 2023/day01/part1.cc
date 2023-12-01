#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

    int sum = 0;
    while (!file.eof()) {
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            vector<int> v;
            for (const auto & c : line) {
                if (isdigit(c)) {
                    v.push_back(c - '0');
                }
            }
            int num = v.front() * 10 + v.back();
            sum += num;
        }
    }

    cout << "ans:" << sum << endl;

    return 0;
}
