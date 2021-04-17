/*
	Vertices sao one based.
	n = quantos vertices da primeira particao
	m = quantos vertices da segunda particao

	A contagem da primeira particao e da segunda sao independentes

	Qual vertice u conectou?
		resposta: match[u] - n
	Qual vertice v conectou?
		resposta: match[n + v]
*/
struct Kuhn {
	int n, m;
	vector<int> vis, match;
	vector<vector<int>> e;

	Kuhn(){}
	Kuhn(int n, int m) {
		this->n = n;
		this->m = m;
		e.resize(n + 5);
		match.assign(n + m + 5, 0);
		vis.resize(n + m + 5);
	}

	void add_edge(int u, int v) {
		e[u].pb(n + v);
	}

	int dfs(int u) {
		if(vis[u]) return 0;
		vis[u] = 1;

		for(int v : e[u]) {
			if(match[v] == 0 or (match[v] and dfs(match[v]))) {
				match[u] = v;
				match[v] = u;
				return 1;
			}
		}
		return 0;
	}
	int solve() {
		int flag, tot = 0;

		do {
			flag = 0;
			fill(vis.begin(), vis.end(), 0);
			for(int u = 1; u <= n; ++u) {
				if(match[u] == 0 and dfs(u)) tot += (flag = 1);
			}

		} while(flag);
		return tot;
	}
};