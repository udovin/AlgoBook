#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <cassert>
#include <iostream>
#include <optional>
using namespace std;

#include <geom_2d.cpp>

void testVec2() {
    assert((Vec2{1, 0} % Vec2{0, 1} == 1));
    assert((Vec2{0, 1} % Vec2{1, 0} == -1));
    assert((Vec2{1, 1} % Vec2{1, 1} == 0));
    assert((Vec2{1, 1} % Vec2{-1, -1} == 0));
    assert((Vec2{1, 1} % Vec2{-1, 1} > 1));
}

void testLine() {
    for (int i = -10; i <= 10; i++) {
        assert((Line{{1, 1}, {5, 5}}.contains({double(i), double(i)})));
        assert(i < 1 || i > 5 || (Line{{1, 1}, {5, 5}}.segmentContains({double(i), double(i)})));
    }
    mt19937 mt;
	uniform_int_distribution<int> gen(-100, 100);
    for (int i = 0; i < 1000000; i++) {
        Line a{Vec2{double(gen(mt)), double(gen(mt))}, Vec2{double(gen(mt)), double(gen(mt))}};
        Line b{Vec2{double(gen(mt)), double(gen(mt))}, Vec2{double(gen(mt)), double(gen(mt))}};
        if ((a.b - a.a) % (b.b - b.a) == 0) {
            continue;
        }
        auto x = intersect(a, b);
        assert(x);
        assert(a.contains(*x));
        assert(b.contains(*x));
    }
}

void testConvexHull() {
    const int n = 5000;
    const int w = 50000;
    mt19937 mt;
	uniform_int_distribution<int> gen(-w, w);
    vector<Vec2> poly;
    for (int i = 0; i < n; i++) {
        poly.push_back(Vec2{double(gen(mt)), double(gen(mt))});
    }
    auto p = convexHull(poly);
    assert(p.size() >= 3);
    for (int i = 0; i < p.size(); i++) {
        assert((poly[p[(i + 1) % p.size()]] - poly[p[i]]) % (poly[p[(i + 2) % p.size()]] - poly[p[i]]) < 0);
    }
}

int main() {
    testVec2();
	testConvexHull();
    testLine();
	return 0;
}
