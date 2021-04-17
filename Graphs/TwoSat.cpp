struct TwoSat {
	int n; // amount of VERTICES (2 * variables)

	vector<vector<int>> edges, reved;

	// N is the amount of VERTICES!!! n = 2 * VARIABLES!!!
	TwoSat(int n) : n(n), edges(n), reved(n) {}
 
 	// i is variable, return vertex id
	inline static int pos(int i) { return i + i; }
	inline static int neg(int i) { return i + i + 1; }
	inline static int getNot(int i) { return i ^ 1; }

	inline void addEdge(int u, int v) { // 0-based pls!
		edges[u].push_back(v);
		edges[getNot(v)].push_back(getNot(u));
		reved[v].push_back(u);
		reved[getNot(u)].push_back(getNot(v));
	}
 
	void dfsOrder(int u, vector<int>& vis, vector<int>& order) {
		vis[u] = 1;
		for (int v : edges[u]) if (!vis[v])
				dfsOrder(v, vis, order);
		order.pb(u);
	}

	void dfsSCC(int u, int c, vector<int>& comp) {
		comp[u] = c;
		for (int v : reved[u]) if (!comp[v])
				dfsSCC(v, c, comp);
	}
 
	/** verify satisfiability */
	inline bool isSat(vector<int>& states) {
		states.assign(n / 2, -1);
		vector<int> color(n);
		vector<int> order;
		for (int i = 0; i < n; i++) if (!color[i])
				dfsOrder(i, color, order);
		reverse(order.begin(), order.end());
		fill(color.begin(), color.end(), 0);
		for (int i = 0, c = 0; i < n; i++) if (!color[order[i]])
				dfsSCC(order[i], ++c, color);
		for (int i = 0; i < n; i += 2) {
			if (color[i] == color[i+1])
				return false;
		}
		for (int i = n - 1; i >= 0; i--) {
			if (states[order[i] / 2] == -1)
				states[order[i] / 2] = !(order[i]&1);
		}
		return true;
	}
};
