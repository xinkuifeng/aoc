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

struct Segment {
    int low;
    int high;

    Segment() : low(0), high(0) {}
    Segment(int lo, int hi) : low(lo), high(hi) {}

    bool valid() const { return low <= high; }

    void display(std::ostream & os) const {
        os << "(" << low << "," << high << ")";
    }
};

std::ostream & operator<<(std::ostream & os, const Segment & s) {
    s.display(os);
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

struct SpaceInfo {
    Segment x;
    Segment y;
    Segment z;

    SpaceInfo(Segment i, Segment j, Segment k) : x(i), y(j), z(k) {}
};

// add outside airs to the rocks
void dfs(
    const unordered_set<Point> & space,
    const SpaceInfo & info,
    unordered_set<Point> & visited,
    const Point & curr)
{
    if (curr.x < info.x.low || curr.x > info.x.high ||
        curr.y < info.y.low || curr.y > info.y.high ||
        curr.z < info.z.low || curr.z > info.z.high) {
        return;
    }

    if (visited.find(curr) != visited.end()) return;

    visited.insert(curr);

    for (const auto & d : g_directions) {
        Point next = curr + d;
        dfs(space, info, visited, next);
    }
}

bool is_external(const SpaceInfo & info, const Point & p)
{
    return p.x <= info.x.low || p.x >= info.x.high ||
        p.y <= info.y.low || p.y >= info.y.high ||
        p.z <= info.z.low || p.z >= info.z.high;
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
        string line;
        while (getline(file, line)) {
            if (line.empty()) break;

            auto p = parse(line);
            points.push_back(p);
        }
    }

    Segment x_axix(INT_MAX, INT_MIN);
    Segment y_axix(INT_MAX, INT_MIN);
    Segment z_axix(INT_MAX, INT_MIN);
    for (const auto & p : points) {
        cout << p << endl;
        x_axix.low = std::min(x_axix.low, p.x);
        x_axix.high = std::max(x_axix.high, p.x);
        y_axix.low = std::min(y_axix.low, p.y);
        y_axix.high = std::max(y_axix.high, p.y);
        z_axix.low = std::min(z_axix.low, p.z);
        z_axix.high = std::max(z_axix.high, p.z);
    }

    unordered_set<Point> search_space;
    SpaceInfo info(x_axix, y_axix, z_axix);
    unordered_set<Point> air;
    for (int i = x_axix.low; i <= x_axix.high; ++i) {
        for (int j = y_axix.low; j <= y_axix.high; ++j) {
            for (int k = z_axix.low; k <= z_axix.high; ++k) {
                Point p(i, j, k);
                search_space.insert(p);
                if (is_external(info, p)) {
                    air.insert(p);
                }
            }
        }
    }

    unordered_set<Point> limits(points.begin(), points.end());
    for (const auto & p : air) {
        dfs(search_space, info, limits, p);
    }

    unordered_set<Point> inner_air;
    for (const auto & p : search_space) {
        if (limits.find(p) == limits.end()) {
            inner_air.insert(p);
        }
    }

    int initial = surface_p1(points);
    vector<Point> pockets(inner_air.begin(), inner_air.end());
    int modifier = surface_p1(pockets);
    cout << "initial: " << initial << endl;
    cout << "modifier: " << modifier << endl;
    cout << "ans: " << initial - modifier << endl;
    return 0;
}
