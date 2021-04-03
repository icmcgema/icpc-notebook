#include <bits/stdc++.h>
using namespace std;

vector<int> linear_sieve(int n) {
    vector<int> low(n+1);
    vector<int> pr;

    for (int i = 2; i <= n; i++) {
        if (low[i] == 0) {
            low[i] = i;
            pr.push_back(i);
        }

        for (int j : pr) {
            if (j > low[i] or i*j > n) break;
            low[i * j] = j;
        }
    }

    return pr;
}