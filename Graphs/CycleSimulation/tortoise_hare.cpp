/*
	Resolve o problema: dado um grafo funcional valorado, com O(N) estados e um tempo T, qual estado se termina após uma soma de pesos igual T for percorrida
	Geralmente nesses problemas, o T significa a duração da simulação, e os pesos das arestas representam o tempo da transição de um estado para outro.
	Versão fera que inclui encontrar o periodo do ciclo com o algoritmo da lebre e tartaruga, removendo um log do map de visitado

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

	// Retorna periodo do ciclo. Possivelmente muda o estado e decrementa o tempo. Retorna 0 se o ciclo nao for encontrado antes do tempo esgotar
	int find_period(State & cur, int & t) {
		vis.clear();

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
				cur = aux;
				return 0;
			}
			period += tim;
			t -= tim;
		}
		return period;
	}

	// retorna periodo do ciclo
	int find_period_tortoise_hare(const State cur) {
		State tor = cur, hare = cur;

		// Acha o ponto de inicio do ciclo
		do {
			tor.next();
			hare.next(); hare.next();
		} while(tor.hash() != hare.hash());

		// Calcula o periodo do ciclo
		int tim = 0;
		do {
			tim += tor.next();
		} while(tor.hash() != hare.hash());

		return tim;
	}

	// Roda a simulacao
	State Simulate(int t, State cur, bool use_tortoise_hare = false) {
		int period = use_tortoise_hare? find_period_tortoise_hare(cur) : find_period(cur, t);

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