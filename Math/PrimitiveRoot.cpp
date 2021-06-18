#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * A raiz primitiva de N é um inteiro g do grupo multiplicativo de N tal que phi(N) é o primeiro k tal que g^k = 1 (mod N)
 * Em outras palavras, g cobre todos os outros elementos do grupo multiplicativo de N.
 * A raiz primitiva de N existe se e somente se alguma das restrições são satisfeitas:
 * - N = 1, 2 ou 4
 * - N = p^k, onde p > 2 é um primo
 * - N = 2 * p^k, onde p > 2 é um primo
 * Se alguma raiz primitiva existir, o número de raizes primitivas de N é phi(phi(N)).
 * A complexidade desse algoritmo pode ser até Nlog(N), mas a complexidade esperada é O(log(N)^6).
 */

namespace PrimitiveRoot {
	int fast_pow(int a, int b, int mod) {
		int ans = 1;
		while(b) {
			if(b&1) ans = 1LL * ans * a % mod;
			a = 1LL * a * a % mod;
			b >>= 1;
		}
		return ans;
	}

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
 			ans *= fast_pow(a, b, n+1) - fast_pow(a, b-1, n+1);
 		}
 		return ans;
	}

	bool exists(int n) {
		auto fact = factor(n);
		return 	n == 1 or n == 2 or n == 4 or
				(fact.size() == 1 and fact.begin()->first > 2) or
				(fact.size() == 2 and fact[2] == 1);
	}

	int find(int n) {
		if(n == 1) return 1;
		if(!exists(n)) return -1;

	    int phi = Phi(n);
	    auto fact = factor(phi);

		for (int res=2; res<=n; ++res) {
			if(__gcd(res, n) > 1) continue; // nao esta no grupo multiplicativo
			bool ok = true;
			for (auto [a, b] : fact) {
				ok &= fast_pow(res, phi / a, n) != 1;
				if(!ok) break;
			}
			if (ok) return res;
		}
	    return -1;
	}

};