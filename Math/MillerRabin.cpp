#include <bits/stdc++.h>
using namespace std;

namespace MillerRabin {
	using ll = long long;

	ll modmul(ll a, ll b, ll M) {
		#ifdef __SIZEOF_INT128__
			return (__int128) a * (__int128) b % M;
		#endif
			
		ll ans = 0;
		while(b) {
			if(b&1) {
				ans += a;
				if(ans >= M) ans -= M;
			}
			b >>= 1;
			a += a;
			if(a >= M) a -= M;
		}
		return ans;
	}

	ll fast_pow(ll a, ll b, ll M) {
		ll ans = 1;
		while(b) {
			if(b&1) ans = modmul(ans, a, M);
			b >>= 1;
			a = modmul(a, a, M);
		}
		return ans;
	}

	bool isProbablePrime(ll n) {
		if(n <= 1) return false;
		ll d = n-1;
		int k = 0;
		while(!(d&1)) {
			k++;
			d >>= 1;
		}

		auto miller = [&](ll x) {
			ll cur = fast_pow(x, d, n);
			if(cur == 1 or cur == n-1) return false;
			for(int tmp = k; --tmp > 0;) {
				cur = modmul(cur, cur, n);
				if(cur == n-1) return false;
			}
			return true;
		};
		// first 12 prime numbers (deterministic for n <= 2^64)
		for(ll x : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
			if(x == n) return true;
			if(miller(x)) return false;
		}
		return true;
	}
};