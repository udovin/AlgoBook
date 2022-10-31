template<class T, class R, class C1, class C2>
vector<T> matroidIntersection(const vector<T>& s, R rebuild, C1 check1, C2 check2) {
    vector<bool> used(s.size());
    auto augment = [&]() {
        vector<T> a;
        for (int i = 0; i < s.size(); i++) {
            if (used[i]) {
                a.push_back(s[i]);
            }
        }
        rebuild(a);
        vector<vector<int>> g(s.size() + 2);
        for (int x = 0; x < s.size(); x++) {
            if (used[x]) {
                continue;
            }
            auto c1 = check1(s[x]);
            auto c2 = check2(s[x]);
            if (c1 && c2) {
                used[x] = true;
                return true;
            }
            if (c1) {
                g[s.size()].push_back(x);
            }
            if (c2) {
                g[x].push_back(s.size() + 1);
            }
        }
        for (int x = 0; x < s.size(); x++) {
            if (!used[x]) {
                continue;
            }
            vector<T> a;
            for (int i = 0; i < s.size(); i++) {
                if (used[i] && i != x) {
                    a.push_back(s[i]);
                }
            }
            rebuild(a);
            for (int y = 0; y < s.size(); y++) {
                if (used[y]) {
                    continue;
                }
                if (check1(s[y])) {
                    g[x].push_back(y);
                }
                if (check2(s[y])) {
                    g[y].push_back(x);
                }
            }
        }
        vector<int> d(s.size() + 2, -1);
        vector<int> p(s.size() + 2);
        queue<int> q;
        q.push(s.size());
        d[s.size()] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto y : g[x]) {
                if (d[y] == -1) {
                    d[y] = d[x] + 1;
                    p[y] = x;
                    q.push(y);
                }
            }
        }
        if (d[s.size() + 1] == -1) {
            return false;
        }
        int x = p[s.size() + 1];
        while (x != s.size()) {
            used[x] = !used[x];
            x = p[x];
        }
        return true;
    };
    while (augment());
    vector<T> a;
    for (int i = 0; i < s.size(); i++) {
        if (used[i]) {
            a.push_back(s[i]);
        }
    }
    return a;
}
