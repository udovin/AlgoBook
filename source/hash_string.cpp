class HashString {
private:
	vector<int> a, m;
	vector<vector<int>> h, p;

public:
	HashString(const string& s, const vector<int>& a, const vector<int>& m)
		: a(a), m(m), h(a.size()), p(a.size()) {
		for (int i = 0; i < m.size(); i++) {
			h[i].resize(s.size() + 1);
			p[i].resize(s.size() + 1);
			h[i][0] = 0, p[i][0] = 1;
			for (int j = 1; j <= s.size(); j++) {
				// Or replace s[j - 1] with (s[j - 1] - FIRST_CHAR)
				h[i][j] = (h[i][j - 1] * (long long)a[i] + s[j - 1]) % m[i];
				p[i][j] = (p[i][j - 1] * (long long)a[i]) % m[i];
			}
		}
	}

	bool check(int a, int b, int l) const {
		for (int i = 0; i < m.size(); i++) {
			int x = h[i][a + l] - h[i][b + l];
			if (x < 0)
				x += m[i];
			int y = (h[i][a] - h[i][b]) * (long long)p[i][l] % m[i];
			if (y < 0)
				y += m[i];
			if (x != y)
				return false;
		}
		return true;
	}

	vector<int> get(int l, int r) const {
		vector<int> x(m.size());
		for (int i = 0; i < m.size(); i++) {
			x[i] = (h[i][r] - h[i][l] * (long long)p[i][r - l]) % m[i];
			if (x[i] < 0)
				x[i] += m[i];
		}
		return x;
	}

	vector<int> get(const string& s) const {
		vector<int> x(m.size());
		// Or replace s[j] with (s[j] - FIRST_CHAR)
		for (int i = 0; i < m.size(); i++)
			for (int j = 0; j < s.size(); j++)
				x[i] = (x[i] * (long long)a[i] + s[j]) % m[i];
		return x;
	}
};
