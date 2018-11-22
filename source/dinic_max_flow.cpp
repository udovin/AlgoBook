const int N = 1e2 + 11;
const int INF = 1e9 + 7;

class DinicMaxFlow {
private:
    struct Edge {
        int to, rev, cap, flow;
    };

    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> d, it;

    bool bfs() {
        fill(d.begin(), d.end(), -1);
        queue<int> q;
        d[s] = 0;
        for (q.push(s); !q.empty(); q.pop()) {
            int a = q.front();
            for (int i = 0; i < g[a].size(); i++) {
                const Edge& e = g[a][i];
                int b = e.to;
                if (d[b] < 0 && e.flow < e.cap) {
                    d[b] = d[a] + 1;
                    q.push(b);
                }
            }
        }
        return d[t] >= 0;
    }

    int dfs(int a, int flow) {
        if (!flow || a == t)
            return flow;
        for (int& i = it[a]; i < g[a].size(); i++) {
            Edge& e = g[a][i];
            Edge& r = g[e.to][e.rev];
            int b = e.to;
            if (d[b] != d[a] + 1)
                continue;
            int delta = dfs(b, min(flow, e.cap - e.flow));
            if (delta > 0) {
                e.flow += delta;
                r.flow -= delta;
                return delta;
            }
        }
        return 0;
    }

public:
    DinicMaxFlow(int n, int s, int t)
        : n(n), s(s), t(t), g(n), d(n), it(n) {}

    void addEdge(int a, int b, int cap) {
        Edge e1 = {b, g[b].size(), cap, 0};
        Edge e2 = {a, g[a].size(), 0, 0};
        g[a].push_back(e1);
        g[b].push_back(e2);
    }

    int getMaxFlow() {
        int flow = 0;
        while (bfs()) {
            fill(it.begin(), it.end(), 0);
            while (int delta = dfs(s, INF))
                flow += delta;
        }
        return flow;
    }
};
