struct DinicMaxFlow {
	struct Edge {
		int from, to, cap, flow;
	};

	int n;
	vector<vector<int>> g;
	vector<Edge> e;
	vector<int> d, it;
	int s_, t_;

	bool bfs_() {
		queue<int> q;
		fill(d.begin(), d.end(), -1);
		for (d[s_] = 0, q.push(s_); !q.empty(); q.pop()) {
			int a = q.front();
			for (int i = 0; i < g[a].size(); i++) {
				const Edge& x = e[g[a][i]];
				if (d[x.to] < 0 && x.flow < x.cap) {
					d[x.to] = d[a] + 1;
					q.push(x.to);
				}
			}
		}
		return d[t_] >= 0;
	}

	int dfs_(int a, int flow) {
		if (!flow || a == t_) {
			return flow;
		}
		for (int& i = it[a]; i < g[a].size(); i++) {
			Edge& x = e[g[a][i]];
			Edge& y = e[g[a][i] ^ 1];
			if (d[x.to] != d[a] + 1) {
				continue;
			}
			int delta = dfs_(x.to, min(flow, x.cap - x.flow));
			if (delta > 0) {
				x.flow += delta, y.flow -= delta;
				return delta;
			}
		}
		return 0;
	}

	DinicMaxFlow(int n) : n(n), g(n), d(n), it(n), s_(), t_() {}

	void addEdge(int a, int b, int cap) {
		g[a].push_back(e.size());
		e.push_back({a, b, cap, 0});
		g[b].push_back(e.size());
		e.push_back({b, a, 0, 0});
	}

	int maxFlow(int s, int t) {
		s_ = s, t_ = t;
		int flow = 0;
		while (bfs_()) {
			fill(it.begin(), it.end(), 0);
			while (int delta = dfs_(s_, INF)) {
				flow += delta;
			}
		}
		return flow;
	}
};
