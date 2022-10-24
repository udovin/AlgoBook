struct EerTree {
    struct Node {
        int start, end;
        int len;
        int link;
        std::vector<int> next;
        Node() : start(-1), end(-1), len(-1), link(-1), next(26, -1) {}
    };
    vector<Node> t;
    int last;

    EerTree() : t(2) {
        t[0].len = -1;
        t[0].link = 0;
        t[1].len = 0;
        t[1].link = 0;
        last = 1;
    }
    void insert(const std::string& s, int pos) {
        int p = last;
        int letter = s[pos] - 'a';
        while (true) {
            if (pos - 1 - t[p].len >= 0 && s[pos - 1 - t[p].len] == s[pos])     
                break;
            p = t[p].link;
        }
        int v = t.size();
        t.emplace_back();
        t[v].len = t[p].len + 2;
        t[v].start = pos - t[v].len + 1;
        t[v].end = pos;
        t[p].next[letter] = v;
        if (t[v].len == 1){
            t[v].link = 1;
            last = v;
            return;
        }
        while (true) {
            p = t[p].link;
            if((pos - 1 - t[p].len) >= 0 && s[pos - 1 - t[p].len] == s[pos]) {
                t[v].link = t[p].next[letter];
                break;
            }       
        }
        last = v;
    }
    void print(const std::string& s, int node) {
        if(node != 0 && node != 1) {
            cout << s.substr(t[node].start, t[node].len) << endl;
        }
        for(int i = 0; i < 26; ++i) {
            if (t[node].next[i] != -1) {
                print(s, t[node].next[i]);
            }
        }
    }
    void printAll(const std::string& s){ print(s, 0); print(s, 1); }
};
