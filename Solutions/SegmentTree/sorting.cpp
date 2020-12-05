// Calcula o número de comparações de um quick sort
// https://www.codechef.com/problems/SORTING
/*
	Supondo que não há randomização do quicksort, e que um indice fixo (nesse problema, o indice do meio), vai ser usado como pivot para fazer as comparações. Repare que como não é randomizado, um numero quadratico de comparações pode ser feito
	Observações:
		- Na recursão do quicksort sempre dividimos o alfabeto atual entre o conjunto menor que o pivot e o conjunto maior.
		- Para uma chamada atual da recursão, o número de comparações sempre é o tamanho do vetor
		- Não importa qual é o indice (do array original) escolhido, e sim como o alfabeto é particionado

	A ideia é manter o range [L, R] atual do alfabeto (assim como na wavelet) 
	Com isso, pra somar o tamanho desse vetor , é só saber quantos caras existem com esse range do alfabeto. Pra achar o k-ésimo, da pra fazer com wavelet 
	(onde queremos saber o n/2-ésimo de um array onde os valores do array original são os indices e o indice do array original sao os valores). Aqui eu fiz com seg persistente

*/
#include <bits/stdc++.h>

#define eb emplace_back
#define mid ((l+r)>>1)

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

struct node {
	int val;
	node * l, * r;

	node() {
		val = 0;
		l = r = 0;
	}
};


node * update(node * cur, int l, int r, int j, int x) {
	if(r < j or l > j) return cur;
	node * u = cur? new node(*cur) : new node();
	if(l == r) {
		u->val = x;
	} else {
		u->l = update(u->l, l, mid, j, x);
		u->r = update(u->r, mid+1, r, j, x);
		u->val = (u->l? u->l->val : 0) + (u->r? u->r->val : 0);
	}
	return u;
}

inline int getl(node * u) {
	if(u == NULL or u->l == NULL) return 0;
	return u->l->val;
}
inline int getr(node * u) {
	if(u == NULL or u->r == NULL) return 0;
	return u->r->val;
}

int kth(node * u, node * v, int l, int r, int k) {

	if(l == r) return l;

	// quantos tem na esquerda
	int left = getl(v) - getl(u);
	if(left >= k) return kth(u?u->l:0, v?v->l:0, l, mid, k);
	else return kth(u?u->r:0, v?v->r:0, mid+1, r, k-left); 
}


const int N = 5e5 + 7;
node * ver[N];
int label[N];
int n;
// lo = indice do menor valor no vetor ordenado
// hi = indice do maior valor no vetor ordenado
ll go(int lo, int hi) {
	if(lo >= hi) return 0;
	int tot = (ver[hi]? ver[hi]->val:0) - (ver[lo-1]?ver[lo-1]->val : 0);
	int middle = kth(ver[lo-1], ver[hi], 1, n, (tot+1)/2); // meio do indice
	middle = label[middle]; 
	return go(lo, middle-1) + go(middle+1, hi) + tot;
}

int main() {
	 cin >> n;

	vector<ii> vec;
	for(int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		vec.eb(x, i);
	}

	sort(vec.begin(), vec.end());

	ver[0] = NULL; 

	for(int i = 1; i <= n; ++i) {
		int x, j; tie(x, j) = vec[i-1];
		ver[i] = update(ver[i-1], 1, n, j, 1);
		label[j] = i;
	}


	cout << go(1, n) << endl;




}