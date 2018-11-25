const int INF = 2e9;

class MinCut {
private:
    int n;
    vector< vector<int> > g;
    vector<int> v;
    vector<int> d;
    vector<int> vis;
public:
    MinCut(int n)
        :n(n), g(n + 1), v(n + 1), d(n + 1), vis(n + 1) {
        for(int i = 1; i <= n; i++) {
            g[i].resize(n + 1);
        }
    }
    void add(int u, int v, int c) {
        g[u][v] += c;
        g[v][u] += c;
    }
    int solve() {
        int res = INF;
        for (int i = 1; i <= n; i++)
            v[i] = i, vis[i] = 0;
        while (n > 1) {
            int p = 2, prev = 1;
            for (int i = 2; i <= n; ++i) {
                d[v[i]] = g[v[1]][v[i]];
                if (d[v[i]] > d[v[p]])
                    p = i;
            }
            vis[v[1]] = n;
            for (int i = 2; i <= n; ++i) {
                if (i == n) {
                    res = min(res, d[v[p]]); // if d[v[p]] < res, then s = v[p] & t = v[prev]
                    for (int j = 1; j <= n; ++j) {
                        g[v[prev]][v[j]] += g[v[p]][v[j]];
                        g[v[j]][v[prev]] = g[v[prev]][v[j]];
                    }
                    v[p] = v[n--];
                    break;
                }
                vis[v[p]] = n;
                prev = p;
                p = -1;
                for (int j = 2; j <= n; ++j) {
                    if (vis[v[j]] != n) {
                        d[v[j]] += g[v[prev]][v[j]];
                        if (p == -1 || d[v[p]] < d[v[j]])
                            p = j;
                    }
                }
            }
        }
        return res;
    }

};
