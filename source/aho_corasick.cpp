class AhoCorasick {
private:
	static const size_t LANG_SIZE = 26;
	static const char FIRST_CHAR = 'a';

	struct Node {
		map<char, size_t> to;
		size_t link;
		bool leaf;

		size_t go[LANG_SIZE];

		Node() : to(), link(), leaf() {
			fill(go, go + LANG_SIZE, 0);
		}

		const size_t operator[](char c) const {
			return go[c - FIRST_CHAR];
		}
	};

	vector<Node> t;

public:
	AhoCorasick() : t(1) {}

	void add(const string& s) {
		size_t v = 0;
		for (char c : s) {
			if (t[v].to.find(c) == t[v].to.end()) {
				t[v].to[c] = t.size();
				t.emplace_back();
			}
			v = t[v].to[c];
		}
		t[v].leaf = true;
	}

	void build() {
		queue<size_t> q;
		for (q.push(0); !q.empty(); q.pop()) {
			size_t v = q.front();
			for (const pair<char, size_t>& p : t[v].to) {
				q.push(p.second);
				if (v > 0) {
					size_t u = t[v].link;
					while (u > 0 && t[u].to.find(p.first) == t[u].to.end())
						u = t[u].link;
					if (t[u].to.find(p.first) != t[u].to.end())
						u = t[u].to[p.first];
					t[p.second].link = u;
				}
				t[v].go[p.first - FIRST_CHAR] = p.second;
			}
			for (size_t i = 0; i < LANG_SIZE; i++)
				if (t[v].go[i] == 0)
					t[v].go[i] = t[t[v].link].go[i];
		}
	}

	size_t size() const {
		return t.size();
	}

	const Node& operator[](size_t v) const {
		return t[v];
	}

	size_t go(size_t v, char c) const {
		while (v > 0 && t[v].to.find(c) == t[v].to.end())
			v = t[v].link;
		if (t[v].to.find(c) != t[v].to.end())
			v = t[v].to.find(c)->second;
		return v;
	}
};