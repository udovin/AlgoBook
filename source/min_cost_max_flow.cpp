struct MinCostMaxFlow {
	struct Edge {
		int from, to, cap, flow, cost;
	};

	vector<vector<int>> g;
	vector<Edge> e;
	vector<int> p;
	vector<int> d, phi;

	MinCostMaxFlow(int n) : g(n), e(), p(n), d(n), phi(n) {}
	void fordBellman_(int s) {
		fill(d.begin(), d.end(), INF);
		d[s] = 0;
		bool change = true;
		for (int k = 0; k <= g.size() && change; k++) {
			change = false;
			for (int i = 0; i < e.size(); i++) {
				const Edge& ei = e[i];
				if (ei.flow >= ei.cap || d[ei.from] == INF) {
					continue;
				}
				if (d[ei.from] + ei.cost < d[ei.to]) {
					d[ei.to] = d[ei.from] + ei.cost;
					change = true;
				}
			}
		}
		assert(!change);
	}
	bool dijkstra_(int s, int t) {
		priority_queue<pair<int, int>> q;
		fill(d.begin(), d.end(), INF);
		fill(p.begin(), p.end(), -1);
		d[s] = 0;
		q.emplace(0, s);
		while (!q.empty()) {
			int x = q.top().second;
			int dx = -q.top().first;
			q.pop();
			if (dx > d[x]) {
				continue;
			}
			for (int i : g[x]) {
				const Edge& ei = e[i];
				if (ei.flow >= ei.cap) {
					continue;
				}
				int wi = ei.cost + phi[ei.from] - phi[ei.to];
				if (dx + wi < d[ei.to]) {
					d[ei.to] = dx + wi;
					p[ei.to] = i;
					q.emplace(-d[ei.to], ei.to);
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
		fordBellman_(s);
		phi = d;
		int flow = 0, cost = 0;
		while (dijkstra_(s, t)) {
			for (int i = 0; i < g.size(); i++) {
            	phi[i] = min(phi[i] + d[i], INF);
			}
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
