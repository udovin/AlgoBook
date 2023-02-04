template<int N = 2> class HashString {
private:
	array<int, N> a, m;
	array<vector<int>, N> h, p;

public:
	HashString(
		const string& s, const array<int, N>& a = {31, 37}, const array<int, N>& m = {int(1e9) + 7, int(1e9) + 9})
		: a(a), m(m), h{}, p{} {
		for (int i = 0; i < N; i++) {
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
		for (int i = 0; i < N; i++) {
			int x = h[i][a + l] - h[i][b + l];
			if (x < 0)
				x += m[i];
			int y = (h[i][a] - h[i][b]) * i64(p[i][l]) % m[i];
			if (y < 0)
				y += m[i];
			if (x != y)
				return false;
		}
		return true;
	}

	array<int, N> get(int l, int r) const { // [l, r)
		array<int, N> x{};
		for (int i = 0; i < N; i++) {
			x[i] = (h[i][r] - h[i][l] * i64(p[i][r - l])) % m[i];
			if (x[i] < 0)
				x[i] += m[i];
		}
		return x;
	}

	array<int, N> get(const string& s) const {
		array<int, N> x{};
		// Or replace s[j] with (s[j] - FIRST_CHAR)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < s.size(); j++)
				x[i] = (x[i] * i64(a[i]) + s[j]) % m[i];
		return x;
	}
};
