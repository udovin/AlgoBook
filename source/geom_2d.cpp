struct Vector {
	long long x, y;

	Vector operator+(const Vector& v) const {
		return {x + v.x, y + v.y};
	}

	Vector operator-(const Vector& v) const {
		return {x - v.x, y - v.y};
	}

	Vector operator*(long long a) const {
		return {x * a, y * a};
	}

	long long operator*(const Vector& v) const {
		return x * v.x + y * v.y;
	}

	long long operator%(const Vector& v) const {
		return x * v.y - y * v.x;
	}
};

struct Line {
	long long a, b, c;
};

Line getLine(const Vector& a, const Vector& b) {
	Line c;
	c.a = b.y - a.y;
	c.b = a.x - b.x;
	c.c = -(c.a * a.x + c.b * a.y);
	return c;
}
