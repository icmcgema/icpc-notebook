// 101549E (2012 ACM-ICPC Asia Hatyai Regional Programming Contest)
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define emp emplace
 
using namespace std;
using ll = long long;
using ii = pair<int, int>;
 
struct node {
	char c;
	node * l, *r;
	int rank, cnt;
 
	node(char c = 'f') {
		l = r = 0;
		rank = rand();
		this->c = c;
		cnt = 1;
	}
};
 
 
typedef node * treap;
 
treap copy(treap t) {
	treap x = new node(t->c);
	x->rank = t->rank;
	x->cnt = t->cnt;
	x->l = t->l;
	x->r = t->r;
	return x;
}
 
 
void upd(treap t) {
	if(t) t->cnt = 1 + (t->l? t->l->cnt : 0) + (t->r? t->r->cnt : 0);
}
 
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
 
 
int d = 0;
void print(treap t, int l, int r, int cur = 0) {
	if(!t) return;
 
	int pos = cur + (t->l? t->l->cnt : 0) + 1;
	if(pos + (t->r? t->r->cnt : 0) < l or cur > r) return;
	print(t->l, l, r, cur);
	if(pos >= l and pos <= r) {
		cout << t->c;
		d += t->c == 'c';
	}
	print(t->r, l, r, pos);
}
 
void debug(treap t) {
	if(!t) return;
	debug(t->l);
	cout << t->c;
	debug(t->r);
}
 
const int N = 2000007;
treap V[N];
 
int main() {
	srand(time(0));
	ios::sync_with_stdio(0); cin.tie(0);
 
	int q; cin >> q;
 
	treap t = 0;
 
	int v = 0;
	for(int i = 0; i < q; ++i) {
		int op; cin >> op;
 
		if(op == 1) {
			int p; string s;
			cin >> p >> s;
 
			p -= d;
			treap aux = 0;
 
			for(char c : s) {
				merge(aux, aux, new node(c));
			}
 
			treap L, R;
			split(t, t, R, p);
			merge(R, aux, R);
			merge(t, t, R);
 
 
		} else if(op == 2) {
			int p, c; cin >> p >> c;
			p -= d;
			c -= d;
			treap L, R;
			split(t, t, L, p-1);
			split(L, L, R, c);
			merge(t, t, R);
			
		} else {
			int ver, p, c;
			cin >> ver >> p >> c;
			p -= d;
			c -= d;
			ver -= d;
			print(V[ver], p, p + c - 1);
			cout << '\n';
		}
		if(op < 3) {
			v++;
			V[v] = t;
		}
	}
 
	return 0;
}