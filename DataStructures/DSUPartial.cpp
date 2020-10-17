#include <bits/stdc++.h>
using namespace std;

struct DSUPartial {
	int n, curTime;
	std::vector<int> par, sz, tim;

	// Union Find with union by size.
	// "Partially persistent": past states can be seen, but not modified
	// operations in O(log(n))
	DSUPartial(int n) : n(n) {
		par.resize(n + 1);
		tim.resize(n + 1);
		sz = std::vector<int>(n + 1, 1);
		iota(par.begin(), par.end(), 0);
		curTime = 0;
	}

	// find leader of current component on time t
	int find(int x, int t = INT_MAX) {
		return par[x] == x || tim[x] > t ? x : find(par[x], t);
	}

	// merge two components at time t
	// returns whether they don't already belong to the same
	inline bool merge(int u, int v, int t) {
		u = find(u, t), v = find(v, t);
		if (u == v) return false;

		if (sz[u] > sz[v]) std::swap(u, v);
		par[u] = v;
		tim[u] = t;
		sz[v] += sz[u];
		return true;
	}

	// merge two componnets
	// returns whether they don't already belong to the same
	inline bool merge(int u, int v) {
		if (merge(u, v, curTime + 1)) {
			++curTime;
			return true;
		}
		return false;
	}

	// returns whether u and v are at the same component at time t
	inline bool same(int u, int v, int t) {
		return find(u, t) == find(v, t);
	}
};

// Pictionary. https://codeforces.com/gym/102078/problem/A
int main() {
	int n, m, q; scanf("%d%d%d", &n, &m, &q);
	
	DSUPartial uf(n);
	for (int k = m; k >= 1; k--) {
		for (int i = k + k; i <= n; i += k) {
			uf.merge(i, k, m - k + 1);
		}
	}

	while(q--) {
		int u, v; scanf("%d%d", &u, &v);
		int lo = 0, hi = m, mi;
		while(lo < hi) {
			mi = (lo + hi) / 2;
			if (uf.same(u, v, mi)) hi = mi;
			else lo = mi + 1;
		}
		printf("%d\n", hi);
	}
}