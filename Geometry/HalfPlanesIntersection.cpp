#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-9;
struct pt {
	double x, y;
	pt(){}
	pt(double _x, double _y): x(_x), y(_y){}

	pt operator-(pt q) const {
		return pt(x - q.x, y - q.y);
	}
	pt operator+(pt q) const {
		return pt(x + q.x, y + q.y);
	}
	double operator^(pt q) const {
		return x * q.y - q.x * y; 
	}
};

struct line {
	double a, b, c;

	line(){}
	line(double _a, double _b, double _c): a(_a), b(_b), c(_c) {}
	line(pt p, pt q) {
		pt aux = q - p;
		a = -aux.y;
		b = aux.x;
		c = -a * p.x - b * p.y;
	}

	bool contains(pt p) {
		return a * p.x + b * p.y + c >= 0;
	}

	pt norm() {
		return pt(a, b);
	}

	pt any() {
		if(abs(b) < eps) return pt(-c/a, 0);
		return {0, -c/b};
	}

	static pt intersection(line l1, line l2, int & err) {
		const double eps = 1e-9;
		double a1, b1, c1;
		a1 = l1.a, b1 = l1.b, c1 = -l1.c;
		double a2, b2, c2;
		a2 = l2.a, b2 = l2.b, c2 = -l2.c;

		err= 0;

		double den = l1.norm()^l2.norm();

		if(abs(den) < eps) {
			if(abs(c1 - c2) < eps) err = 1; // são a mesma reta
			err = 2; // nao há intersecção
			return pt(0, 0);
		}

		double x = (c1 * b2 - c2 * b1)/den;
		double y = (a1 * c2 - a2 * c1)/den;
		return pt(x, y);
	}
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/* Retorna se esse vector<line> vec, que contem halfplanes, é vazio ou não */
bool intersection_not_empty(vector<line> vec) {
	// vec.emplace_back(1, 0, 1e9); // parede esquerda
	// vec.emplace_back(-1, 0, 1e9); // parede direita
	// vec.emplace_back(0, 1, 1e9); // parede inferior
	// vec.emplace_back(0, -1, 1e9); // parede superior

	pt cur = {0, 0}; // qualquer ponto dentro da interseccao dos semi planos
	shuffle(vec.begin(), vec.end(), rng);

	for(int i = 0; i < vec.size(); ++i) {
		line & l = vec[i];
		if(l.contains(cur)) continue;
		// acha o novo p, vai ser alguma interseccao de l com todos os outros ate agora

		pt hi, lo;
		int flaghi = 0, flaglo = 0;
		for(int j = 0; j < i; ++j) {
			int err;
			pt p = line::intersection(l, vec[j], err);
			if(err == 1) continue; // sao a mesma linha, nao acontece nada
			if(err == 2) {
				// significa que os semi planos paralelos são contrários
				if(!vec[j].contains(l.any()) and !l.contains(vec[j].any())) return false; 
			} else {
				// dois casos
				if((l.norm()^vec[j].norm()) > 0) {
					// pra tras
					if(!flaghi or ((hi - p)^l.norm()) > 0) {
						hi = p;
						flaghi = 1;
					}
				} else {
					// pra frente
					if(!flaglo or ((p - lo)^l.norm()) > 0) {
						lo = p;
						flaglo = 1;
					}
				}
			}
		}

		if(flaghi + flaglo < 2) cur = flaghi? hi : flaglo? lo : l.any();
		else if(((hi - lo)^l.norm()) >= 0) cur = hi; // hi ou lo, tanto faz
		else return false; // intersecao vazia
	}

	return true;
}
