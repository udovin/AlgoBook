const double PI = acos(-1);

struct Vec2 {
	int64_t x, y;

	bool operator<(const Vec2& o) const {
		return pair(x, y) < make_pair(o.x, o.y);
	}

	Vec2 operator+(const Vec2& v) const {
		return {x + v.x, y + v.y};
	}

	Vec2 operator-(const Vec2& v) const {
		return {x - v.x, y - v.y};
	}

	Vec2 operator*(int64_t a) const {
		return {x * a, y * a};
	}

	int64_t operator*(const Vec2& v) const {
		return x * v.x + y * v.y;
	}

	int64_t operator%(const Vec2& v) const {
		return x * v.y - y * v.x;
	}

	int64_t lenSq() const {
		return x * x + y * y;
	}
};

vector<int> convexHull(const vector<Vec2>& a) {
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

struct Line {
	int64_t a, b, c;
};

Line getLine(const Vec2& a, const Vec2& b) {
	Line c;
	c.a = b.y - a.y;
	c.b = a.x - b.x;
	c.c = -(c.a * a.x + c.b * a.y);
	return c;
}

struct Circle : public Vec2 {
	int64_t r;

	double area() const {
		return PI * r * r;
	}

	// d - distance from center to chord
	double segmentArea(int64_t d) {
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
		return (abs(acos(double(p.x) / r) - asin(double(p.y) / r)) * r * r - s) / 2;
	}
};
