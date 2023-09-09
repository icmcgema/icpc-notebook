// Credits to Victor Forbes - https://github.com/VictorXjoeY/Notebook/blob/master/Number%20Theory/chinese_remainder_theorem.cpp

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
