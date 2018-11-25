class LinkCutTree {
private:
	struct Node {
		int left, right, parent;
		int size;
		bool revert;
		long long nodeValue;
		long long value;
		long long delta;

		Node()
			: left(-1), right(-1), parent(-1), revert()
			, size(1), nodeValue(), value(), delta() {}
	};

	vector<Node> t;

	bool isRoot(int x) const {
		int p = t[x].parent;
		return p == -1 || (t[p].left != x && t[p].right != x);
	}

	int getSize(int x) const {
		return x == -1 ? 0 : t[x].size;
	}

	long long getNodeValue(int x) const {
		if (x == -1)
			return 0;
		return t[x].nodeValue + t[x].delta;
	}

	long long getValue(int x) const {
		if (x == -1)
			return 0;
		return t[x].value + t[x].size * t[x].delta;
	}

	void push(int x) {
		if (t[x].revert) {
			t[x].revert = false;
			swap(t[x].left, t[x].right);
			if (t[x].left != -1)
				t[t[x].left].revert = !t[t[x].left].revert;
			if (t[x].right != -1)
				t[t[x].right].revert = !t[t[x].right].revert;
		}
		t[x].nodeValue = getNodeValue(x);
		t[x].value = getValue(x);
		if (t[x].left != -1)
			t[t[x].left].delta += t[x].delta;
		if (t[x].right != -1)
			t[t[x].right].delta += t[x].delta;
		t[x].delta = 0;
	}

	void update(int x) {
		t[x].value = getNodeValue(x) + getValue(t[x].left) + getValue(t[x].right);
		t[x].size = 1 + getSize(t[x].left) + getSize(t[x].right);
	}

	void connect(int x, int p, int left) {
		if (x != -1)
		t[x].parent = p;
		if (left != -1) {
			if (left)
				t[p].left = x;
			else
				t[p].right = x;
		}
	}

	void rotate(int x) {
		int p = t[x].parent;
		int g = t[p].parent;
		bool root = isRoot(p);
		bool left = (x == t[p].left);
		connect(left ? t[x].right : t[x].left, p, left);
		connect(p, x, !left);
		connect(x, g, root ? -1 : (p == t[g].left));
		update(p);
	}

	void splay(int x) {
		while (!isRoot(x)) {
			int p = t[x].parent;
			int g = t[p].parent;
			if (!isRoot(p))
				push(g);
			push(p);
			push(x);
			if (!isRoot(p))
				rotate((x == t[p].left) == (p == t[g].left) ? p : x);
			rotate(x);
		}
		push(x);
		update(x);
	}

	int expose(int x) {
		int c = -1;
		for (int y = x; y != -1; y = t[y].parent) {
			splay(y);
			t[y].left = c;
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

	bool same(int x, int y) {
		if (x == y)
			return true;
		expose(x);
		expose(y);
		return t[x].parent != -1;
	}

	void link(int x, int y) {
		if (same(x, y))
			throw exception();
		evert(x);
		t[x].parent = y;
	}

	void cut(int x, int y) {
		evert(x);
		expose(y);
		if (t[y].right != x || t[x].left != -1)
			throw exception();
		t[t[y].right].parent = -1;
		t[y].right = -1;
	}

	int lca(int x, int y) {
		expose(x);
		expose(y);
		return t[x].parent;
	}

	long long query(int x, int y) {
		evert(x);
		expose(y);
		return getValue(y);
	}

	void update(int x, int y, long long v) {
		evert(x);
		expose(y);
		t[y].delta += v;
	}
};
