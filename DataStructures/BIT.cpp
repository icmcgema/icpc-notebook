#include <bits/stdc++.h>
using namespace std;

// can be used with all operations that have an inverse
// can also be used in special situation if you dont need an inverse operation 
// eg. the operation is max and the numbers added are increasing
template<typename T>
struct BIT {
// if you need it to cover a dynamic range such as from 0 to 1e9:
// change vector to map and choose an upper limit insted of b.size()s
    vector<T> b;

    BIT() = default;
    BIT(int n) : b(n+1) {};

// if you want to access position 0, add pos++ in the first line
    auto add(int pos, T x) -> void {
        for (int i = pos; i < (int)b.size(); i += i&-i) {
            b[i] += x;
        }
    }

// if you want to access position 0, add pos++ in the first line
    auto get(int pos) -> T {
        T r = 0;
        for (int i = pos; i > 0; i -= i&-i) {
            r += b[i];
        }
        return r;
    }

    auto get(int l, int r) -> T {
        return get(r) - get(l-1);
    }
};

// https://www.spoj.com/problems/INVCNT/
auto main() -> int {
    ios::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto& i : v) cin >> i;

        auto com = v;
        sort(com.begin(), com.end());

        for (auto& i : v) {
            i = lower_bound(com.begin(), com.end(), i) - com.begin() + 1;
        }

        BIT<int> bit(n);
        long long ans = 0;
        for (auto i : v) {
            ans += bit.get(i+1, n);
            bit.add(i, 1);
        }

        cout << ans << '\n';
    }
}