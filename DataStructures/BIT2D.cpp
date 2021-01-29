#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Bit2D {
    int n, m;
    vector<vector<T>> b;

    Bit2D(int n_, int m_) :
        n(n_+2), m(m_+2), b(n, vector<T>(m))
    {}

    // adds delta to position (x, y)
    auto add(int x, int y, T delta) -> void {
        x++, y++;
        for (int i = x; i < n; i += i&-i) {
            for (int j = y; j < n; j += j&-j) {
                b[i][j] += delta;
            }
        }
    }

    // returns sum of rectangle [0, x] x [0, y]
    auto get(int x, int y) -> T {
        x++, y++;
        T ans = 0;
        for (int i = x; i; i -= i&-i) {
            for (int j = y; j; j -= j&-j) {
                ans += b[i][j];
            }
        }
        return ans;
    }

    // returns sum of rectagle defined by [x1, x2] x [y1, y2]
    // generalizable to N-dimensional BIT using inclusion-exclusion principle
    auto get_rectangle(int x1, int x2, int y1, int y2) -> T {
        return get(x2, y2) - get(x1-1, y2) - get(x2, y1-1) + get(x1-1, y1-1);
    }
};