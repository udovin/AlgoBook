class LinkCutTree {
private:
	struct Vertex {
		int left, right, parent;
		bool revert;
		int size;
		int64_t value, result, delta;

		Vertex()
			: left(-1), right(-1), parent(-1), revert()
			, size(1), value(), result(), delta() {}
	};

	vector<Vertex> t;

	bool isRoot(int x) const {
		int p = t[x].parent;
		return p == -1 || (t[p].left != x && t[p].right != x);
	}

	int64_t getValue(int x) const {
		return t[x].value + t[x].delta;
	}

	int64_t getResult(int x) const {
		return t[x].result + t[x].delta * t[x].size;
	}

	void push(int x) {
		if (t[x].revert) {
			if (t[x].left != -1)
				t[t[x].left].revert = !t[t[x].left].revert;
			if (t[x].right != -1)
				t[t[x].right].revert = !t[t[x].right].revert;
			swap(t[x].left, t[x].right);
			t[x].revert = false;
		}
		t[x].value = getValue(x);
		t[x].result = getResult(x);
		if (t[x].left != -1)
			t[t[x].left].delta += t[x].delta;
		if (t[x].right != -1)
			t[t[x].right].delta += t[x].delta;
		t[x].delta = 0;
	}

	void keep(int x) {
		t[x].size = 1;
		t[x].result = getValue(x);
		if (t[x].left != -1) {
			t[x].size += t[t[x].left].size;
			t[x].result += getResult(t[x].left);
		}
		if (t[x].right != -1) {
			t[x].size += t[t[x].right].size;
			t[x].result += getResult(t[x].right);
		}
	}

	void rotate(int x) {
		int p = t[x].parent;
		int g = t[p].parent;
		push(p), push(x);
		if (g != -1) {
			if (t[g].left == p)
				t[g].left = x;
			else if (t[g].right == p)
				t[g].right = x;
		}
		t[x].parent = g;
		if (t[p].left == x) {
			t[p].left = t[x].right;
			if (t[p].left != -1)
				t[t[p].left].parent = p;
			t[x].right = p;
		} else {
			t[p].right = t[x].left;
			if (t[p].right != -1)
				t[t[p].right].parent = p;
			t[x].left = p;
		}
		t[p].parent = x;
		keep(p), keep(x);
	}

	void splay(int x) {
		while (!isRoot(x)) {
			int p = t[x].parent;
			if (!isRoot(p)) {
				int g = t[p].parent;
				bool zigzig = (x == t[p].left) == (p == t[g].left);
				rotate(zigzig ? p : x);
			}
			rotate(x);
		}
		push(x);
	}

	int expose(int x) {
		int c = -1;
		for (int y = x; y != -1; y = t[y].parent) {
			splay(y);
			t[y].right = c;
			keep(y);
			c = y;
		}
		splay(x);
		return c;
	}

public:
	LinkCutTree(int n) : t(n) {}

	void evert(int x) {
		expose(x);
		t[x].revert = !t[x].revert;
	}

	int root(int x) {
		expose(x);
		while (t[x].left != -1) {
			x = t[x].left;
			push(x);
		}
		expose(x);
		return x;
	}

	int parent(int x) {
		expose(x);
		if (t[x].left == -1)
			return -1;
		x = t[x].left;
		push(x);
		while (t[x].right != -1) {
			x = t[x].right;
			push(x);
		}
		return x;
	}

	bool path(int x, int y) {
		if (x == y)
			return true;
		expose(y), expose(x);
		return t[y].parent != -1;
	}

	void link(int x, int y) {
		if (path(x, y))
			return;
		evert(x);
		t[x].parent = y;
	}

	void cut(int x) {
		expose(x);
		if (t[x].left == -1)
			return;
		t[t[x].left].parent = -1;
		t[x].left = -1;
	}

	int lca(int x, int y) {
		if (!path(x, y))
			return -1;
		expose(x);
		return expose(y);
	}

	int depth(int x) {
		expose(x);
		if (t[x].left == -1)
			return 0;
		return t[t[x].left].size;
	}

	int distance(int x, int y) {
		int l = lca(x, y);
		if (l == -1)
			return -1;
		return depth(y) + depth(x) - depth(l) * 2;
	}

	int64_t query(int x, int y) {
		if (!path(x, y))
			return 0;
		evert(x), expose(y);
		return t[y].result;
	}

	void update(int x, int y, int64_t value) {
		if (!path(x, y))
			return;
		evert(x), expose(y);
		t[y].delta += value;
	}
};
