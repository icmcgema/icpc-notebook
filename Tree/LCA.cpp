/** Tree struct with LCA (binary lifting) implemented. EDGE struct can be changed, according to the problem. */
const int LOG = 20;
struct Tree {
	struct Edge { int to; }; // you can also add some weight here, etc
	int n;
	vector<int> level;
	vector<vector<int>> par;
	vector<vector<Edge>> edges;
	Tree(int n) : n(n), edges(n) {}

	// add edge from->to. 0-based please.
	void add_edge(int from, int to) {
		edges[from].push_back(Edge{to});
		edges[to].push_back(Edge{from});
	}

	// Initialize in O(n logn)
	inline void init_lca(int root) {
		par.resize(n, vector<int>(LOG));
		level.resize(n);

		auto dfs_lca = [&](auto&& dfs_lca, int u, int p)->void {
			par[u][0] = p;
			for (Edge const& ed : edges[u]) if (ed.to != p) {
				level[ed.to] = level[u] + 1;
				dfs_lca(dfs_lca, ed.to, u);
			}
		};

		dfs_lca(dfs_lca, root, root);
		for (int b = 1; b < LOG; b++) {
			for (int i = 0; i < n; i++) {
				par[i][b] = par[par[i][b-1]][b-1];
			}
		}
	}

	// Finds LCA in O(logn)
	int lca(int u, int v) {
		if (level[u] < level[v]) swap(u, v);
		for (int b = LOG-1; b >= 0; b--) if (level[u] - (1 << b) >= level[v])
			u = par[u][b];
		if (u == v) return u;
		for (int b = LOG-1; b >= 0; b--) if (par[u][b] != par[v][b]) {
			u = par[u][b];
			v = par[v][b];
		}
		return par[u][0];
	}
};