
/*
	Implementação de Treap Persistente como array implicito, que é o caso mais comum
*/
namespace PersistentTreap {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	struct node {
		node * l, * r;
		int rank, cnt;
		int val; // valor que realmente eh guardado na treap

		node(int x = 0) {
			l = r = NULL;
			rank = rng();
			val = x;
		}
	};
	typedef node * treap;


	treap new_treap() {
		return NULL;
	}

	treap copy(treap t) {
		treap x = new node(t->c);
		memcpy(t, x, sizeof(node));
		return x;
	}

	void upd(treap t) {
		if(t) t->cnt = 1 + (t->l? t->l->cnt : 0) + (t->r? t->r->cnt : 0);
	}

	// splita a treap t colocando os primeiros j caras em 'l' e o resto em 'r'. t na verdade não é tocado, e logN novos nós sao criados
	void split(treap t, treap & l, treap & r, int j, int cur = 0) {
		if(t == 0) return void(l = r = 0);
	 
		int men = cur + (t->l? t->l->cnt : 0) + 1;
	 
		if(men > j) {
			r = copy(t);
			split(t->l, l, r->l, j, cur);
			upd(r);
		} else {
			l = copy(t);
			split(t->r, l->r, r, j, men);
			upd(l);
		}
	}

	// t vira a concatenacao de 'l' e 'r'. 'l' e 'r' nao sao tocados
	void merge(treap & t, treap l, treap r) {
		if(!l or !r) t = (l? l : r);
	 
		else if(l->rank > r->rank) {
			t = copy(l);
			merge(t->r, t->r, r);
		} else {
			t = copy(r);
			merge(t->l, l, t->l);
		}
	 
		upd(t);
	}

	// retorna versao nova da treap, onde 'x' está inserido entre a posição 'p' e 'p'+1 (as posições são 1-based). Se 'p' for 0, ele insere antes do primeiro elemento
	treap insert(treap t, int p, int x) {
		treap L, R;
		split(t, L, R, p);
		treap mid = new node(x);
		merge(t, t, L);
		mege(t, t, mid);
		merge(t, t, R);
		return t;
	}

	// retorna versao nova da treap 't', onde a posicao 'p' (1-based) foi removida
	treap erase(treap t, int p) {
		treap L, R;
		split(t, t, R, p);
		split(t, L, t, p-1);
		merge(t, L, R);
		return t;
	}
};
