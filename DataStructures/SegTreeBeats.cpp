#include <bits/stdc++.h>

/*
	Segment Tree Beats:

	Task 1:

	- For all l <= i <= r, change A_i to max(A_i, x)
	- Query for sum of [l, r]

	Task 2:

	- For all l <= i <= r, change A_i to max(A_i, x)
	- For all l <= i <= r, change A_i to min(A_i, x)
	- For all l <= i <= r, change A_i to A_i + x, x any integer
	- Query for sum of [l, r]

	Qualquer outro problema pode ser resolvido genericamente com o codigo, faltando so a analise da complexidade:

	void modify(int node, int l, int r, int ll, int rr) {
	  if (break_condition()) return;
	  if (tag_condition()) {
	      puttag(node); return;
	  }
	  pushdown(node);
	  int mid = (l + r) >> 1;
	  modify(node * 2, l, mid, ll, rr);
	  modify(node * 2 + 1, mid + 1, r, ll ,rr);
	  update();
	}
*/

using namespace std;
typedef long long ll;

// Task 1
struct SegtreeBeats {
	static constexpr int inf = 0x3f3f3f3f;

	#define mid ((l+r)>>1)
	int n;
	vector<ll> seg;
	vector<int> mai, cnt_mai, seg_mai, lazy;

	SegtreeBeats(int sz = 0): n(sz), seg(4*sz + 2), mai(4*sz + 2), cnt_mai(4*sz + 2), seg_mai(4 * sz + 2), lazy(4*sz + 2) {
		build(1, 0, sz-1);
	}

	SegtreeBeats(vector<int> vec) {
		*this = SegtreeBeats(vec.size());

		for(int i = 0; i < n; ++i) {
			update(1, 0, n-1, i, i, vec[i]);
		}
	}

	void merge(int p, int l, int r) {
		if(mai[l] == mai[r]) {
			mai[p] = mai[l];
			cnt_mai[p] = cnt_mai[l] + cnt_mai[r];
			seg_mai[p] = max(seg_mai[l], seg_mai[r]);
		} else {
			if(mai[l] < mai[r]) swap(l, r);
			mai[p] = mai[l];
			cnt_mai[p] = cnt_mai[l];
			seg_mai[p] = max(seg_mai[l], mai[r]);
		}

		seg[p] = seg[l] + seg[r];
	}

	void build(int p, int l, int r) {
		if(l == r) {
			mai[p] = seg[p] = inf;
			seg_mai[p] = -inf; // menor valor que posso ter
			cnt_mai[p] = 1;
		} else {
			build(2 * p, l, mid);
			build(2 * p + 1, mid+1, r);
			merge(p, 2 * p, 2 * p + 1);
		}
		lazy[p] = inf;
	}


	void prop(int p, int l, int r) {
		if(lazy[p] < mai[p]) {
			seg[p] -= ll(mai[p] - lazy[p]) * cnt_mai[p];
			mai[p] = lazy[p];
		}

		if(l != r) {
			lazy[2 * p] = min(lazy[2 * p], lazy[p]);
			lazy[2 * p + 1] = min(lazy[2 * p + 1], lazy[p]);
		}

		lazy[p] = inf;
	}

	// para todo i em [a, b], atualiza seg_i = min(seg_i, x)
	void update(int p, int l, int r, int a, int b, int x) {
		prop(p, l, r);
		if(r < a or l > b or mai[p] <= x) return;
		if(l >= a and r <= b and seg_mai[p] < x) {
			lazy[p] = min(lazy[p], x);
			prop(p, l, r);
		} else {
			update(2 * p, l, mid, a, b, x);
			update(2 * p + 1, mid+1, r, a, b, x);
			merge(p, 2 * p, 2 * p + 1);
		}
	}

	// retorna a soma de [a, b]
	ll query(int p, int l, int r, int a, int b) {
		prop(p, l, r);
		if(r < a or l > b) return 0;
		if(l >= a and r <= b) return seg[p];
		return query(2 * p, l, mid, a, b) + query(2 * p + 1, mid+1, r, a, b);
	}

	#undef mid
};

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, q; cin >> n;

	SegtreeBeats seg(n);

	int op, l, r, x; 
	while(cin >> op >> l >> r) {
		if(op == 1) {
			cout << seg.query(1, 0, n-1, l-1, r-1) << '\n';
		} else {
			cin >> x;
			seg.update(1, 0, n-1, l-1, r-1, x);
		}
	}
}