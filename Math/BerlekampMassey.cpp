/*
	Acha a menor recorrencia linear para a sequência dada como input.
	Por exemplo, para a sequência
	0 1 1 2 3 5 8 13
	A recorrencia encontrada será f(x) = 1 * f(x-1) + 1 * f(x-2)

	Como aprendido no blog https://codeforces.com/blog/entry/61306
*/

#include <bits/stdc++.h>

#define pb push_back

using namespace std;
typedef long long ll;

namespace BerlekampMassey {
	const int M = 1e9 + 7;

	ll fast_pow(ll a, ll b) {
		ll ans = 1;

		while(b) {
			if(b&1) ans = ans * a % M;
			b >>= 1;
			a = a * a % M;
		}
		return ans;
	}

	inline ll inv(ll x) {
		return fast_pow(x, M - 2);
	}

	/* 
		'vec' eh o array com os primeiros vec.size() numeros da recorrencia 
		'cur' eh o array de coeficientes multiplicados, 
		e deve ser interpretado como vec[i] = cur[0] * vec[i-1] + cur[1] * vec[i-2] + ...
	*/
	vector<ll> solve(vector<ll> vec) {
		const int n = vec.size();

		vector<vector<ll> > S(n, vector<ll>()); // S[i] = recorrencia calculada para o prefixo i, que avalia em 0 para todos os indices de 0 ate i e avalia em 1 para o i+1
		vector<ll> cur = {0}; // recorrencia atual

		S[0] = {1};

		for(int i = 1; i < n; ++i) {
			ll res = 0;
			assert((int) cur.size() <= i);
			for(int j = 0; j < cur.size(); ++j) {
				res = (res + cur[j] * vec[i - 1 - j] % M) % M;
			}

			if(vec[i] == res) continue; // deu certo

			ll v = (res - vec[i] + M) % M; // v tal que vec[i] + v = res

			// Calcula S[i]
			S[i].pb(M-1 * inv(v) % M);
			for(ll x : cur) S[i].pb(x * inv(v) % M);

			// recalcula cur
			int k = 0;
			for(int j = 0; j < i; ++j) {
				if(S[j].size() == 0) continue;
				if(S[j].size() + i - 1 - j <= S[k].size() + i - 1 - k) k = j;
			}

			vector<ll> aux(max(int(S[k].size()) + i - 1 - k, (int) cur.size()));
			for(int j = 0; j < aux.size(); ++j) {
				ll x = j < (i - 1 - k)? 0 : S[k][j - (i - 1 - k)];
				aux[j] = ((vec[i] - res + M) * x % M) + (j < cur.size()? cur[j] : 0);
				aux[j] %= M;
			}

			cur = aux;
		}

		return cur;
	}
};