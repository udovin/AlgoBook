struct Complex {
	long double x, y;

	Complex() : x(), y() {}

	Complex(long double x, long double y) : x(x), y(y) {}

	Complex operator+(const Complex& o) const {
		return {x + o.x, y + o.y};
	}

	Complex operator-(const Complex& o) const {
		return {x - o.x, y - o.y};
	}

	Complex operator*(const Complex& o) const {
		return {x * o.x - y * o.y, x * o.y + y * o.x};
	}
};

const long double PI = acosl(-1);

// a should be of size 2^k
void fft(vector<Complex>& a, bool inv = false) {
	for (int i = 1, j = 0; i < a.size(); i++) {
		int bit = a.size() / 2;
		for (; j >= bit; bit /= 2) {
			j -= bit;
		}
		j += bit;
		if (i < j) {
			swap(a[i], a[j]);
		}
	}
	int n = a.size();
	for (int k = 1; k < n; k *= 2) {
		long double ang = PI / (inv ? -k : k);
		Complex e(cosl(ang), sinl(ang));
		for (int i = 0; i < n; i += 2 * k) {
			Complex w(1, 0);
			for (int j = 0; j < k; ++j) {
				Complex v = a[i + j + k] * w;
				a[i + j + k] = a[i + j] - v;
				a[i + j] = a[i + j] + v;
				w = w * e;
			}
		}
	}
	if (inv) {
		for (int i = 0; i < n; i++) {
			a[i].x /= n;
			a[i].y /= n;
		}
	}
}
