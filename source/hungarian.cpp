class Hungarian {
public:
    static constexpr int INF = 1e9 + 7;

    vector<vector<int>> a;
    int n, m;

    Hungarian(const vector<vector<int>> &mat) {
        n = mat.size();
        m = mat[0].size();
        a.resize(n + 1, vector<int>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i + 1][j + 1] = mat[i][j];
            }
        }
    }

    struct Result {
        int cost;
        std::vector<int> p;
    };

    Result Solve() {
        vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
        for (int i = 1; i <= n; ++i) {
            p[0] = i;
            int j0 = 0;
            vector<int> minv(m + 1, INF);
            vector<char> used(m + 1, false);
            do {
                used[j0] = true;
                int i0 = p[j0], delta = INF, j1;
                for (int j = 1; j <= m; ++j)
                    if (!used[j]) {
                        int cur = a[i0][j] - u[i0] - v[j];
                        if (cur < minv[j])
                            minv[j] = cur, way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j], j1 = j;
                    }
                for (int j = 0; j <= m; ++j)
                    if (used[j])
                        u[p[j]] += delta, v[j] -= delta;
                    else
                        minv[j] -= delta;
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }

        Result res;
        res.cost = -v[0];
        res.p.resize(n, -1);
        for (int j = 0; j < m; ++j) {
            if (p[j + 1] != 0) {
                res.p[p[j + 1] - 1] = j;
            }
        }

        return res;
    }
};
