// solution for https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3616

#include <bits/stdc++.h>

using namespace std;

/*
	O casamento estavel tradicional é entre N homens e N mulheres.
	Aqui a gente assume que esses numeros podem diferir, o que implica que alguem vai ficar sem par
	Aqui nos temos N homens e M mulheres (N proposers e M proposees). O resultado vai ser otimo pros proposers
	homens (proposers) vao de 1 a N
	mulheres (proposees) vao de 1 a M
*/
struct StableMarriage {
	int n, m;
	vector<vector<int> > prior; // lista de preferencias dos homens
	vector<unordered_map<int, int> > rank; // rank[i][x] = indice do homem x (do primeiro conjunto), na lista de preferencias da mulher i (do segundo conjunto) 

	// n proposers, m proposees
	StableMarriage(int n, int m) {
		this->n = n, this->m = m;
		prior.resize(n + 1);
		rank.resize(m + 1);
	}

	void setPreferencesMan(int x, vector<int> vec) {
		prior[x] = vec;
	}

	void setPreferencesWoman(int y, vector<int> vec) {
		int cur = 0;
		for(int x : vec) {
			rank[y][x] = cur++;
		}
	}

	// retorna ans (1-based!!!), onde ans[x] = mulher com quem x casou, ou 0 se ele ficou encalhado
	// voce deve ignorar ans[0]
	vector<int> solve() {
		vector<int> ans(n + 1, 0), cur(n + 1, 0), match(m + 1, 0);
		queue<int> q;

		for(int i = 1; i <= n; ++i) {
			q.push(i); // fila de rejeitados
		}

		while(q.size()) {
			int x = q.front(); q.pop();

			for(int & i = cur[x]; i < prior[x].size() and !ans[x]; i++) {
				int y = prior[x][i];
				if(!match[y] or rank[y][match[y]] > rank[y][x]) { // se a mulher nao ta noivada, ou se ela prefere eu
					q.push(match[y]); // coloca o noivo dela novamente na fila de rejeitados
					ans[match[y]] = 0;

					// faz um novo noivado
					match[y] = x;
					ans[x] = y;
				}
			}
		}

		return ans;
	}

};

void _solve() {
	int n; cin >> n;

	StableMarriage stab(n, n);
	for(int i = 1; i <= n; ++i) {
		vector<int> vec(n);
		for(int j = 0; j < n; ++j) {
			cin >> vec[j];
		}
		stab.setPreferencesMan(i, vec);
	}

	for(int i = 1; i <= n; ++i) {
		vector<int> vec(n);
		for(int j = 0; j < n; ++j) {
			cin >> vec[j];
		}
		stab.setPreferencesWoman(i, vec);
	}

	vector<int> ans = stab.solve();

	for(int i = 1; i < ans.size(); ++i) {
		cout << ans[i] << '\n';
	}
}

int main() {
	int t; cin >> t;
	while(t--) {
		_solve();
		if(t) cout << "\n";
	}
}