/** Minimum Cost Maximum Flow using Johnson's Algo (potential function). O(V^2 * logV + V * E) */

template<typename T>
struct MCMF {
	T flow_inf = numeric_limits<T>::max() / 2;
	using pti = pair<T, int>;
	using pii = pair<int, int>;

	struct Edge {
		int to;
		T cost, cap, flow;
		int rid;

		Edge() : to(), cost(), cap(), flow(), rid() {}
		Edge(int to, T cost, T cap, T flow, int rid) :
				to(to), cost(cost), cap(cap), flow(flow), rid(rid) {}
	};

	vector<vector<Edge>> edges;
	vector<T> h, dist;
	vector<pii> par;

	int n;
	MCMF(int n) : n(n) {
		edges.resize(n+1);
		h.resize(n+1);
		dist.resize(n+1);
		par.resize(n+1);
	}

	void add_edge(int u, int v, T cost, T cap) {
		edges[u].emplace_back(v, cost, cap, 0, (int) edges[v].size());
		edges[v].emplace_back(u, -cost,  0, 0, (int) edges[u].size() - 1);
	}

	void bellman_ford(int s) {
		fill(h.begin(), h.end(), flow_inf);
		h[s] = 0;

		for (int i = 0; i < n - 1; i++) {
			for (int at = 0; at < n; at++) {
				for (int j = 0; j < (int) edges[at].size(); j++) {
					if (!edges[at][j].cap)  continue;
					int next = edges[at][j].to;
					T w = edges[at][j].cost;
					h[next] = min(h[next], h[at] + w);
				}
			}
		}
	}

	bool dijkstra(int s, int t) {
		fill(dist.begin(), dist.end(), flow_inf);
		fill(par.begin(), par.end(), mk(-1, -1));
		priority_queue<pti, vector<pti>, greater<pti> > pq;

		dist[s] = 0;
		pq.emplace(0, s);
		bool ret = false;

		while (!pq.empty()) {
			int at = pq.top().se;
			T d = pq.top().fi;
			pq.pop();

			if (at == t) ret = true;
			if (d != dist[at]) continue;

			for (int i = 0; i < (int) edges[at].size(); i++) {
				Edge edg = edges[at][i];
				int next = edg.to;
				if (edg.cap - edg.flow <= 0) continue;
				T w = dist[at] + edg.cost + h[at] - h[next];
				if (dist[next] > w) {
					dist[next] = w;
					par[next] = {at, i};
					pq.emplace(dist[next], next);
				}
			}
		}

		for (int i = 0; i <= n; i++)
			if (h[i] < flow_inf and dist[i] < flow_inf)
				h[i] += dist[i];

		return ret;
	}

	pair<T, T> flow(int s, int t) {
		T cost = 0, flow = 0;
		bellman_ford(s);

		while (dijkstra(s, t)) {
			T f = flow_inf;
			for (int at = t; at != s; at = par[at].fi) {
				Edge edg = edges[par[at].fi][par[at].se];
				f = min(f, edg.cap - edg.flow);
			}
			flow += f;
			for (int at = t; at != s; at = par[at].fi) {
				Edge &edg = edges[par[at].fi][par[at].se];
				edg.flow += f;
				edges[edg.to][edg.rid].flow -= f;
				cost += edg.cost * f;
			}
		}

		return mk(cost, flow);
	}
};
