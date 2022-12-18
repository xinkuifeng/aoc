#include <fstream>
#include <iostream>
#include <string>

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

    int max = 0;
    while (!file.eof()) {
        int current = 0;
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            current += stoi(line);
        }
        max = std::max(max, current);
    }

    cout << "ans: " << max << endl;

    return 0;
}
