#include <bits/stdc++.h>
using namespace std;

// finds an answer for the assignment problem using
// the hungarian algorithm in O(n^2*m) [O(n^3)]
// everything is 1 indexed
// ans[0] is the cost of the minimum assignment
struct Hungarian {
    constexpr static int inf = numeric_limits<int>::max();

    Hungarian(vector<vector<int>> const& a) :
            n((int)a.size() - 1), m((int)a[0].size() - 1),
            u(n+1), v(m+1), p(m+1), way(m+1) 
    {
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            vector<int> minv (m+1, inf);
            vector<char> used (m+1, false);

            do {
                used[j0] = true;
                int i0 = p[j0],  delta = inf,  j1;
                for (int j = 1; j <= m; j++) {
                    if (!used[j]) {
                        int cur = a[i0][j] - u[i0] - v[j];
                        if (cur < minv[j])
                            minv[j] = cur,  way[j] = j0;
                        if (minv[j] < delta)
                            delta = minv[j],  j1 = j;
                    }
                }
                for (int j = 0; j <= m; j++) {
                    if (used[j])
                        u[p[j]] += delta,  v[j] -= delta;
                    else
                        minv[j] -= delta;
                }
                j0 = j1;
            } while (p[j0] != 0);
            
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
    }

    vector<int> get_ans() {
        vector<int> ans (n+1);
        for (int j=1; j <= m; j++) {
            ans[p[j]] = j;
        }
        ans[0] = -v[0];
        return ans;
    }

    int n, m;
    vector<int> u, v, p, way;
};