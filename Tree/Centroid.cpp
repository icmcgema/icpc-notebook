#include <bits/stdc++.h>
using namespace std;

int const maxn = 101010;

vector<int> g[maxn];
int cvis[maxn];

namespace Centroid {
    int sz[maxn];
    
    int dfs_sz(int x, int p = -1) {
        sz[x] = 1;
        for (int u : g[x]) {
            if (u == p or cvis[u]) continue;
            sz[x] += dfs_sz(u, x);
        }
        return sz[x];
    }

    int dfs_cent(int tot, int x, int p = -1) {
        for (int u : g[x]) {
            if (u == p or cvis[u]) continue;
            if (sz[u] > tot/2) return dfs_cent(tot, u, x);
        }
        return x;
    }

    int centroid(int x) {
        return dfs_cent(dfs_sz(x), x);
    }

} // end namespace Centroid

// example problem
// find number of simple paths in tree with lenght in range [l, r]

struct BIT {
    int n;
    vector<int> b;

    BIT(int n_) : n(n_+1), b(n) {};

    int get(int p) {
        int r = 0;
        for (int i = p+1; i > 0; i -= i&-i) {
            r += b[i];
        }
        return r;
    } 

    int get(int a, int b) {
        return get(b) - get(a-1);
    }

    void add(int p, int v) {
        for (int i = p+1; i < n; i += i&-i) {
            b[i] += v;
        }
    }
};

BIT bit(maxn);

void dfs_add(int x, int p = -1, int d = 1, int to_add = 1) {
    bit.add(d, to_add);
    for (int u : g[x]) {
        if (u == p or cvis[u]) continue;
        dfs_add(u, x, d+1, to_add);
    }
}

long long dfs_get(int l, int r, int x, int p = -1, int d = 1) {
    if (d > r) return 0;
    long long ans = bit.get(max(0, l - d),  r - d);
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

    bit.add(0, 1);
    for (int u : g[x]) {
        if (cvis[u]) continue;
        ans += dfs_get(l, r, u);
        dfs_add(u);
    }
    dfs_add(x, -1, 0, -1);

    for (int u : g[x]) {
        if (cvis[u]) continue;

        ans += solve(l, r, u);
    }

    return ans;
}

int main () {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, l, r;
    cin >> n >> l >> r;

    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    cout << solve(l, r, 1) << "\n";;
}