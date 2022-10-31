struct DSU {
    vector<int> p;
    vector<char> r;
    
    DSU(int n) : p(n), r(n) {
        iota(p.begin(), p.end(), 0);
    }

    int get(int x) {
        return x == p[x] ? x : p[x] = get(p[x]);
    }

    void join(int x, int y) {
        x = get(x), y = get(y);
        if (x != y) {
            if (r[x] < r[y]) {
                swap(x, y);
            }
            p[y] = x;
            if (r[x] == r[y]) {
                r[x]++;
            }
        }
    }
};
