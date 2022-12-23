#ifndef FXK_POINT_H_
#define FXK_POINT_H_

#include <functional>
#include <iostream>

namespace fxk {

struct Point {
    int x;
    int y;

    Point() : x(0), y(0) {}
    Point(int m, int n) : x(m), y(n) {}

    Point & operator+=(const Point & other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point & operator-=(const Point & other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    bool operator==(const Point & other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point & other) const {
        return x != other.x || y != other.y;
    }

    void display(std::ostream & os) const {
        os << "(" << x << "," << y << ")";
    }
};

Point operator+(const Point & p1, const Point & p2) {
    return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator-(const Point & p1, const Point & p2) {
    return Point(p1.x - p2.x, p1.y - p2.y);
}

std::ostream & operator<<(std::ostream & os, const Point & p) {
    p.display(os);
    return os;
}

}

namespace std {
    template <> struct hash<fxk::Point> {
        inline size_t operator()(const fxk::Point & p) const {
            std::hash<int> int_hasher;
            return int_hasher(p.x) ^ int_hasher(p.y);
        }
    };
}

#endif
