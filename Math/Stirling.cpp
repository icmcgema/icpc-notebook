#include <bits/stdc++.h>

using namespace std;
using ll = long long;



/*
 * Stirling Numbers do primeiro e segundo tipo
 * 1o: F(n+1, k) = F(n, k-1) + n * F(n, k)
 * 2o: F(n+1, k) = F(n, k-1) + k * F(n, k)
 *
 */

namespace Stirling {
	const int N = 5007;
	int stirling[N][N];

	/** Usa a recorrencia F(n+1, k) = F(n, k-1) + ? * F(n, k), onde ? = N se kind = 1, e ? = K se kind = 2 */
	void build(int kind, int mod = 1e9 + 7) {
		stirling[0][0] = 1;
		for(int n = 1; n < N; n++) {
			for(int k = 1; k < N; k++) {
				const int x = kind == 1? n-1 : k;
				stirling[n][k] = (stirling[n-1][k-1] + 1LL * x * stirling[n-1][k] % mod) % mod; 
			}
		}
	}

	int fast_pow(int a, int b, int mod) {
		int ans = 1;
		while(b) {
			if(b&1) ans = 1LL * ans * a % mod;
			b >>= 1;
			a = 1LL * a * a % mod;
		}
		return ans;
	}

	/** 
	 * Retorna um vector com S1(n, 1), S1(n, 2), ..., S1(n, n)
	 * Faz isso calculando x * (x + 1) * (x + 2) * ... * (x + n - 1)
	 * S1(n, k) = coeficiente de x^k
	 * Nao esquecer de configurar corretamente as constantes do NTT, dependendo do seu MOD
	 * Complexidade: O(n log(n))
	 * Precisa incluir codigo de NTT
	 */
	vector<int> stirling1(int n) {
		
		int nn = 1;
		while(nn < n) nn <<= 1;

		vector<vector<int> > pol(nn);

		// inicializa (x + i)
		for(int i = 0; i < n; ++i) {
			pol[i] = {i, 1};
		}
		
		// preenche o resto com (1)
		for(int i = n; i < nn; ++i) {
			pol[i] = {1};
		}

		// multiplica todos os s[i] com NTT
		for(int j = nn; j > 1; j >>= 1){
			int hn = j >> 1;
			for(int i = 0; i < hn; ++i) {
				pol[i] = NTT::multiply(pol[i], pol[i + hn]);
			}
		}

		return pol[0];
	}

	/** Calcula S2(n, k) em O(k log(n)), usando fórmula de convolução */
	int stirling2(int n, int k, int mod) {

		// calcula fatorial inverso
		vector<ll> inv_fat(k+1);
		inv_fat[0] = 1;
		for(int i = 1; i <= k; ++i) inv_fat[i] = inv_fat[i-1] * i % mod;
		inv_fat[k] = fast_pow(inv_fat[k], mod - 2, mod);
		for(int i = k-1; i >= 0; --i) inv_fat[i] = inv_fat[i+1] * (i+1) % mod;
	
		int ans = 0;
		for(int i = 0; i <= k; ++i) {
			int a = i%2? mod - inv_fat[i] : inv_fat[i];
			int b = inv_fat[k - i] * fast_pow(k - i, n, mod) % mod;
			ans = (ans + 1LL * a * b % mod) % mod;
		}

		return ans;
	}

	/** 
	 * Calcula S2(n, k) pra todo k de 0 ate n, usando convolucao com NTT
	 * Nao esquecer de configurar corretamente as constantes do NTT, dependendo do seu MOD
	 * Precisa incluir codigo de NTT
	 * Complexidade: O(n log(n))
	 */
	vector<int> stirling2(int n, int mod) {

		// calcula fatorial inverso
		vector<ll> inv_fat(n+1);
		inv_fat[0] = 1;
		for(int i = 1; i <= n; ++i) inv_fat[i] = inv_fat[i-1] * i % mod;
		inv_fat[n] = fast_pow(inv_fat[n], mod - 2, mod);
		for(int i = n-1; i >= 0; --i) inv_fat[i] = inv_fat[i+1] * (i+1) % mod;

		vector<int> a(n+1), b(n+1);
		for(int i = 0; i <= n; ++i) {
			a[i] = i%2? mod - inv_fat[i] : inv_fat[i];
			b[i] = inv_fat[i] * fast_pow(i, n, mod) % mod;
		}

		return NTT::multiply(a, b);
	}

	/** Paridade de S2(n, k), em O(1) */
	int second_kind_parity(int n, int k) {
		return ( (n-k) & ((k-1)/2) ) == 0;
	}
};