class TwoSat {
private:
	vector<vector<int>> g, gr;
	vector<int> color, order;

	void dfs1(int x) {
		color[x] = 1;
		for (int y : g[x])
			if (!color[y])
				dfs1(y);
		order.push_back(x);
	}

	void dfs2(int x, int c) {
		color[x] = c;
		for (int y : gr[x])
			if (!color[y])
				dfs2(y, c);
	}

public:
	TwoSat(int n) : g(2 * n), gr(2 * n) {}

	// id returns id of variable
	int id(int x, bool neg = false) {
		return x * 2 + neg;
	}

	// addIMPLY adds (x -> y)
	void addIMPLY(int x, int y) {
		g[x].push_back(y), gr[y].push_back(x);
	}

	// add adds (x)
	void add(int x) {
		addIMPLY(x ^ 1, x);
	}

	// addOR adds (x | y)
	void addOR(int x, int y) {
		addIMPLY(x ^ 1, y), addIMPLY(y ^ 1, x);
	}

	// addXOR adds (x ^ y)
	void addXOR(int x, int y) {
		addOR(x, y), addOR(x ^ 1, y ^ 1);
	}

	vector<bool> solve() {
		order.clear();
		color.assign(g.size(), 0);
		for (int i = 0; i < g.size(); i++)
			if (!color[i])
				dfs1(i);
		color.assign(g.size(), 0);
		for (int i = 0, c = 0; i < g.size(); i++) {
			int x = order[g.size() - i - 1];
			if (!color[x])
				dfs2(x, ++c);
		}
		vector<bool> ans;
		for (int i = 0; i < g.size(); i += 2) {
			if (color[i] == color[i + 1])
				return vector<bool>();
			ans.push_back(color[i] > color[i + 1]);
		}
		return ans;
	}
};
