const ll INF = 1e18;
struct Edge { int u, v; ll w; };

// Bellman Ford algorithm, and check for negative edges. O(N * M).
bool bellman_ford(vector<Edge> const& edges, vector<ll>& d, int n) {
	d.assign(n, INF);
	d[0] = 0;

	for (int it = 0; it < n; it++) {
		for (Edge const& ed : edges) {
			int u = ed.u, v = ed.v; ll w = ed.w;
			if (d[u] < INF && d[v] > d[u] + w) {
				d[v] = max(-INF, d[u] + w);
			}
		}
	}

	// If it's possible to relax some edge, there is a negative cycle;
	// you can ignore the following code if it isn't necessary to deal with negative edges

	// negative[i] is true if there is a negative cycle in path 0..i
	vector<bool> negative(n);

	for (int it = 0; it < n; it++) {
		for (Edge const& ed : edges) {
			int u = ed.u, v = ed.v; ll w = ed.w;
			if (d[u] == INF) continue;

			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				negative[v] = true;
			}

			if (negative[u]) negative[v] = true;
		}
	}

	// do something with negative edges here
	return negative[n - 1]; // in this case I return if there is a negative cycle from 0 to n - 1
}
