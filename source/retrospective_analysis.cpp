class Analysis {
private:
	int n;
	vector<vector<int>> g;
	vector<char> state;
	vector<char> used;
	vector<int> degree;

	void dfs (int v) {
		used[v] = true;
		for (auto x : g[v]) {
			if (!used[x]) {
				if (state[v] == -1)
					state[x] = 1;
				else if (--degree[x] == 0)
					state[x] = -1;
				else
					continue;
				dfs(x);
			}
		}
	}
public:
	Analysis(int n) : n(n), g(n), state(n), used(n), degree(n) {}

	void addEdge(int u, int v) { g[v].push_back(u); degree[u]++; }
	void addState(int x, bool f) { state[x] = f ? 1 : -1; }

	vector<char> solve() {
		for (int i = 0; i < n; i++) {
			if (!used[i] && state[i]) {
				dfs(i);
			}
		}
		return state;
	}
};
