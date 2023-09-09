// Credits to Victor Forbes - https://github.com/VictorXjoeY/Notebook/blob/master/Number%20Theory/chinese_remainder_theorem.cpp

// NOTE; MOD MUL IS NOT REQUIRED UNLESS OVERFLOW IS EXPECTED - Replace multiplications (lines with // *) by mod_mul() if overflow. 

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

/* O(Log(min(a, b))) - Extended Euclidean Algorithm.
   Returns a solution to a * x + b * y = gcd(a, b).
   Returns |x| <= |a / gcd(a, b)|, |y| <= |b / gcd(a, b)| and gcd(a, b). */
tuple<ll, ll, ll> extended_gcd(ll a, ll b) {
    ll x, y, gcd;

    if (a == 0) {
        return {b, 0ll, 1ll};
    }

    tie(gcd, x, y) = extended_gcd(b % a, a);

    return {gcd, y - (b / a) * x, x};
}


/* O(Log(min(a, b))).
a * x + b * y = c
        x = x1 + k * (b / gcd(a, b))
        y = y1 - k * (a / gcd(a, b))

a * x - b * y = c ---> a * x + b * (-y) = c
        x = x1 + k * (b / gcd(a, b))
        -y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))

-a * x + b * y = c ---> a * (-x) + b * y = c
        -x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
        y = y1 - k * (a / gcd(a, b))

-a * x - b * y = c ---> a * (-x) + b * (-y) = c
        -x = x1 + k * (b / gcd(a, b)) ---> x = -x1 - k * (b / gcd(a, b))
        -y = y1 - k * (a / gcd(a, b)) ---> y = -y1 + k * (a / gcd(a, b))

Use positive values for a and b for this function.
Has infinite solutions if and only if gcd(a, b) divides c.
If a and/or b are 0, treat those cases separately.
Returns |x1| <= |(a * c) / gcd^2(a, b)|, |y1| <= |(b * c) / gcd^2(a, b)| and gcd(a, b) if there are solutions. */
tuple<ll, ll, ll> diophantine(ll a, ll b, ll c) {
    ll gcd, x, y;

    // Obtaining a * x1 + b * y1 = gcd(a, b)
    tie(gcd, x, y) = extended_gcd(a, b);

    // No solution
    if (c % gcd != 0) {
        return {0ll, 0ll, 0ll};
    }

    // Obtaining lcm(a, b).
    ll lcm = (a / gcd) * b;

    // Multiplying the above equation by k = c / gcd to obtain a * x1 + b * y1 = c
    return {gcd, x*(c / gcd)%lcm, y*(c / gcd)%lcm}; // *
}
