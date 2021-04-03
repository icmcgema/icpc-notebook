#include <bits/stdc++.h>

using namespace std;

/*
	PointsUnderLine::calc(p, q, n) calcula:
		Soma { floor(p * i / q) } para i=1..n

	Complexidade: log(min(p, q))
	Ideia: Pensando no resultado de calc(p, q, n) como a area hachurada de um retangulo de largura n e altura p * n, 
	escreva calc(p, q, n) como função de g(p, q, n), em que g(p, q, n) calcula a área hachurada se este retangulo
	for rotacionado em 90° no sentido anti-horario
*/

namespace PointsUnderLine {
	ll g(ll p, ll q, ll n) {
	    return p == 0? 0 : (n * gcd(p, q))/q;
	}

	ll calc(ll p, ll q, ll n) {
	    if(p == 0 or q == 0 or n == 0) return 0;
	    return (p/q) * ((n *(n+1))/2) + (((p%q)*n)/q)*n - calc(q, p%q, ((p%q)*n)/q) + g(p%q, q, n);
	}
};