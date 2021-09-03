#include <bits/stdc++.h>

// Example for segtree of sum:
// int sum(int a, int b) { return a + b; }
// segtree<int, 0, sum> seg;
template<typename T, T zero, T (*op)(T, T) >
struct segtree {
	vector<T> seg;
	int n;
	segtree(int n_): n(n_) {
		seg.assign(n_ + n_ + 5, zero);
	}

	T query(int l, int r) {
		T ansl = zero;
		T ansr = zero;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if(l&1) ansl = op(ansl, seg[l++]);
			if(r&1) ansr = op(ansr, seg[--r]);
		}
		return op(ansl, ansr);
	}

	void update(int p, T val) {
		for(seg[p += n] = val; p >> 1; p >>= 1) {
			seg[p >> 1] = op(seg[p], seg[p^1]);
		}
	}
};