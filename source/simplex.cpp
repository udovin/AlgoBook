const double EPS = 1e-9;

class Simplex {
	size_t m, n;
	vector<vector<double>> D;
	vector<size_t> B, N;

	void pivot(size_t r, size_t s) {
		double inv = 1 / D[r][s];
		for (size_t i = 0; i < m + 2; i++)
			if (i != r)
				for (size_t j = 0; j < n + 2; j++)
					if (j != s)
						D[i][j] -= D[r][j] * D[i][s] * inv;
		for (size_t j = 0; j < n + 2; j++)
			if (j != s)
				D[r][j] *= inv;
		for (size_t i = 0; i < m + 2; i++)
			if (i != r)
				D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(bool first) {
		size_t x = first ? m + 1 : m;
		for(;;) {
			size_t s = n + 1;
			for (size_t j = 0; j <= n; j++) {
				if (!first && N[j] == n + m + 1)
					continue;
				if (s == n + 1 || D[x][j] < D[x][s]
					|| D[x][j] == D[x][s] && N[j] < N[s])
					s = j;
			}
			if (s == n + 1 || D[x][s] > -EPS)
				return true;
			size_t r = m;
			for (size_t i = 0; i < m; i++) {
				if (D[i][s] < EPS)
					continue;
				if (r == m
					|| D[i][n + 1] * D[r][s] < D[r][n + 1] * D[i][s]
					|| D[i][n + 1] * D[r][s] == D[r][n + 1] * D[i][s]
					&& B[i] < B[r])
					r = i;
			}
			if (r == m)
				return false;
			pivot(r, s);
		}
	}

public:
	struct Unbounded : exception {};
	struct Infeasible : exception {};

	Simplex(const vector<vector<double>> &A,
		const vector<double> &b, const vector<double> &c)
		: m(b.size()), n(c.size()), N(n + 1), B(m)
		, D(m + 2, vector<double>(n + 2)) {
		for (size_t i = 0; i < m; i++)
			for (size_t j = 0; j < n; j++)
				D[i][j] = A[i][j];
		for (size_t i = 0; i < m; i++) {
			B[i] = n + i;
			D[i][n] = -1;
			D[i][n+1] = b[i];
		}
		for (size_t j = 0; j < n; j++) {
			N[j] = j;
			D[m][j] = -c[j];
		}
		N[n] = n + m + 1;
		D[m + 1][n] = 1;
	}

	double solve(vector<double> &x) {
		size_t r = 0;
		for (size_t i = 1; i < m; i++)
			if (D[i][n + 1] < D[r][n + 1])
				r = i;
		if (D[r][n + 1] < -EPS) {
			pivot(r, n);
			if (!simplex(true) || D[m + 1][n + 1] < -EPS)
				throw Infeasible();
			for (size_t i = 0; i < m; i++) {
				if (B[i] == n + m + 1) {
					size_t s = 0;
					for (size_t j = 1; j <= n; j++)
						if (D[i][j] < D[i][s]
							|| D[i][j] == D[i][s] && N[j] < N[s])
							s = j;
					pivot(i, s);
				}
			}
		}
		if (!simplex(false))
			throw Unbounded();
		x = vector<double>(n);
		for (size_t i = 0; i < m; i++)
			if (B[i] < n)
				x[B[i]] = D[i][n + 1];
		return D[m][n + 1];
	}
};