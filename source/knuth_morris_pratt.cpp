vector<int> kmp(const string& s) {
	vector<int> pi(s.size());
	for (int i = 1; i < s.size(); i++) {
		int j = pi[i - 1];
		while (j > 0 && s[j] != s[i])
			j = pi[j - 1];
		if (s[j] == s[i])
			j++;
		pi[i] = j;
	}
	return pi;
}

vector<int> find(const string& s, const string& t) {
	vector<int> pi(kmp(s)), pos;
	for (int i = 0, j = 0; i < t.size(); i++) {
		while (j > 0 && s[j] != t[i])
			j = pi[j - 1];
		if (s[j] == t[i])
			j++;
		if (j == s.size()) {
			pos.push_back(i - j + 1);
			j = pi[j - 1];
		}
	}
	return pos;
}
