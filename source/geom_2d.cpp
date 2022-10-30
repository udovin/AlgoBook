const double PI = acos(-1);
const double EPS = 1e-8;

struct Vec2 {
	double x, y;
	bool operator<(const Vec2& v) const { return pair(x, y) < pair(v.x, v.y); }
	Vec2 operator+(const Vec2& v) const { return {x + v.x, y + v.y}; }
	Vec2 operator-(const Vec2& v) const { return {x - v.x, y - v.y}; }
	Vec2 operator*(double a) const { return {x * a, y * a}; }
	double operator*(const Vec2& v) const { return x * v.x + y * v.y; }
	double operator%(const Vec2& v) const { return x * v.y - y * v.x; }
	double lenSq() const { return x * x + y * y; }
	double len() const { return sqrt(lenSq()); }
};

istream& operator>>(istream& is, Vec2& v) { return is >> v.x >> v.y; }
ostream& operator<<(ostream& os, const Vec2& v) {
	return os << v.x << ' ' << v.y;
}

vector<int> convexHull(const vector<Vec2>& a) { // clockwise
	vector<int> p(a.size());
	int s = 0;
	for (int i = 0; i < p.size(); i++) {
		p[i] = i;
		if (a[i] < a[s]) {
			s = i;
		}
	}
	sort(p.begin(), p.end(), [&](int x, int y) {
		if (x == s || y == s) {
			return x == s;
		}
		return (a[x] - a[s]) % (a[y] - a[s]) < 0;
	});
	s = p[0];
	vector<int> h(1, p[0]);
	for (int i = 1; i < p.size(); i++) {
		while (h.size() > 1) {
			int x = h[h.size() - 1];
			int y = h[h.size() - 2];
			if ((a[x] - a[y]) % (a[p[i]] - a[x]) < 0) {
				break;
			}
			h.pop_back();
		}
		h.push_back(p[i]);
	}
	while (h.size() > 1) {
		int x = h[h.size() - 1];
		int y = h[h.size() - 2];
		if ((a[x] - a[y]) % (a[p[0]] - a[x]) < 0) {
			break;
		}
		h.pop_back();
	}
	return h;
}

struct Line { // a -> b
	Vec2 a, b;
	bool contains(const Vec2& v) const { return abs((b - a) % (v - a)) < EPS; }
	bool segmentContains(const Vec2& v) const {
		return contains(v) &&
			(b - a) * (v - a) > -EPS && (a - b) * (v - b) > -EPS;
	}
};

optional<Vec2> intersect(const Line& a, const Line& b) {
	auto dax = a.a.x - a.b.x;
	auto day = a.a.y - a.b.y;
	auto dbx = b.a.x - b.b.x;
	auto dby = b.a.y - b.b.y;
	auto l = dax * dby - day * dbx;
	if (abs(l) < EPS) {
		return {};
	}
	auto da = a.a % a.b;
	auto db = b.a % b.b;
	auto x = da * dbx - db * dax;
	auto y = da * dby - db * day;
	return Vec2{x / l, y / l};
}

struct Circle : public Vec2 {
	double r;
	double area() const { return PI * r * r; }
	// d - distance from center to chord
	double segmentArea(double d) {
		if (d < 0) {
			return area() - segmentArea(-d);
		}
		if (d >= r) {
			return 0;
		}
		double l = sqrt(r * r - d * d);
		double s = asin(l / r) * r * r;
		return s - l * d;
	}
	// p - position of intersection of two perpendicular chords
	double segmentOverlapArea(Vec2 p) {
		if (p.x < 0) {
			p.x = -p.x;
			return area() - segmentArea(-p.y) - segmentOverlapArea(p);
		}
		if (p.y < 0) {
			p.y = -p.y;
			return area() - segmentArea(-p.x) - segmentOverlapArea(p);
		}
		if (p.lenSq() >= r * r) {
			return 0;
		}
		double rx = sqrt(r * r - p.y * p.y);
		double ry = sqrt(r * r - p.x * p.x);
		double s = abs(p.x * p.y - p.y * rx) + abs(p.x * ry - p.y * p.x);
		return (abs(acos(p.x / r) - asin(p.y / r)) * r * r - s) / 2;
	}
};

struct Sphere {
    double x, y, z;
	double r;
	double area() const { return 4 * PI * r * r; }
	double volume() const { return area() * r / 3; }
    // d - distance from center to chord
    double segmentVolume(double d) const {
        if (d > 0) {
            return volume() - segmentVolume(-d);
        }
        auto h = r + d;
        return PI * h * h * (r - h / 3);
    }
};
