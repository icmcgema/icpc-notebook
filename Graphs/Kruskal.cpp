#include <bits/stdc++.h>
using namespace std;

namespace Kruskal {
	struct UF {
		vector<int> par;
		UF(int n) {
			par.resize(n);
			iota(par.begin(), par.end(), 0);
		}
		int find(int x) {
			return par[x] == x ? x : par[x] = find(par[x]);
		}
		void merge(int u, int v) {
			u = find(u), v = find(v);
			par[u] = v;
		}
	};

	struct Edge {
		int u, v;
		long long w;
		Edge() {}
		Edge(int u, int v, long long w) : u(u), v(v), w(w) {}
		bool operator<(Edge const& e) const { return w < e.w; }
	};

	vector<Edge> kruskal(int n, vector<Edge>& edg) {
		sort(edg.begin(), edg.end());
		UF uf(n + 1);
		vector<Edge> ans;
		for (Edge const& e : edg) {
			if (uf.find(e.u) != uf.find(e.v)) {
				uf.merge(e.u, e.v);
				ans.push_back(e);
			}
		}
		return ans;
	}
}

int main() {
	using namespace Kruskal;
}