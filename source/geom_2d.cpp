struct Vector {
	double x, y;

	Vector operator+(Vector& v) const {
		return {x + v.x, y + v.y};
	}

	Vector operator-(Vector& v) const {
		return {x - v.x, y - v.y};
	}

	Vector operator*(double a) const {
		return {x * a, y * a};
	}

	double operator*(Vector& v) const {
		return x * v.x + y * v.y;
	}

	double operator%(Vector& v) const {
		return x * v.y - y * v.x;
	}
};

struct Line {
	double a, b, c;
};

Line getLine(Vector a, Vector b) {
	Line c;
	c.a = b.y - a.y;
	c.b = a.x - b.x;
	c.c = -(c.a * a.x + c.b * a.y);
	return c;
}
