struct MinCostMaxFlow {
	struct Edge {
		int from, to, cap, flow, cost;
	};

	vector<vector<int>> g;
	vector<Edge> e;
	vector<int> d, p;

	MinCostMaxFlow(int n) : g(n), d(n), p(n) {}

	bool fordBellman_(int s, int t) {
		fill(d.begin(), d.end(), INF);
		fill(p.begin(), p.end(), -1);
		d[s] = 0;
		for (int i = 0; i < g.size(); i++) {
			for (int j = 0; j < e.size(); j++) {
				const Edge& x = e[j];
				if (d[x.from] == INF || x.flow >= x.cap) {
					continue;
				}
				if (d[x.from] + x.cost < d[x.to]) {
					d[x.to] = d[x.from] + x.cost;
					p[x.to] = j;
				}
			}
		}
		return d[t] != INF;
	}

	void addEdge(int a, int b, int cap, int cost) {
		g[a].push_back(e.size());
		e.push_back({a, b, cap, 0, cost});
		g[b].push_back(e.size());
		e.push_back({b, a, 0, 0, -cost});
	}

	pair<int, int> solve(int s, int t) {
		int flow = 0, cost = 0;
		while (fordBellman_(s, t)) {
			int cflow = INF;
			for (int i = t; p[i] != -1; i = e[p[i]].from) {
				cflow = min(cflow, e[p[i]].cap - e[p[i]].flow);
			}
			for (int i = t; p[i] != -1; i = e[p[i]].from) {
				cost += cflow * e[p[i]].cost;
				e[p[i]].flow += cflow;
				e[p[i] ^ 1].flow -= cflow;
			}
			flow += cflow;
		}
		return {flow, cost};
	}
};
