/*
 *  Calculates dominator tree in O(M * log(N)) 
 *  A dominator of a node u is a node v such that all paths from source to u goes trough v. In other words, 
 *  if you take v off the graph, s and u become disconnected.
 *  A immeadiate dominator idom(u) := the dominator of u closest to u. In the s-DFS tree, it would be the lowest dominator of u
 *  The dominator tree of the graph is the tree were s is the root and edges are idom(u) -> u
 * 
 *  This can also be calculated in O(N * M) more easily with N DFSs, where in i-th DFS you remove node i from the graph
 *
 *  In the end, parent of u in the dominator tree will be pred(u) = inv_tim[idom[tim[u]]], unless u is the source, then it will be itself.
 *  If u is not reachable by the source, pred(u) will be 0
 * 
 *  BE CAREFUL if in your problems there can be nodes not reachable by the source 
 *  BE CAREFUL that label of nodes are changed to the visit time of nodes for every array except "e" and "rev"
 */

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

using namespace std;
typedef pair<int, int> ii;

namespace DominatorTree {
	const int N = 100007;

	vector<int> e[N], rev[N]; // graph, reverse graph
	vector<int> sd[N]; // semidominated, sd[u] = {v | sdom[v] = u}

	int tim[N], inv_tim[N], par[N]; // visit time, inverse function of visit time, parent in the DFS tree
	int sdom[N], idom[N]; // semidominator, immediate dominator
	int un[N], path[N]; // DSU stuff for path compression min query

	// Finds the guy that has least sdom in the ancestors of u, and uses path compression to optimize it
	ii query(int u) {
		if(u == un[u]) return ii(u, u);
		int p;
		tie(p, un[u]) = query(un[u]);
		if(sdom[p] < sdom[path[u]]) path[u] = p;
		return ii(path[u], un[u]);
	}

	int tt;
	void dfs(int u) {
		tim[u] = ++tt;
		inv_tim[tt] = u;
		for(int v : e[u]) {
			if(!tim[v]) {
				dfs(v);
				par[tim[v]] = tim[u];
			}
		}
	}
	void build() {
		for(int u = 1; u <= tt; ++u) sdom[u] = idom[u] = un[u] = path[u] = u;
		for(int u = tt; u >= 1; --u) {
			for(int v : rev[inv_tim[u]]) {
				v = tim[v];
				if(v == 0) continue;
				if(v < u) sdom[u] = min(sdom[u], sdom[v]);
				else sdom[u] = min(sdom[u], sdom[query(v).fi]);
			}
			sd[sdom[u]].pb(u);

			for(int v : sd[u]) {
				int best = query(v).fi;
				if(sdom[best] >= u) idom[v] = u;
				else idom[v] = best;
			}

			for(int v : e[inv_tim[u]]) {
				v = tim[v];
				if(v == 0) continue;
				if(par[v] == u) un[v] = u; // if u->v is tree edge, add it
			}
		}
		for(int u = 1; u <= tt; ++u) 
			if(idom[u] != sdom[u]) idom[u] = idom[idom[u]];
	}

};

int main() {
	using namespace DominatorTree;

    // Reads n = number of vertices, m = number of edges and s = source vertice.
    int n, m, s; cin >> n >> m >> s; 

    // Read the graph
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        e[u].pb(v);
        rev[v].pb(u); // Need to add reversed graph
    }

    dfs(s);
    build();

    for(int i = 1; i <= n; ++i) {
        cout << inv_tim[idom[tim[i]]] << ' ';
    }
    cout << endl;
}