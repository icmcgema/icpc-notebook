/*
	Resolve o problema: dado um grafo funcional valorado, com O(N) estados e um tempo T, qual estado se termina após uma soma de pesos igual T for percorrida
	Geralmente nesses problemas, o T significa a duração da simulação, e os pesos das arestas representam o tempo da transição de um estado para outro.
	Versão simples: os pesos das arestas são 1.
*/

#include <bits/stdc++.h>

using namespace std;

struct State {

	State next() {

	}

	int hash() {

	}
};

struct Simulator {

	map<int, int> vis;

	State Simulate(int t, State cur) {
		int period = 0;

		while(t--) {
			if(vis.count(cur.hash())) {
				period -= vis[cur.hash()];
				break;
			}
			
			vis[cur.hash()] = period;
			cur = cur.next()
		}

		if(t) t %= period;
		while(t--) {
			cur = cur.next();
		}

		return cur;
	}
};
