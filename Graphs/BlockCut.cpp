#include <bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;
using Gr = vector<vector<int>>;

/*
    Calculates cut edges (bridges), cut nodes (articulation points),
    bicconnected components and builds block-cut tree, all in O(n + m)

    Block cut tree properties:
    => all cut nodes will go to internal nodes; equivalently:
        - cut node cant be leaf, all leaves are blocks
        - cut node has degree at least 2
    => internal block nodes can have 0 nodes
    => degree of cut node in BCT is less or equal to degree of correspondent node in original graph
*/

struct TarjanMisc {
    vector<int> num, low;
    int at = 1;

    // you can also store edge ids
    // important if you have parallel edges
    vector<ii> edges;
    vector<int> art; // art[u] = 1 if u is articulation point
    stack<int> stk; // aux stack for biconnected components calculation
    vector<vector<int>> comps; // the biconnected components

    void dfs(Gr const& g, int u, int p = -1) {
        num[u] = low[u] = at++;
        int nchild = 0;
        stk.push(u);

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
            if (low[v] >= num[u]) {
                if(p != -1) {
                    art[u] = 1;
                }
                
                comps.push_back({u});
                while (comps.back().back() != v)
                    comps.back().push_back(stk.top()), stk.pop();
            }
        }

        if (p == -1 and nchild > 1) art[u] = 1;
    }
    
    // 0 indexed please
    TarjanMisc(Gr const& g) : num(g.size()), low(g.size()), art(g.size()), stk(), comps() {
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

    vector<vector<int>> get_biconnected_components() {
        return comps;
    }

    // to[u] will store to which new node u will go in the tree.
    // In case u is articulation point, it will go to its dedicated node
    Gr get_block_cut_tree(vector<int> * to = nullptr) {
        Gr tree;
        int n = num.size();
        vector<int> id(n);

        int cur = 0;
        auto new_node = [&]() {
            tree.emplace_back();
            return cur++;        
        };

        for (int u = 0; u < n; ++u) 
            if (art[u]) id[u] = new_node();

        for (auto &comp : comps) {
            int node = new_node();
            for (int u : comp)
                if (!art[u]) id[u] = node;
                else {
                    tree[node].push_back(id[u]);
                    tree[id[u]].push_back(node);
                }
        }

        if(to) {
            (*to) = id;
        }

        return tree;
    }
};
