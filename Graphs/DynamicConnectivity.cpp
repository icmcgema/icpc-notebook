#include <bits/stdc++.h>
using namespace std;
 
using ii = pair<int, int>;

struct Dsu {
    int n;
    vector<int> pai, w;
    vector<ii> rb;
    
    Dsu(int n_) : n(n_), pai(n+1), w(n+1, 1) {
        iota(pai.begin(), pai.end(), 0);
    }
 
    int find(int x) {
        if (pai[x] == x) return x;
        return find(pai[x]);
    }
 
    void join(int a, int b) {
        a = find(a), b = find(b);
        
        if (a != b) {
            if (w[a] < w[b]) swap(a, b);
            rb.emplace_back(b, pai[b]);
            rb.emplace_back(a, w[a]);
 
            pai[b] = a;
            w[a] += w[b];
            n--;
        }
        else {
            rb.emplace_back(0, 0);
        }
    }
 
    void rollback() {
        if (rb.back() == ii{0, 0}) {
            rb.pop_back();
            return;
        }
 
        auto f = [this] (auto& v) {
            auto [pos, val] = this->rb.back();
            this->rb.pop_back();
            v[pos] = val;
        };
        
        f(w);
        f(pai);
        n++;
    }
};

struct DynConnectivity {
    int n, k;
    vector<vector<ii>> tree;
    Dsu dsu;

    DynConnectivity(int n_, int k_) : n(n_), k(k_), tree((k+1)*4), dsu(n) {}; 

    void add(int no, int l, int r, int a, int b, ii const& u) {
        if (a <= l and r <= b) {
            tree[no].push_back(u);
            return;
        }
        if (l == r) return;
    
        int m = (l+r)/2;
    
        if (a <= m) add(no*2, l, m, a, b, u);
        if (b > m) add(no*2+1, m+1, r, a, b, u);
    }
    
    // marks the existence of the edge u between the times a and b
    void add(int a, int b, ii const& u) {
        add(1, 0, k, a, b, u);
    }

    void solve(vector<int>& res, int no, int l, int r) {
        for (auto& [a, b] : tree[no]) {
            dsu.join(a, b);
        }
    
        if (l == r) {
            res[l] = dsu.n;
        }
        else {
            int m = (l+r)/2;
            solve(res, no*2, l, m);
            solve(res, no*2+1, m+1, r);
        }
    
        for (int i = 0; i < (int)tree[no].size(); i++) dsu.rollback();
    }

    vector<int> solve() {
        vector<int> v(k+1);
        solve(v, 1, 0, k);
        return v;
    }
};

// example solution
// solution for the problem - Dynamic Connectivity
// https://cses.fi/problemset/task/2133/
// given a graph with n vertex and m edges originally and k toggle edge
// operations, find the number of components before the first and 
// after each operation

int main() {
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
 
    int n, m, k;
    cin >> n >> m >> k;
    
    DynConnectivity dyn(n, k);

    set<ii> g;
    map<ii, int> gt;
 
    while (m--) {
        int x, y;
        cin >> x >> y;
 
        if (x > y) swap(x, y);
 
        gt[{x, y}] = 0;    
    }
    
    // for every edge finds the times of start and end of the edge
    for (int i = 1; i <= k; i++) {
        int op, x, y;
        cin >> op >> x >> y;
 
        if (x > y) swap(x, y);
 
        if (op == 1) {
            gt[{x, y}] = i;
        }
        else {
            auto it = gt.find({x, y});
            int ini = it->second;
            gt.erase(it);
 
            dyn.add(ini, i-1, {x, y});
        }
    }
    
    // the edges that exist afer everything is done
    for (auto [p, key] : gt) {
        dyn.add(key, k, p);
    }
 
    auto res = dyn.solve();
    
    for (int i = 0; i <= k; i++) {
        cout << res[i] << " \n"[i==k];
    }
}