/*
	Resolve o problema: dado um grafo funcional valorado, com O(N) estados e um tempo T, qual estado se termina após uma soma de pesos igual T for percorrida
	Geralmente nesses problemas, o T significa a duração da simulação, e os pesos das arestas representam o tempo da transição de um estado para outro.

	// Acho que com pesos 0 funciona
*/

#include <bits/stdc++.h>

using namespace std;

struct State {

	// representacao unica do estado
	int hash() {

	}

	// vai pro proximo estado, e retorna o tempo atravessado
	int next() {

	}

	// Faz o passo final (quando sobre um tantinho de tempo mas ainda nao da pra ir no proximo estado)
	State finish(int tim) {

	}
};

struct Simulator {

	map<int, int> vis;

	// recebe o tempo total e o estado inicial
	State Simulate(int t, State cur) {
		int period = 0;

		while(t > 0) {

			if(vis.count(cur.hash()) ) {
				period -= vis[cur.hash()];
				break;
			}

			vis[cur.hash()] = period;
			State aux = cur;
			int tim = cur.next();

			if(t - tim < 0) {
				period = 0;
				cur = aux;
				break;
			}
			period += tim;
			t -= tim;
		}

		if(period) t %= period;

		while(t > 0) {
			State aux = cur;
			int tim = cur.next();
			if(t - tim < 0) {
				cur = aux;
				break;
			}
			t -= tim;
		}

		cur = cur.finish(t);

		return cur;
	}
};