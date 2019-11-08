const int N = 1e2 + 11;
const int INF = 1e9 + 7;

struct DinicMaxFlow {
	struct Edge {
		int from, to, cap, flow;
	};

	int n, s, t;
	vector<vector<int>> g;
	vector<Edge> e;
	vector<int> d, it;

	bool bfs() {
		queue<int> q;
		fill(d.begin(), d.end(), -1);
		for (d[s] = 0, q.push(s); !q.empty(); q.pop()) {
			int a = q.front();
			for (int i = 0; i < g[a].size(); i++) {
				const Edge& x = e[g[a][i]];
				if (d[x.to] < 0 && x.flow < x.cap) {
					d[x.to] = d[a] + 1;
					q.push(x.to);
				}
			}
		}
		return d[t] >= 0;
	}

	int dfs(int a, int flow) {
		if (!flow || a == t)
			return flow;
		for (int& i = it[a]; i < g[a].size(); i++) {
			Edge& x = e[g[a][i]];
			Edge& y = e[g[a][i] ^ 1];
			if (d[x.to] != d[a] + 1)
				continue;
			int delta = dfs(x.to, min(flow, x.cap - x.flow));
			if (delta > 0) {
				x.flow += delta, y.flow -= delta;
				return delta;
			}
		}
		return 0;
	}

	DinicMaxFlow(int n, int s, int t)
		: n(n), s(s), t(t), g(n), d(n), it(n) {}

	void add(int a, int b, int cap) {
		g[a].push_back(e.size());
		e.push_back({a, b, cap, 0});
		g[b].push_back(e.size());
		e.push_back({a, b, 0, 0});
	}

	int get() {
		int flow = 0;
		while (bfs()) {
			fill(it.begin(), it.end(), 0);
			while (int delta = dfs(s, INF))
				flow += delta;
		}
		return flow;
	}
};
