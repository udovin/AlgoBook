#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

#include <big_integer.cpp>

mt19937 mt;

void testBigInt() {
    {
        BigInt a = 10, b = 5;
        assert(a / b == 2);
        assert(a * b == 50);
        assert(a % b == 0);
    }
    {
        BigInt a = 2;
        for (int i = 0; i < 8; i++) {
            a *= a;
        }
        BigInt b = 1;
        for (int i = 0; i < 10; i++) {
            b *= 3;
        }
        assert(a / 2 * 2 == a);
        assert(a % 2 == 0);
        assert(a % 3 == 1);
        assert(a % b == 45754);
    }
}

int main() {
    testBigInt();
	return 0;
}
