#include <bits/stdc++.h>

using namespace std;

namespace GaussianElimination {
	const double EPS = 1e-9;
	const int INF = 2; // it doesn't actually have to be infinity or a big number

	// Retorna o numero de soluções do sistema (0, 1 ou INF). No caso de 1, ans contém a solução
	// Complexidade: O(min(n, m) * m) - n é o numero de colunas e m é o número de linhas
	int gauss(vector<vector<double>> a, vector<double> & ans) {
		int n = a.size();
		int m = a[0].size() - 1;

		vector<int> where(m, -1);
		for(int col = 0, row = 0; col < m and row < n; ++col) {
			int sel = row;
			for(int i = row; i < n; ++i)
				if(abs(a[i][col]) > abs(a[sel][col]))
					sel = i;

			if(abs(a[sel][col]) < EPS)
				continue;
			
			for(int i = col; i <= m; ++i)
				swap(a[sel][i], a[row][i]);
			
			where[col] = row;

			for(int i = 0; i < n; ++i)
				if(i != row) {
					double c = a[i][col] / a[row][col];
					for(int j = col; j <= m; ++j)
						a[i][j] -= a[row][j] * c;
				}
			++row;
		}

		ans.assign(m, 0);
		for (int i = 0; i < m; ++i)
			if (where[i] != -1)
				ans[i] = a[where[i]][m] / a[where[i]][i];
		for(int i = 0; i < n; ++i) {
			double sum = 0;
			for(int j = 0; j < m; ++j)
				sum += ans[j] * a[i][j];
			if(abs(sum - a[i][m]) > EPS)
				return 0;
		}

		for (int i = 0; i < m; ++i)
			if (where[i] == -1)
				return INF;
		return 1;
	}

	const int N = 1e3 + 7;
	// Retorna o numero de soluções do sistema (0, 1 ou INF). No caso de 1, ans contém a solução
	// Complexidade: O(n * m) - n é o numero de colunas e m é o número de linhas
	int gauss (vector<bitset<N>> a, int n, int m, bitset<N> & ans) {
		vector<int> where (m, -1);
		for(int col = 0, row = 0; col < m and row < n; ++col) {
			for(int i = row; i < n; ++i)
				if(a[i][col]) {
					swap(a[i], a[row]);
					break;
				}
			if(!a[row][col])
				continue;
			where[col] = row;

			for(int i = 0; i < n; ++i)
				if(i != row && a[i][col])
					a[i] ^= a[row];
			++row;
		}

		// The rest of implementation is the same as above
		ans = 0;
		for(int i = 0; i < m; ++i)
			if(where[i] != -1)
				ans[i] = a[where[i]][m];
		
		for(int i = 0; i < n; ++i) {
			int sum = 0;
			for(int j = 0; j < m; ++j)
				sum ^= ans[j] * a[i][j];
			if(sum^a[i][m])
				return 0;
		}

		for (int i = 0; i < m; ++i)
			if (where[i] == -1)
				return INF;
		return 1;
	}
};