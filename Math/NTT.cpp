#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * NTT eh o mesmo que FFT, so que com um *n-th root* diferente
 * MOD tem que ser um primo do tipo p = c * 2^k + 1
 * Com isso, a n-th root existe pra n = 2^k. 
 * Essa n-th root é g^c, onde g é um *primitive root* de 2^k
 */

/**
 * NTT eh o mesmo que FFT, so que com um *n-th root* diferente
 * MOD tem que ser um primo do tipo p = c * 2^k + 1
 * Com isso, a n-th root existe pra n = 2^k. 
 * Essa n-th root é g^c, onde g é um *primitive root* de 2^k
 */

namespace NTT {
	//					~10^5	 	 ~5*10^6	~10^6
	const int mod = 	998244353;// 998244353	7340033
	const int root = 	363395222;// 15311432	5
	const int root_1 = 	704923114;// 469870224	4404020
	const int root_pw = 1 << 19;//	 1 << 23;	1 << 20;

	int fast_pow(int a, int b, int m) {
		int ans = 1;
		while(b) {
			if(b&1) ans = 1LL * ans * a % m;
			a = 1LL * a * a % m;
			b >>= 1;
		}
		return ans;
	}
	int inverse(int x, int m) { return fast_pow(x, m - 2, m); }

	/* <=============================== INICIO ======================================> */
	/** Só quando as constantes acima não forem suficientes */

 	map<int, int> factor(int n) {
 		map<int, int> ans;
 		for(int i = 2; i * i <= n; ++i) {
 			while(n%i == 0) {
 				ans[i]++;
 				n /= i;
 			}
 		}
 		if(n > 1) ans[n]++;
 		return ans;
 	}

 	int Phi(int n) {
 		auto fact = factor(n);
 		int ans = 1;
 
 		for(auto [a, b] : fact) {
 			ans *= fast_pow(a, b, n + 1) - fast_pow(a, b-1, n + 1);
 		}
 		return ans;
	}

	int prim_root(int n) {
	    int phi = Phi(n);
	    auto fact = factor(phi);

		for (int res=2; res<=n; ++res) {
			if(__gcd(res, n) > 1) continue;
			bool ok = true;
			for (auto [a, b] : fact) {
				ok &= fast_pow(res, phi / a, n) != 1;
				if(!ok) break;
			}
			if (ok) return res;
		}
	    return -1;
	}

	// Generates NTT constants for any Mod and prints it on the screen
	void generate(int Mod) {

		int n = 1;
		int aux = Mod-1;
		while((aux&1) == 0) aux >>= 1, n <<= 1;
		int c = aux;

		// g = primitive root de Mod
		int g = prim_root(Mod);
		if(g == -1) {
			printf("No constants could be found, cant find primitive root of %d\n", n);
			return;
		}
		int root = fast_pow(g, c, Mod);
		int root_1 = inverse(root, Mod);
		printf("mod = %d, root = %d, root_1 = %d root_pw = %d\n", Mod, root, root_1, n);
		assert(fast_pow(root, n, Mod) == 1);
		// g^c
	}
	/* ===============================>  FIM  <====================================== */


	inline void ntt(vector<int>& a, bool invert) {
		int n = a.size();
		
		for (int i = 1, j = 0; i < n; i++) {
			int bit = n >> 1;
			for (; j & bit; bit >>= 1)
				j ^= bit;
			j ^= bit;

			if (i < j)
				swap(a[i], a[j]);
		}

		for (int len = 2; len <= n; len <<= 1) {
			int wlen = invert ? root_1 : root;

			for (int i = len; i < root_pw; i <<= 1)
				wlen = 1LL * wlen * wlen % mod;

			for (int i = 0; i < n; i += len) {
				int w = 1;
				for (int j = 0; j < len / 2; j++) {
					int u = a[i+j], v = 1LL * a[i+j+len/2] * w % mod;
					a[i+j] = u + v < mod ? u + v : u + v - mod;
					a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
					w = 1LL * w * wlen % mod;
				}
			}
		}


		if (invert) {
			int n_1 = inverse(n, mod);
			for (int & x : a)
				x = 1LL * x * n_1 % mod;
		}
	}

	vector<int> multiply(vector<int> const& a, vector<int> const& b) {
		vector<int> ca(a.begin(), a.end()), cb(b.begin(), b.end());
		int n = 1;
		while(n < (int) max(a.size(), b.size())) n <<= 1;
		n <<= 1;

		ca.resize(n); cb.resize(n);
		
		ntt(ca, false); ntt(cb, false);
		
		for (int i = 0; i < n; i++) ca[i] = 1LL * ca[i] * cb[i] % mod;
		ntt(ca, true);

		return ca;
	}
};