#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <cassert>
#include <iostream>
using namespace std;

#include <link_cut_tree.cpp>

mt19937 mt;

pair<vector<pair<int, int>>, int> gen_tree(int n) {
	vector<int> p(n);
	for (int i = 0; i < n; i++)
		p[i] = i;
	shuffle(p.begin(), p.end(), mt);
	vector<pair<int, int>> t;
	for (int i = 1; i < n; i++) {
		uniform_int_distribution<int> gen(0, i - 1);
		t.emplace_back(p[i], p[gen(mt)]);
	}
	shuffle(t.begin(), t.end(), mt);
	return {t, p[0]};
}

void test_depth() {
	const int n = 100;
	const int m = 10000;
	pair<vector<pair<int, int>>, int> t = gen_tree(n);
	vector<vector<int>> g(n);
	vector<int> vd(n);
	LinkCutTree lct(n);
	for (auto e : t.first) {
		g[e.first].push_back(e.second);
		g[e.second].push_back(e.first);
		lct.link(e.first, e.second);
	}
	function<void(int, int, int)> dfs = [&](int x, int p, int d) {
		vd[x] = d;
		for (int y : g[x]) {
			if (y != p) {
				dfs(y, x, d + 1);
			}
		}
	};
	dfs(t.second, -1, 0);
	for (int i = 0; i < m; i++) {
		uniform_int_distribution<int> gen(0, n - 1);
		int x = gen(mt);
		assert(vd[x] == lct.depth(x));
	}
}

int main() {
	test_depth();

	return 0;
}