const int POWER = 9, BASE = int(1e9);

int compare(const vector<int>& a, const vector<int>& b) {
	if (a.size() != b.size())
		return a.size() < b.size() ? -1 : 1;
	for (int i = a.size() - 1; i >= 0; i--) {
		if (a[i] != b[i])
			return a[i] < b[i] ? -1 : 1;
	}
	return 0;
}

void add(vector<int>& a, const vector<int>& b) {
	a.resize(max(a.size(), b.size()) + 1);
	int carry = 0;
	for (int i = 0; i < a.size(); i++) {
		carry += a[i];
		if (i < b.size())
			carry += b[i];
		a[i] = carry;
		carry = 0;
		if (a[i] >= BASE) {
			a[i] -= BASE;
			carry = 1;
		}
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
}

void subtract(vector<int>& a, const vector<int>& b) {
	a.resize(max(a.size(), b.size()) + 1);
	int carry = 0;
	for (int i = 0; i < a.size(); i++) {
		carry += a[i];
		if (i < b.size())
			carry -= b[i];
		a[i] = carry;
		carry = 0;
		if (a[i] < 0) {
			a[i] += BASE;
			carry = -1;
		}
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size());
	for (int i = 0; i < a.size(); i++) {
		long long carry = 0;
		for (int j = 0; j < b.size() || carry > 0; j++) {
			carry += c[i + j] + a[i] * (long long)(j < b.size() ? b[j] : 0);
			c[i + j] = carry % BASE;
			carry /= BASE;
		}
	}
	while (c.size() > 1 && c.back() == 0)
		c.pop_back();
	return c;
}

pair<vector<int>, vector<int>> divMod(
	const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size());
	vector<int> mod;
	for (int i = a.size() - 1; i >= 0; i--) {
		mod.insert(mod.begin(), a[i]);
		while (mod.size() > 1 && mod.back() == 0)
			mod.pop_back();
		int x = 0, l = 0, r = BASE;
		while (l <= r) {
			int m = (l + r) / 2;
			if (compare(mod, multiply(b, vector<int>(1, m))) >= 0)
				x = m, l = m + 1;
			else
				r = m - 1;
		}
		c[i] = x;
		subtract(mod, multiply(b, vector<int>(1, x)));
	}
	while (c.size() > 1 && c.back() == 0)
		c.pop_back();
	return {c, mod};
}

string print(const vector<int>& a) const {
	stringstream value;
	value << a.back();
	for (int i = int(a.size()) - 2; i >= 0; i--) {
		value << setfill('0') << setw(POWER) << a[i];
	}
	return value.str();
}
