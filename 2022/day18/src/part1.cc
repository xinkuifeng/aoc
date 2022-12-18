#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
    int z;

    Point(int a = 0, int b = 0, int c = 0) : x(a), y(b), z(c) {}

    Point & operator+=(const Point & other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Point & operator-=(const Point & other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    bool operator==(const Point & other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Point & other) const {
        return x != other.x || y != other.y || z != other.z;
    }

    void display(std::ostream & os) const {
        os << "(" << x << "," << y << "," << z << ")";
    }
};

Point operator+(const Point & p1, const Point & p2) {
    return Point(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

Point operator-(const Point & p1, const Point & p2) {
    return Point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

std::ostream & operator<<(std::ostream & os, const Point & p) {
    p.display(os);
    return os;
}

namespace std {
    template <> struct hash<Point> {
        inline size_t operator()(const Point & p) const {
            std::hash<int> int_hasher;
            return int_hasher(p.x) ^ int_hasher(p.y) ^ int_hasher(p.z);
        }
    };
}

Point parse(string line) {
    int x, y, z;
    char c, d;

    stringstream ss(line);
    ss >> x >> c >> y >> d >> z;
    return Point(x, y, z);
}

const vector<Point> g_directions = {
    Point(1, 0, 0),
    Point(-1, 0, 0),
    Point(0, 1, 0),
    Point(0, -1, 0),
    Point(0, 0, 1),
    Point(0, 0, -1),
};

int surface_p1(const vector<Point> & points) {
    int ans = points.size() * 6;

    unordered_set<Point> st(points.begin(), points.end());
    for (const auto & p : points) {
        for (const auto & d : g_directions) {
            Point tmp = p + d;
            if (st.find(tmp) != st.end()) {
                ans -= 1;
            }
        }
    }

    return ans;
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

    vector<Point> points;
    while (!file.eof()) {
        string line = "";
        while (getline(file, line)) {
            if (line == "") break;

            auto p = parse(line);
            points.push_back(p);
        }
    }

    for (const auto & p : points) {
        cout << p << endl;
    }

    int ans = surface_p1(points);

    cout << "ans: " << ans << endl;
    return 0;
}
