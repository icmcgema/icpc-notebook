#include <bits/stdc++.h>
using namespace std;

// evaluates linear reccurences in O(n^2*log(k)) time
struct LinRec {
    using ll = long long;

    constexpr static int mod = 1e9 + 7;

public:
    // reccurence f[i] defined by vectors c and s
    // f[i+1] = c[0]*f[i] + c[1]*f[i-1] + ... + c[n-1]*f[i-n+1]
    // f[0] = s[0], f[1] = s[1], ..., f[n-1] = s[n-1]
    LinRec(vector<int> const& c_, vector<int> const& s_) : n(c_.size()), c(c_), s(s_) {
        cache[0] = {0, 1};

        for (int i = 1; i < (int)cache.size(); i++) {
            cache[i] = mul(cache[i-1], cache[i-1]);
        }
    }

    // evaluates G(x ^ k mod char_poly(f[x])) = G(x ^ k) = f[k]
    // where G(f[x]) = sum(c[i]*s[i]) from 0 to n
    // O(n^2 * log(k)) time
    ll kth(ll k) {
        if (k < n) return s[k];

        // x ^ k mod char_poly(f[x])
        auto x = fexp(k);

        ll r = 0;
        // G(x)
        for (int i = 0; i < n; i++) {
            r += (ll) x[i] * s[i] % mod;
        }

        return r % mod;
    }

private:
    int n;
    vector<int> c, s;
    array<vector<int>, 64> cache;

    // computes a[x] * b[x] mod characteristic_poly(s) 
    // optimized naive (O(n^2)) implementation
    vector<int> mul(vector<int> const& a, vector<int> const& b) {
        // guarantees an >= bn
        if (a.size() < b.size()) return mul(b, a);

        int const an = a.size(), bn = b.size();
        vector<int> res(an + bn - 1);

        // multiplies a and b, computing per exponent
        for (int i = 0; i < an + bn - 1; i++) {
            int x = min(i, an - 1);
            int y = i - x;

            ll acc = 0;

            if (i < bn) {
                for (; x >= 0; x--, y++) {
                    acc += (ll) a[x] * b[y] % mod;
                }
            }
            else {
                for (; y < bn; x--, y++) {
                    acc += (ll) a[x] * b[y] % mod;
                }
            }

            res[i] = acc % mod;
        }


        // reduces mod char_poly(s)
        for (int i = an+bn-2; i >= n; i--) {
            for (int j = n-1; j >= 0; j--) {
                res[i-j-1] += res[i] * c[j];
            }
        }

        res.resize(min(an + bn - 1, n));
        return res;
    }

    vector<int> fexp(ll k) {
        vector<int> ans = {1};
        for (int i = 0; k > 0; k >>= 1, i++) {
            if (k&1) ans = mul(ans, cache[i]);
        }
        return ans;
    }
};

int main() {

    LinRec a({1, 3}, {1, 2});

    int x;
    cin >> x;

    cout << a.kth(x) << "\n";
}
