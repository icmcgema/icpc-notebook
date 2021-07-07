#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

struct UnionFind {
	vector<int> un, sz;
	stack<ii> ops;
	stack<int> checkpoints;

	UnionFind(){}
	UnionFind(int n) {
		un.resize(n + 5);
		sz.assign(n + 5, 1);
		iota(un.begin(), un.end(), 0);
	}

	int find(int u) {
		return un[u] == u? u : find(un[u]);
	}

	void unite(int u, int v) {
		u = find(u); v = find(v);
		if(u == v) return;

		if(sz[v] > sz[u]) swap(u, v);

		ops.emplace(v, un[v]);
		un[v] = u;
		ops.emplace(u, sz[u]);
		sz[u] += sz[v];
	}

	void save() {
		checkpoints.emplace(ops.size());
	}

	void undo() {
		if(ops.size() == 0) return;
		assert(ops.size()%2 == 0);
		for(int i = 0; i < 2; i++) {
			auto [a, b] = ops.top(); ops.pop();
			if(i == 0) {
				sz[a] = b;
			} else {
				un[a] = b;
			}
		}
	}

	void rollback() {
		if(checkpoints.size() == 0) return;
		while(ops.size() > checkpoints.top()) {
			undo();
		}

		checkpoints.pop();
	}
};
