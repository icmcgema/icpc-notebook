struct Dinic {
	const long long flow_inf = 1e18;

	struct FlowEdge {
		int from, to;
		long long cap, flow = 0;
		FlowEdge(int from, int to, long long cap) : from(from), to(to), cap(cap) {}
	};

	vector<FlowEdge> edges;
	vector<vector<int>> adj;
	vector<int> level, ptr;

	Dinic(int n) : adj(n), level(n), ptr(n) {}

	inline void add_edge(int from, int to, long long cap) {
		adj[from].push_back(edges.size());
		edges.emplace_back(from, to, cap);
		adj[to].push_back(edges.size());
		edges.emplace_back(to, from, 0);
	}

	inline bool bfs(int src, int snk) {
		fill(level.begin(), level.end(), -1);
		level[src] = 0;

		vector<int> q = {src};
		for (int i = 0; i < (int) q.size(); i++) {
			int u = q[i];
			for (int id : adj[u]) {
				if (edges[id].cap - edges[id].flow > 0 && level[edges[id].to] == -1) {
					level[edges[id].to] = level[u] + 1;
					q.push_back(edges[id].to);
				}
			}
		}

		return level[snk] != -1;
	}

	long long dfs(int u, int snk, long long pushed) {
		if (u == snk || pushed == 0) return pushed;		

		for (int& cid = ptr[u]; cid < (int) adj[u].size(); cid++) {
			int id = adj[u][cid];
			int v = edges[id].to;
			
			if (level[u] + 1 != level[v] || edges[id].cap - edges[id].flow < 1) continue;
			long long tr = dfs(v, snk, min(pushed, edges[id].cap - edges[id].flow));
			if (tr == 0) continue;

			edges[id].flow += tr;
			edges[id^1].flow -= tr;
			return tr;
		}

		return 0;
	}

	long long flow(int src, int snk) {
		long long f = 0;
		while (bfs(src, snk)) {
			fill(ptr.begin(), ptr.end(), 0);
			while (long long pushed = dfs(src, snk, flow_inf)) f += pushed;
		}
		return f;
	}
};
