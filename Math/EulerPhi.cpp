#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
 * Phi(x) = qtd de 1 <= y < x tal que gcd(x, y) = 1
 * a^Phi(N) = 1 (mod N) para qualquer a coprimo com N.
 * É uma função multiplicativa
 * A soma de phi(d) para todo d que divide N é N 
 */

namespace EulerPhi {
	const int N = 1000007;
	int phi[N];

	// Builds every phi[x] for small x (x <= 10^6)
	void build() {
		for(int i = 1; i < N; ++i) {
			phi[i] = i;
		}
		for(int i = 1; i < N; ++i) {
			for(int j = i + i; j < N; j += i) {
				phi[j] -= phi[i];
			}
		}
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

 	// finds Phi in sqrt(n)
 	int Phi(int n) {
 		auto fact = factor(n);
 		int ans = 1;
 
 		for(auto [a, b] : fact) {
 			ans *= fast_pow(a, b, n+1) - fast_pow(a, b-1, n+1);
 		}
 		return ans;
	}
}