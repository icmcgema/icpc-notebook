#include <bits/stdc++.h>
using namespace std;

struct TarjanSCC {
    using Gr = vector<vector<int>>;

    stack<int> st;
    vector<int> num, low, vis;
    vector<int> sccs;
    int idx = 1, n_sccs = 0;

    // 0 indexed please
    TarjanSCC(Gr const& g) : num(g.size()), low(g.size()), vis(g.size()), sccs(g.size()) {
        int n = g.size();
        for (int i = 0; i < n; i++) {
            if (num[i] == 0) dfs(g, i);
        }
    }

    void dfs(Gr const& g, int u) {
        num[u] = low[u] = idx++;
        st.push(u);
        vis[u] = 1;

        for (int v : g[u]) {
            if (num[v] == 0) {
                dfs(g, v);
                low[u] = min(low[u], low[v]);
            }
            else if (vis[v]) {
                low[u] = min(low[u], num[v]);
            }
        }

        if (low[u] == num[u]) {
            while (true) {
                int x = st.top();
                st.pop();
                vis[x] = 0;
                sccs[x] = n_sccs;
                if (x == u) break;
            }
            n_sccs++;
        }
    }

    // returns pair< vector v, where: v[x] = index of x's scc, 
    //               int n, where : n = number of sccs >
    // the sccs come in reverse topological order
    // scc[0] < scc[1] < scc[2] < ...
    // scc[x] represent the set of vertex with scc index x
    pair<vector<int>, int> get_sccs() {
        return {sccs, n_sccs};
    }

    // returns the same as above + compressed graph of the components
    tuple<Gr, vector<int>, int> compressed_g(Gr const& gr) {
        auto gc = vector<vector<int>>(n_sccs);
        int n = gr.size();
        for (int u = 0; u < n; u++) {
            for (int v : gr[u]) {
                if (sccs[u] != sccs[v]) {
                    gc[sccs[u]].push_back(sccs[v]);
                }
            }
        }
        for (auto& l : gc) {
            sort(l.begin(), l.end());
            l.erase(unique(l.begin(), l.end()), l.end());
        }

        return {gc, sccs, n_sccs};
    }
};