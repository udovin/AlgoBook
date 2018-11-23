class DynamicConvexHullTrick {
private:
	struct Line {
		long long a, b;
		bool isQuery;
		mutable set<Line>::iterator prev, next;
		const set<Line>* root;

		bool operator<(const Line &line) const {
			if (!line.isQuery)
				return a < line.a;
			if (next == root->end())
				return false;
			return b - next->b < line.a * (next->a - a);
		}
	};

	set<Line> hull;

	bool isBad(set<Line>::iterator curr) {
		set<Line>::iterator prev = curr->prev, next = curr->next;
		if (prev == hull.end() || next == hull.end())
			return false;
		const Line& p = *prev, c = *curr, n = *next;
		return (c.b - n.b) * (c.a - p.a) <= (p.b - c.b) * (n.a - c.a);
	}

	void removeLine(set<Line>::iterator curr) {
		set<Line>::iterator prev = curr->prev, next = curr->next;
		if (prev != hull.end())
			prev->next = curr->next;
		if (next != hull.end())
			next->prev = curr->prev;
		hull.erase(curr);
	}

public:
	DynamicConvexHullTrick() : hull() {}

	void add(long long a, long long b) {
		Line line = (Line){a, b, false, hull.end(), hull.end(), &hull};
		set<Line>::iterator curr = hull.find(line);
		if (curr != hull.end()) {
			if (b <= curr->b)
				return;
			removeLine(curr);
		}
		curr = hull.insert(line).first;
		set<Line>::iterator prev = curr, next = curr;
		if (++next != hull.end())
			curr->next = next, next->prev = curr;
		if (prev-- != hull.begin())
			curr->prev = prev, prev->next = curr;
		if (isBad(curr)) {
			removeLine(curr);
			return;
		}
		while (curr->next != hull.end() && isBad(curr->next))
			removeLine(curr->next);
		while (curr->prev != hull.end() && isBad(curr->prev))
			removeLine(curr->prev);
	}

	long long get(long long x) const {
		Line query = (Line){x, 0, true, hull.end(), hull.end(), &hull};
		Line line = *hull.lower_bound(query);
		return line.a * x + line.b;
	}

	void clear() {
		hull.clear();
	}
};
