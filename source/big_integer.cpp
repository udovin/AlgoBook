class BigInt {
private:
	static const int POWER = 9, BASE = int(1e9);

	vector<int> digits;
	bool sign;

	static int compare(const vector<int>& a, const vector<int>& b) {
		if (a.size() != b.size())
			return a.size() < b.size() ? -1 : 1;
		for (int i = a.size() - 1; i >= 0; i--) {
			if (a[i] != b[i])
				return a[i] < b[i] ? -1 : 1;
		}
		return 0;
	}

	static void add(vector<int>& a, const vector<int>& b) {
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

	static void subtract(vector<int>& a, const vector<int>& b) {
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

	static vector<int> multiply(const vector<int>& a, const vector<int>& b) {
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

	static vector<int> divide(const vector<int>& a, const vector<int>& b) {
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
		return c;
	}

	static vector<int> module(
		const vector<int>& a, const vector<int>& b) {
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
			subtract(mod, multiply(b, vector<int>(1, x)));
		}
		return mod;
	}

public:
	BigInt(long long value = 0) : digits(), sign() {
		if (value < 0)
			sign = true, value = -value;
		do {
			long long carry = value / BASE;
			digits.push_back(value - carry * BASE);
			value = carry;
		} while (value > 0);
	}

	BigInt(const string& value) : digits(), sign() {
		if (value[0] == '-')
			sign = true;
		for (int i = value.size(); i > sign; i -= POWER) {
			int j = max(i - POWER, int(sign));
			string part = value.substr(j, i - j);
			int digit;
			stringstream(part.c_str()) >> digit;
			digits.push_back(digit);
		}
	}

	BigInt(const BigInt& other)
		: digits(other.digits), sign(other.sign) {}

	BigInt& operator=(const BigInt& other) {
		digits = other.digits, sign = other.sign;
		return *this;
	}

	operator string() const {
		stringstream value;
		if (sign)
			value << '-';
		value << digits.back();
		for (int i = int(digits.size()) - 2; i >= 0; i--) {
			value << setfill('0') << setw(POWER) << digits[i];
		}
		return value.str();
	}

	BigInt& operator+=(BigInt other) {
		if (sign == other.sign) {
			add(digits, other.digits);
			return *this;
		}
		int value = compare(digits, other.digits);
		if (value == 0) {
			sign = false;
			digits = vector<int>(1);
			return *this;
		}
		if (value < 0) {
			sign = !sign;
			digits.swap(other.digits);
		}
		subtract(digits, other.digits);
		return *this;
	}

	BigInt& operator-=(BigInt other) {
		if (sign != other.sign) {
			add(digits, other.digits);
			return *this;
		}
		int value = compare(digits, other.digits);
		if (value == 0) {
			sign = false;
			digits = vector<int>(1);
			return *this;
		}
		if (value < 0) {
			sign = !sign;
			digits.swap(other.digits);
		}
		subtract(digits, other.digits);
		return *this;
	}

	BigInt& operator*=(const BigInt& other) {
		digits = multiply(digits, other.digits);
		if (other.sign)
			sign = !sign;
		if (digits.size() == 1 && digits[0] == 0)
			sign = false;
		return *this;
	}

	BigInt& operator/=(const BigInt& other) {
		digits = divide(digits, other.digits);
		if (other.sign)
			sign = !sign;
		if (digits.size() == 1 && digits[0] == 0)
			sign = false;
		return *this;
	}

	BigInt& operator%=(const BigInt& other) {
		digits = module(digits, other.digits);
		if (digits.size() == 1 && digits[0] == 0)
			sign = false;
		return *this;
	}

	bool operator==(const BigInt& other) const {
		if (sign != other.sign)
			return false;
		return compare(digits, other.digits) == 0;
	}

	bool operator<(const BigInt& other) const {
		if (sign != other.sign)
			return sign;
		return compare(digits, other.digits) < 0;
	}

	bool operator>(const BigInt& other) const {
		if (sign != other.sign)
			return !sign;
		return compare(digits, other.digits) > 0;
	}

	bool operator!=(const BigInt& other) const { return !operator==(other); }
	bool operator<=(const BigInt& other) const { return !operator>(other); }
	bool operator>=(const BigInt& other) const { return !operator<(other); }
	BigInt operator+(const BigInt& other) const { return BigInt(*this) += other; }
	BigInt operator-(const BigInt& other) const { return BigInt(*this) -= other; }
	BigInt operator*(const BigInt& other) const { return BigInt(*this) *= other; }
	BigInt operator/(const BigInt& other) const { return BigInt(*this) /= other; }
	BigInt operator%(const BigInt& other) const { return BigInt(*this) %= other; }
};

istream& operator>>(istream& is, BigInt& value) {
	string raw;
	is >> raw;
	value = raw;
	return is;
}

ostream& operator<<(ostream& os, const BigInt& value) {
	return os << string(value);
}
