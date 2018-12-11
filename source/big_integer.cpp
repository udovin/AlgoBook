class BigInt {
private:
	static const int POWER = 9, BASE = int(1e9);

	vector<int> digits;
	bool sign;

	static int compare(
		const vector<int>& digits, const vector<int>& other) {
		if (digits.size() != other.size())
			return digits.size() < other.size() ? -1 : 1;
		for (int i = digits.size() - 1; i >= 0; i--) {
			if (digits[i] != other[i])
				return digits[i] < other[i] ? -1 : 1;
		}
		return 0;
	}

	static void add(
		vector<int>& digits, const vector<int>& other) {
		digits.resize(max(digits.size(), other.size()) + 1);
		int carry = 0;
		for (int i = 0; i < digits.size(); i++) {
			carry += digits[i];
			if (i < other.size())
				carry += other[i];
			digits[i] = carry;
			carry = 0;
			if (digits[i] >= BASE) {
				digits[i] -= BASE;
				carry = 1;
			}
		}
		while (digits.size() > 1 && digits.back() == 0)
			digits.pop_back();
	}

	static void subtract(
		vector<int>& digits, const vector<int>& other) {
		digits.resize(max(digits.size(), other.size()) + 1);
		int carry = 0;
		for (int i = 0; i < digits.size(); i++) {
			carry += digits[i];
			if (i < other.size())
				carry -= other[i];
			digits[i] = carry;
			carry = 0;
			if (digits[i] < 0) {
				digits[i] += BASE;
				carry = -1;
			}
		}
		while (digits.size() > 1 && digits.back() == 0)
			digits.pop_back();
	}

	static vector<int> multiply(
		const vector<int>& digits, const vector<int>& other) {
		vector<int> value(digits.size() + other.size());
		for (int i = 0; i < digits.size(); i++) {
			long long carry = 0;
			for (int j = 0; j < other.size() || carry > 0; j++) {
				carry += value[i + j]
					+ digits[i] * (long long)other[j];
				value[i + j] = carry % BASE;
				carry /= BASE;
			}
		}
		while (value.size() > 1 && value.back() == 0)
			value.pop_back();
		return value;
	}

	static vector<int> divide(
		const vector<int>& digits, const vector<int>& other) {
		vector<int> value(digits.size());
		vector<int> mod, cur;
		for (int i = digits.size() - 1; i >= 0; i--) {
			mod.insert(mod.begin(), digits[i]);
			while (mod.size() > 1 && mod.back() == 0)
				mod.pop_back();
			int x = 0, l = 0, r = BASE;
			while (l <= r) {
				int m = (l + r) / 2;
				cur = multiply(other, vector<int>(1, m));
				if (compare(mod, cur) >= 0)
					x = m, l = m + 1;
				else
					r = m - 1;
			}
			value[i] = x;
			cur = multiply(other, vector<int>(1, x));
			subtract(mod, cur);
		}
		while (value.size() > 1 && value.back() == 0)
			value.pop_back();
		return value;
	}

	static vector<int> module(
		const vector<int>& digits, const vector<int>& other) {
		vector<int> mod, cur;
		for (int i = digits.size() - 1; i >= 0; i--) {
			mod.insert(mod.begin(), digits[i]);
			while (mod.size() > 1 && mod.back() == 0)
				mod.pop_back();
			int x = 0, l = 0, r = BASE;
			while (l <= r) {
				int m = (l + r) / 2;
				cur = multiply(other, vector<int>(1, m));
				if (compare(mod, cur) >= 0)
					x = m, l = m + 1;
				else
					r = m - 1;
			}
			cur = multiply(other, vector<int>(1, x));
			subtract(mod, cur);
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

	bool operator!=(const BigInt& other) const {
		return !operator==(other);
	}

	bool operator<=(const BigInt& other) const {
		return !operator>(other);
	}

	bool operator>=(const BigInt& other) const {
		return !operator<(other);
	}

	BigInt operator+(const BigInt& other) const {
		return BigInt(*this) += other;
	}

	BigInt operator-(const BigInt& other) const {
		return BigInt(*this) -= other;
	}

	BigInt operator*(const BigInt& other) const {
		return BigInt(*this) *= other;
	}

	BigInt operator/(const BigInt& other) const {
		return BigInt(*this) /= other;
	}

	BigInt operator%(const BigInt& other) const {
		return BigInt(*this) %= other;
	}
};

istream& operator>>(istream& is, BigInt& value) {
	string raw;
	is >> raw;
	value = raw;
	return is;
}

ostream& operator<<(ostream& os, const BigInt& value) {
	cout << string(value);
	return os;
}
