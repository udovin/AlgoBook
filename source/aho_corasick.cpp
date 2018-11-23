class AhoCorasick {
private:
	static const int LANG_SIZE = 26;
	static const char FIRST_CHAR = 'a';

	struct Node {
		map<char, int> to;
		int link;
		bool leaf;

		int go[LANG_SIZE];

		Node() : to(), link(), leaf() {
			fill(go, go + LANG_SIZE, 0);
		}

		const int operator[](char c) const {
			return go[c - FIRST_CHAR];
		}
	};

	vector<Node> t;

public:
	AhoCorasick() : t(1) {}

	void add(const string& s, int i) {
		int v = 0;
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
		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int v = q.front();
			for (const pair<char, int>& p : t[v].to) {
				q.push(p.second);
				if (v > 0) {
					int u = t[v].link;
					while (u > 0 && t[u].to.find(p.first) == t[u].to.end())
						u = t[u].link;
					if (t[u].to.find(p.first) != t[u].to.end())
						u = t[u].to[p.first];
					t[p.second].link = u;
				}
				t[v].go[p.first - FIRST_CHAR] = p.second;
			}
			for (int i = 0; i < LANG_SIZE; i++)
				if (t[v].go[i] == 0)
					t[v].go[i] = t[t[v].link].go[i];
		}
	}

	int size() const {
		return t.size();
	}

	const Node& operator[](int v) const {
		return t[v];
	}

	int go(int v, char c) const {
		while (v > 0 && t[v].to.find(c) == t[v].to.end())
			v = t[v].link;
		if (t[v].to.find(c) != t[v].to.end())
			v = t[v].to.find(c)->second;
		return v;
	}
};
