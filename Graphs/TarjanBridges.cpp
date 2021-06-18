#include <bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;
using Gr = vector<vector<int>>;

struct TarjanBridges {
    vector<int> num, low;
    int at = 1;

    // you can also store edge ids
    // important if you have parallel edges
    vector<ii> edges;
    vector<int> art;

    void dfs(Gr const& g, int u, int p = -1) {
        num[u] = low[u] = at++;
        int nchild = 0;

        for (int v : g[u]) {
            // if graph has parallel edged you should assing an id to every edge
            // and in the next line check if the edge id is the same as the parent edge
            if (v == p) continue;
            if (num[v] != 0) {
                low[u] = min(low[u], num[v]);
                continue;
            }
            dfs(g, v, u);
            low[u] = min(low[u], low[v]);
            nchild++;

            if (low[v] > num[u]) {
                edges.emplace_back(u, v);
            }
            if (p != -1 and low[v] >= num[u]) {
                art[u] = 1;
            } 
        }

        if (p == -1 and nchild > 1) art[u] = 1;
    }
    
    // 0 indexed please
    TarjanBridges(Gr const& g) : num(g.size()), low(g.size()), art(g.size()) {
        int n = g.size();
        for (int i = 0; i < n; i++) {
            if (num[i] == 0) {
                dfs(g, i);
            }
        }
    }

    vector<int> get_articulations() {
        int n = num.size();
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (art[i]) {
                ans.push_back(i);
            }
        }
        return ans;
    }

    vector<ii> get_bridges() {
        return edges;
    }
};