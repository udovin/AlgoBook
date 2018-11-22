int gcd(int a, int b, int& x, int& y) {
	int c, q, xp, yp;
	x = yp = 1;
	y = xp = 0;
	while (b != 0) {
		q = a / b;
		c = a - q * b;
		a = b;
		b = c;
		c = x - q * xp;
		x = xp;
		xp = c;
		c = y - q * yp;
		y = yp;
		yp = c;
	}
	return a;
}
