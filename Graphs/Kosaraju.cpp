#include "bits/stdc++.h"

#define pb push_back

using namespace std;

namespace Kosaraju {
	#define ind(x) (x-1)

	vector<vector<int>> g, rev;
	vector<int> col, topo;

	void dfs_topo(int u) {
		col[ind(u)] = 1;
		for(int v : g[ind(u)]) {
			if(!col[ind(v)]) dfs_topo(v);
		}
		topo.pb(u);
	}

	void dfs_scc(int u, int c) {
		col[ind(u)] = c;
		for(int v : rev[ind(u)]) {
			if(!col[ind(v)]) dfs_scc(v, c);
		}
	}

	// receives a graph, where g_[u-1] contains nodes adjacent to node u
	// and returns the colors (ids of SCCs of each node of the input graph)
	// Also, optionally returns the edges of the new graph. 
	// WARNING: Output graph may have MULTIPLE EDGES!!!!
	vector<int> solve(const vector<vector<int>> & g_, vector<vector<int>> * out = nullptr) {
		g = g_;
		int n = g.size();

		rev.assign(n, vector<int>());
		col.assign(n, 0);

		// calc reverse edges
		for(int i = 1; i <= n; ++i) {
			for(int v : g[ind(i)]) {
				rev[ind(v)].pb(i);
			}
		}

		for(int i = 1; i <= n; ++i) {
			if(!col[ind(i)]) dfs_topo(i);
		}
		fill(col.begin(), col.end(), 0);

		assert(topo.size() == n);
		reverse(topo.begin(), topo.end());
		int c = 0;
		for(int u : topo) {
			if(!col[ind(u)]) dfs_scc(u, ++c);
		}

		if(out) {
			vector<vector<int>> ret(c);
			for(int i = 1; i <= n; ++i) {
				for(int v : g[ind(i)]) {
					
					if(col[ind(i)] != col[ind(v)]) {
						// cout << col[ind(i)] << endl;
						// cout << col[ind(v)] << endl;
						ret[ind(col[ind(i)])].pb(col[ind(v)]);
					}
				}
			}
			*out = ret;
		}

		return col;
	}
};
