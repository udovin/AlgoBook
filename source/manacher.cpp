vector<int> manacher(const string& s, bool e) {
	vector<int> d(s.size() - e);
	for (int i = 0, l = 0, r = 0; i < d.size(); i++) {
		if (i < r)
			d[i] = min(d[l + r - i], r - i);
		while (i - d[i] >= 0 && i + d[i] < d.size()
			&& s[i - d[i]] == s[i + d[i] + e])
			d[i]++;
		if (i + d[i] > r)
			l = i - d[i], r = i + d[i];
	}
	return d;
}
