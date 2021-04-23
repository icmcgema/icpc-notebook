#include <bits/stdc++.h>

#define fi first
#define se second

using namespace std;

const int N = 1e5 + 7;

vector<int> e[N]; // tree

namespace TreeIsomorphism {
	int lev[N], pai[N];

	map<vector<int>, int> mp;
	int cur;

	void dfs(int u, int p = -1, int l = 0) {
		pai[u] = p;
		lev[u] = l;
		for(int v : e[u]) if(v != p) dfs(v, u, l + 1);
	}

	// find centers of tree rooted in r
	ii find_centers(int n) {
		int rr;
		for(int k = 0; k < 2; ++k) {
			int r = k? rr : 1;

			dfs(r);
			
			rr = 1;
			for(int i = 1; i <= n; ++i)
				if(lev[i] > lev[rr]) rr = i;
			
			if(!k) r = rr;
		}
		
		vector<int> aux;
		for(; rr != -1; rr = pai[rr]) aux.pb(rr);

		int sz = aux.size();
		if(sz%2) return ii(aux[sz/2], 0);
		return ii(aux[sz/2], aux[sz/2 - 1]);
	}

	int dfs_hash(int u, int p = -1) {
		vector<ll> vec;

		for(auto v : e[u]) {
			if(v != p) {
				int h = dfs_hash(v);
				vec.eb(h);
			}
		}

		sort(vec.begin(), vec.end());
		if(mp[vec] == 0) mp[vec] = ++cur;
		return mp[vec];
	}

	int rooted_unlabeled_tree_hash(int n, int r) {
		return dfs_hash(r);
	}

	ii unrooted_unlabeled_tree_hash(int n) {
		ii centers = find_centers(n, 1);
		
		int r1 = rooted_unlabeled_tree_hash(n, centers.fi);
		int r2 = rooted_unlabeled_tree_hash(n, centers.se);

		return {r1, r2};
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
}