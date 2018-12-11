class DynamicConvexHullTrick {
private:
	struct Line {
		long long a, b;
		mutable set<Line>::iterator next;
		const set<Line>* root;

		bool operator<(const Line& line) const {
			if (line.root != nullptr)
				return a < line.a;
			if (root == nullptr || next == root->end())
				return false;
			return b - next->b < line.a * (next->a - a);
		}
	};

	set<Line> hull;

	bool isBad(set<Line>::iterator curr) {
		set<Line>::iterator prev = curr, next = curr->next;
		if (next == hull.end())
			return false;
		const Line& p = *--prev, c = *curr, n = *next;
		return (c.b - n.b) * (long double)(c.a - p.a)
			<= (p.b - c.b) * (long double)(n.a - c.a);
	}

	void removeLine(set<Line>::iterator curr) {
		set<Line>::iterator prev = curr, next = curr->next;
		if (prev != hull.begin())
			(--prev)->next = curr->next;
		hull.erase(curr);
	}

public:
	DynamicConvexHullTrick() : hull() {}

	void add(long long a, long long b) {
		Line line = (Line){a, b, hull.end(), &hull};
		set<Line>::iterator curr = hull.find(line);
		if (curr != hull.end()) {
			if (b <= curr->b)
				return;
			removeLine(curr);
		}
		curr = hull.insert(line).first;
		set<Line>::iterator prev = curr, next = curr;
		if (++next != hull.end())
			curr->next = next;
		if (prev != hull.begin()) {
			if (isBad(curr)) {
				removeLine(curr);
				return;
			}
			(--prev)->next = curr;
		}
		while (curr->next != hull.end() && isBad(curr->next))
			removeLine(curr->next);
		while (prev-- != hull.begin() && isBad(prev->next))
			removeLine(prev->next);
	}

	long long get(long long x) const {
		Line query = (Line){x, 0, hull.end(), nullptr};
		const Line& line = *hull.lower_bound(query);
		return line.a * x + line.b;
	}

	void clear() {
		hull.clear();
	}
};
