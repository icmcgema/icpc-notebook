#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using Gr = vector<vector<ii>>;

// returns empty if there is no negative cycle in graph g
// else returns any negative cycle in g
// complexity O(V * E), but actually much faster in almost all cases
// if graph has no negative cycles expected time O(E)
optional<vector<int>> negative_cycle(Gr& g) {
    int n = g.size();
    g.emplace_back();
    for (int i = 0; i < n; i++) {
        g.back().emplace_back(i, 0);
    }
    n++;

    int src = n-1;

    vector<char> in_queue(n);
    vector<int> len(n), pre(n);
    vector<ll> d(n, numeric_limits<ll>::max() / 2);
    deque<int> q;

    q.push_back(src);
    in_queue[src] = 1;
    d[src] = 0;

    auto recover = [&] (int u) {
        vector<char> in_stack(n);
        stack<int> s;

        while (!in_stack[u]) {
            s.push(u);
            in_stack[u] = 1;
            u = pre[u];
        }

        vector<int> cyc = {u};
        while (s.top() != u) {
            cyc.push_back(s.top());
            s.pop();
        }

        return cyc;
    };

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();

        in_queue[u] = 0;

        for (auto [v, w] : g[u]) {
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                pre[v] = u;
                len[v] = len[u] + 1;

                // cycle detected
                if (len[v] == n) {
                    return recover(v);
                }

                if (!in_queue[v]) {
                    if (!q.empty() and d[q.front()] >= d[v])
                        q.push_front(v);
                    else
                        q.push_back(v);

                    in_queue[v] = 1;
                }
            }
        }
    }

    return {};
}