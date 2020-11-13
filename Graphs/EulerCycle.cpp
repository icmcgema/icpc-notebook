/* 
	Checa se existe e encontra um caminho euleriano num grafo dado. 
	Works for euler cycle and euler path. If you want euler cycle, change line 36
*/

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int N = 100007;

int deg[N][2], un[N], sz[N];
stack<int> edges[N];

int find(int u) {
	return un[u] == u? u : un[u] = find(un[u]);
}

void unite(int u, int v) {
	u = find(u); v = find(v);
	if(u == v) return;
	if(sz[u] < sz[v]) swap(u, v);
	sz[u] += sz[v];
	un[v] = u;
}

// Retorna 0 se o grafo estiver invalido e o inicio do caminho se estiver correto
int check(int n) {
	int cnt = 0, u;
	for(int i = 1; i <= n; ++i) {
		if(abs(deg[i][0] - deg[i][1]) > 1) return 0;
		cnt += deg[i][0] - deg[i][1] != 0;
		if(deg[i][1] - deg[i][0] == 1) u = i;
	}
	if(cnt == 2 and sz[find(1)] == n) return u; // if euler cycle, change to 'cnt == 0'
	else return 0;
}

// DFS for euler tour
vector<int> path;
void dfs(int u) {
	int v;
	while(edges[u].size()) {
		v = edges[u].top();
		edges[u].pop();
		dfs(v);
	}
	path.pb(u);
}

int main() {
	int n, m, u, v;
	cin >> n >> m;

	for(int i = 1; i <= n; ++i) {
		un[i] = i;
		sz[i] = 1;
	}

	for(int i = 0; i < m; ++i) {
		cin >> u >> v;
		edges[u].push(v);
		deg[u][1]++;
		deg[v][0]++;
		unite(u, v);
	}

	u = check(n);
	if(u == 0) cout << "NO" << endl;
	else {
		cout << "YES" << endl;
		dfs(u);
		reverse(path.begin(), path.end());
		for(int i = 0; i < path.size(); ++i) {
			cout << path[i] << " ";
		}
		cout << endl;
	}
}