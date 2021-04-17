/* https://maps20.kattis.com/problems/thewrathofkahn */
/*
 * Uses Dilworth's theorem (https://www.google.com.br/amp/s/www.geeksforgeeks.org/dilworths-theorem/amp/), that
 * says that the largest anti-chain of a partially ordered set is equal to the minimum number of chains that covers the set
 * 
 * Translating to graph world, chain is a path, partially ordered set is a DAG and the largest anti-chain is the width of the DAG
 * We only have to calculate minimum number of paths to cover a DAG, which is a classic problem and can be calculated with matching
 * 
 * This problem is equivalent to calculating the minimum number of *disjoint* paths to cover the transitive closure of the DAG,
 * which is a DAG where the existence of edge u->v and existence of edge v->w implies existence of edge u->w. Basically, there is
 * an edge u->v in the transitive closure of the DAG if there is a path from u to v in the original DAG.
 * 
 * To calculate this with matching, we can see the graph as if initially there are n paths of length 1 (each node alone). A matching
 * u -> v means, then, that we are merging the path that ends in u with the path that starts with v. So to calculate this we
 * duplicate the graph into a bipartite graph, and add edge u from the left side to v of the right side if u->v is present in the DAG.
 * Since everytime we add an edge we subtract the number of paths by one, because we want the maximum matching, we will achieve the minimum
 * number of paths. 
 * 
 * Another way to see this is as if each edge of the matching will become an edge of the path. But wait, each node can match up with two nodes, not one.
 * That's why we duplicate the nodes, into one (let's call it A) that only receives incoming edges, and another (let's call it B) which only has
 * outgoing edges coming out of it, and there is an implicit edge from A to B to construct the paths. That way, each node can only match with one other node,
 * and matching algorithm can work correctly.
 */
#include "Kuhn.cpp"


namespace DagWidth {

	const int N = 1e5 + 7;
	vector<int> e[N];
	bool vis[N];

	void dfs(int u) {
		vis[u] = true;
		for(int v : e[u]) {
			if(!vis[v]) dfs(v);
		}
	} 
	int solve(int n) {
		// build closure graph

		Kuhn kuhn(n, n);
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) vis[j] = false;

			dfs(i);

			for(int j = 1; j <= n; ++j) {
				if(i == j) continue;
				if(vis[j]) kuhn.add_edge(i, j);
			}
		}

		return kuhn.solve();
	}
};
