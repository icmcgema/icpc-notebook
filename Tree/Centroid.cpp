#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <utility>
#include <tuple>
 
#include <cstdio>
 
using namespace std;
using ll = long long;
 
int const maxn = 202020;
 
vector<vector<int>> g;
vector<char> cvis;
vector<int> sz;
 
namespace Centroid {
    
    int dfs_sz(int x, int p = -1) {
        sz[x] = 1;
        for (int u : g[x]) {
            if (u == p or cvis[u]) continue;
            sz[x] += dfs_sz(u, x);
        }
        return sz[x];
    }
 
    int dfs_cent(int tot, int x, int p = -1) {
        int cent = x;
        for (int u : g[x]) {
            if (u == p or cvis[u]) continue;
            if (sz[u] > tot/2) {
                sz[x] -= sz[u];
                sz[u] += sz[x];
                cent = dfs_cent(tot, u, x);
                break;
            }
        }
        return cent;
    }
 
    int centroid(int x) {
        if (sz[x] == 0) dfs_sz(x);
        int cent = dfs_cent(sz[x], x);
        return cent;
    }
 
} // end namespace Centroid
 
// EXAMPLE PROBLEM
// COUNT NUMBER OF PATHS WITH LENGHT IN [L, L+1, ..., R]
struct PartialSum {
    vector<ll> path_cnt_acc, path_cnt;
    int max_idx = 0;
 
    PartialSum(int n) : path_cnt_acc(n), path_cnt(n) {};
 
    void clear() {
        fill(begin(path_cnt), begin(path_cnt) + max_idx + 1, 0);
        max_idx = 0;
    }
 
    inline void add(int i, ll d) {
        max_idx = max(max_idx, i);
        path_cnt[i] += d;
    }
 
    void recompute() {
        for (int i = 0; i <= max_idx; i++) {
            path_cnt_acc[i] = path_cnt[i] + (i > 0 ? path_cnt_acc[i-1] : 0);
        }
    }
 
    inline ll get_range(int l, int r) {
        ll ans = path_cnt_acc[min(max_idx, r)];
        if (l > 0) ans -= path_cnt_acc[min(max_idx, l-1)];
        return ans;
    }
};
 
PartialSum sum(maxn);
 
void dfs_add(int x, int p = -1, int d = 1, int to_add = 1) {
    sum.add(d, to_add);
    for (int u : g[x]) {
        if (u == p or cvis[u]) continue;
        dfs_add(u, x, d+1, to_add);
    }
}
 
long long dfs_get(int l, int r, int x, int p = -1, int d = 1) {
    if (d > r) return 0;
    ll ans = sum.get_range(l - d,  r - d);
    for (int u : g[x]) {
        if (u == p or cvis[u]) continue;
        ans += dfs_get(l, r, u, x, d + 1);
    }
    return ans;
}
 
long long solve(int l, int r, int x) {
    x = Centroid::centroid(x);
    cvis[x] = 1;
 
    long long ans = 0;
 
    if (g[x].empty()) return 0;
    sort(
        g[x].begin(),
        g[x].end(), 
        [&] (auto lhs, auto rhs) {
            return tie(cvis[lhs], sz[lhs]) < tie(cvis[rhs], sz[rhs]); 
        }
    );
    
    sum.add(0, 1);
    sum.recompute();
    int last = -1;
    for (int u : g[x]) {
        if (cvis[u]) break;
        if (last != -1) {
            dfs_add(last);
            sum.recompute();
        }
        ans += dfs_get(l, r, u);
        last = u;
    }
 
    sum.clear();
 
    for (int u : g[x]) {
        if (cvis[u]) break;
        ans += solve(l, r, u);
    }
    return ans;
}
 
int main () {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n, l, r;
    cin >> n >> l >> r;
    
    g.resize(n+1);
 
    cvis.resize(n+1);
    sz.resize(n+1);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
 
        g[a].push_back(b);
        g[b].push_back(a);
    }
 
    cout << solve(l, r, 1) << "\n";
}