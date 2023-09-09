// Credits to Victor Forbes - https://github.com/VictorXjoeY/Notebook/blob/master/Number%20Theory/chinese_remainder_theorem.cpp

/* O(Log(min(a, b))) - Returns a * b mod m without overflowing. 2 * (m - 1) must not overflow. */
ll mod_mul(ll a, ll b, ll m) {
// O(1) - If there's __int128_t available, just multiply.
#ifdef __SIZEOF_INT128__
    return ((__int128_t)a * (__int128_t)b) % m;
#endif

    // In case a >= m or b >= m.
    a = (a % m + m) % m;
    b = (b % m + m) % m;

    // Forcing b to be the smallest.
    if (a < b) {
        swap(a, b);
    }

    ll ans = 0;

    // Decomposing b in binary. Adding to the answer a * 2^0, a * 2^1, a * 2^2, a * 2^4, a * 2^8, ...
    while (b > 0) {
        // If current bit is set.
        if (b & 1ll) {
            ans = (ans + a) % m;
        }

        b >>= 1ll;         // Next bit.
        a = (2ll * a) % m; // Next power of two multiplied by a.
    }

    return ans;
}