class ConvexHullTrick {
private:
    struct Line {
        long long a, b;

        long long get(long long x) {
            return a * x + b;
        }
    };

    vector<Line> hull;

    bool isBad(vector<Line>::iterator curr) {
        vector<Line>::iterator prev = curr, next = curr;
        --prev, ++next;
        const Line& p = *prev, c = *curr, n = *next;
        return (c.b - n.b) * (c.a - p.a) <= (p.b - c.b) * (n.a - c.a);
    }

public:
    ConvexHullTrick() : hull() {}

    void clear() {
        hull.clear();
    }

    void addLine(long long a, long long b) {
        hull.push_back((Line){a, b});
        while (hull.size() > 2 && isBad(hull.end() - 2))
            hull.erase(hull.end() - 2);
    }

    long long query(long long x) {
        size_t l = 0, r = hull.size() - 1;
        while (l < r) {
            size_t m = (l + r) / 2;
            if (hull[m].get(x) <= hull[m + 1].get(x))
                l = m + 1;
            else
                r = m;
        }
        return hull[l].get(x);
    }

    long long fastQuery(long long x) {
        static size_t it = 0;
		it = min(it, hull.size() - 1);
		while (it + 1 < hull.size()) {
			if (hull[it].get(x) > hull[it + 1].get(x))
				break;
			it++;
		}
		while (it > 0) {
			if (hull[it].get(x) > hull[it - 1].get(x))
				break;
			it--;
		}
		return hull[it].get(x);
	}
};
