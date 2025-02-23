#include <cstdio>
#include <iostream>
using namespace std;

struct Point {
    int x, y;
    Point() {}
    ///Point(int xx, int yy): x(xx), y(yy) {}
    Point(int xx, int yy) {
        x = xx;
        y = yy;
    }
    Point operator+(const Point &a) const {
        return Point(x + a.x, y + a.y);
    }
    int square_len() const {
        return x * x + y * y;
    }
};

istream& operator>>(istream &input_stream, Point &a) {
    input_stream >> a.x >> a.y;
    return input_stream;
}

ostream& operator<<(ostream &output_stream, Point &a) {
    output_stream << a.x << " " << a.y;
    return output_stream;
}

struct Line {
    int a, b, c;
    Line() {}
    Line(int aa, int bb, int cc): a(aa), b(bb), c(cc) {}
    Line(Point d, Point e) {
        a = d.y - e.y;
        b = e.x - d.x;
        c = -a * d.x - b * d.y;
    }
};

int main() {
    Point a;
    cin >> a;
    cout << a;
    return 0;
}
