class SuffixAutomaton {
private:
	struct Node {
		map<char, int> to;
		int len, link;

		Node() : to(), len(0), link(-1) {}

		int operator[](char c) const {
			map<char, int>::const_iterator it = to.find(c);
			return it == to.end() ? 0 : it->second;
		}
	};

	vector<Node> t;
	int last;

public:
	SuffixAutomaton() : t(1), last() {}

	void extend(char c) {
		int v = int(t.size());
		t.emplace_back();
		t[v].len = t[last].len + 1;
		int p;
		for (p = last; p != -1 && !t[p].to.count(c); p = t[p].link)
			t[p].to[c] = v;
		if (p < 0)
			t[v].link = 0;
		else {
			int q = t[p].to[c];
			if (t[p].len + 1 == t[q].len)
				t[v].link = q;
			else {
				int u = int(t.size());
				t.push_back(t[q]);
				t[u].len = t[p].len + 1;
				for (; p != -1 && t[p].to[c] == q; p = t[p].link)
					t[p].to[c] = u;
				t[q].link = t[v].link = u;
			}
		}
		last = v;
	}

	const Node& operator[](int v) const {
		return t[v];
	}
};
