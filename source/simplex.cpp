const double EPS = 1e-9;

class Simplex {
	int m, n;
	vector<vector<double>> D;
	vector<int> B, N;

	void pivot(int r, int s) {
		double inv = 1 / D[r][s];
		for (int i = 0; i < m + 2; i++)
			if (i != r)
				for (int j = 0; j < n + 2; j++)
					if (j != s)
						D[i][j] -= D[r][j] * D[i][s] * inv;
		for (int j = 0; j < n + 2; j++)
			if (j != s)
				D[r][j] *= inv;
		for (int i = 0; i < m + 2; i++)
			if (i != r)
				D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = phase == 1 ? m + 1 : m;
		for (;;) {
			int s = -1;
			for (int j = 0; j <= n; j++) {
				if (phase == 2 && N[j] < 0)
					continue;
				if (s < 0 || D[x][j] < D[x][s]
					|| D[x][j] == D[x][s] && N[j] < N[s])
					s = j;
			}
			if (s < 0 || D[x][s] > -EPS)
				return true;
			int r = -1;
			for (int i = 0; i < m; i++) {
				if (D[i][s] < EPS)
					continue;
				if (r < 0
					|| D[i][n + 1] * D[r][s] < D[r][n + 1] * D[i][s]
					|| D[i][n + 1] * D[r][s] == D[r][n + 1] * D[i][s]
					&& B[i] < B[r])
					r = i;
			}
			if (r < 0)
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
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				D[i][j] = A[i][j];
		for (int i = 0; i < m; i++) {
			B[i] = n + i;
			D[i][n] = -1;
			D[i][n + 1] = b[i];
		}
		for (int j = 0; j < n; j++) {
			N[j] = j;
			D[m][j] = -c[j];
		}
		N[n] = -1;
		D[m + 1][n] = 1;
	}

	double solve(vector<double> &x) {
		int r = 0;
		for (int i = 1; i < m; i++)
			if (D[i][n + 1] < D[r][n + 1])
				r = i;
		if (D[r][n + 1] < -EPS) {
			pivot(r, n);
			if (!simplex(1) || D[m + 1][n + 1] < -EPS)
				throw Infeasible();
			for (int i = 0; i < m; i++) {
				if (B[i] < 0) {
					int s = 0;
					for (int j = 1; j <= n; j++)
						if (D[i][j] < D[i][s]
							|| D[i][j] == D[i][s] && N[j] < N[s])
							s = j;
					pivot(i, s);
				}
			}
		}
		if (!simplex(2))
			throw Unbounded();
		x = vector<double>(n);
		for (int i = 0; i < m; i++)
			if (B[i] < n)
				x[B[i]] = D[i][n + 1];
		return D[m][n + 1];
	}
};