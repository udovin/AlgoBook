i64 sum(int a, int b, int k) { // sum (a + b * i), i=0..k
	return a * i64(k + 1) + k * i64(k + 1) / 2 * b;
}
i64 divSum(int a, int b, int m, int k) { // sum (a + b * i) / m, i=0..k
	if (m == 0) return 0;
	if (a >= m || b >= m) {
		return sum(a / m, b / m, k) + divSum(a % m, b % m, m, k);
    }
	i64 c = (a + i64(b) * k) / m;
	return c * k - divSum(m - a - 1, m, b, c - 1);
}
i64 modSum(int a, int b, int m, int k) { // sum (a + b * i) % m, i=0..k
	return sum(a, b, k) - divSum(a, b, m, k) * m;
}
