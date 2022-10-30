#include <iostream>
#include <cassert>
using namespace std;
using i64 = int64_t;
#include <div_mod_sums.cpp>

i64 testDivSum(int a, int b, int m, int k) {
    i64 x = a;
    i64 s = 0;
    for (int i = 0; i <= k; i++) {
        s += x / m;
        x += b;
    }
    return s;
}

i64 testModSum(int a, int b, int m, int k) {
    i64 x = a;
    i64 s = 0;
    for (int i = 0; i <= k; i++) {
        s += x % m;
        x += b;
    }
    return s;
}

int main() {
    for (int a = 0; a <= 20; a++) {
        for (int b = 0; b <= 20; b++) {
            for (int m = 1; m <= 200; m++) {
                for (int k = 0; k <= 200; k++) {
                    assert(divSum(a, b, m, k) == testDivSum(a, b, m, k));
                    assert(modSum(a, b, m, k) == testModSum(a, b, m, k));
                }
            }
        }
    }
    return 0;
}
