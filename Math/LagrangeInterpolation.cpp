#include <bits/stdc++.h>

#define pb push_back

typedef long long ll;
using namespace std;

/**
 * Faz a interpolação de lagrange de um polinomio P(x), porém não encontra os coeficientes do polinomio
 * Se P(x) tem grau deg, e tenho P(x_0), P(x_1), ..., P(x_deg), consigo calcular um P(x) arbitrario em O(deg^2 lg(deg))
 * Se x_0, x_1, ..., x_deg formarem uma P.A., dá pra calcular em O(deg)
 * x_0, x_1, ..., x_deg devem ser todos distintos
 * Repare que deg é o grau do polinomio, mas o polinomio tem deg+1 termos!!
 * Fonte: https://www.notion.so/turci/Lagrange-Interpolation-2c1b2465899146d2a9dd17bf45f16e11
 */
struct Lagrange {
	int deg;
	vector<ll> X, Y;

	// deg = grau do polinomio. O numero de termos do polinomio (e o numero de samples necessario) eh deg + 1
	Lagrange(int deg_ = 0): deg(deg_) {
		X.reserve(deg_ + 1);
		Y.reserve(deg_ + 1);
	}

	/** 
	 * Adiciona o sample (x, y), onde P(x) = y
	 * Todos os x devem ser distintos
	 * Assume que 0 <= x < mod e 0 <= y < mod
	 */
	void add_sample(ll x, ll y) {
		X.pb(x), Y.pb(y);
	}

	ll fast_pow(ll a, ll b, int mod) {
		ll ans = 1;
		while(b) {
			if(b&1) ans = ans * a % mod;
			b >>= 1;
			a = a * a % mod;
		}
		return ans;
	}

 	// Calcula P(x) em O(deg^2 * lg(mod)) 
	ll solve(ll x, int mod) {
		if(X.size() != deg + 1) throw runtime_error("Sem samples suficientes (deg + 1 != #samples)");

		ll ans = 0;
		for(int i = 0; i <= deg; ++i) {
			ll p = Y[i];
			for(int j = 0; j <= deg; ++j) {
				if(j == i) continue;
				p = p * (x - X[j] + mod) % mod;
				p = p * fast_pow(X[i] - X[j] + mod, mod - 2, mod) % mod;
			}
			ans = (ans + p) % mod;
		}
		return ans;
	}

 	// Calcula P(x) em O(deg), se os X[0], X[1], ... X[deg] formarem uma progressao aritmetica 
	ll solve_pa(ll x, int mod) {
		if(X.size() != deg + 1) throw runtime_error("Sem samples suficientes (deg + 1 != #samples)");
		if(deg == 0) return X[0];
		
		const ll d = (X[1] - X[0] + mod) % mod;
		const ll d_n = fast_pow(d, 1LL * deg * (mod - 2), mod);
 
		// calcula fatorial inverso
		vector<ll> inv_fat(deg+1);
		inv_fat[0] = 1;
		for(int i = 1; i <= deg; ++i) inv_fat[i] = inv_fat[i-1] * i % mod;
		inv_fat[deg] = fast_pow(inv_fat[deg], mod - 2, mod);
		for(int i = deg-1; i >= 0; --i) inv_fat[i] = inv_fat[i+1] * (i+1) % mod;
 
		vector<ll> pref(deg + 1), suf(deg + 1);
 
		ll cur = 1;
		for(int i = 0; i <= deg; ++i) {
			cur = cur * (x - X[i] + mod) % mod;
			pref[i] = cur;
		}
 
		cur = 1;
		for(int i = deg; i >= 0; --i) {
			cur = cur * (x - X[i] + mod) % mod;
			suf[i] = cur;
		}
 
		ll ans = 0;
		for(int i = 0; i <= deg; ++i) {
			ll aux = (i? pref[i-1] : 1) * (i < deg? suf[i + 1] : 1) % mod;
			aux = aux * d_n % mod;
			aux = aux * inv_fat[i] % mod;
			aux = aux * inv_fat[deg - i] % mod;
			aux = aux * Y[i] % mod;
			if((deg - i)%2) aux = mod-aux;
			ans = (ans + aux) % mod;
		}
 
		return ans;
	}
};