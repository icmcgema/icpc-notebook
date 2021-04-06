struct Seg {
	struct Node {
		ll v = 0; // initialize empty values; HERE
		ll lazy = 0;

		inline void apply(int i, int j, ll x) {
			lazy += x; // HERE
		}
	};

	int n;
	vector<Node> seg;
	Seg(int n) : n(n), seg(4 * n) {}

	Node merge(Node const& L, Node const& R) { // HERE (merge children)
		Node ret;
		ret.v = min(L.v, R.v);
		return ret;
	}

	void prop(int p, int i, int j) { // HERE (lazy propagation)
		if (seg[p].lazy) {
			seg[p].v += seg[p].lazy;
			if (i != j) {
				seg[p + p].lazy += seg[p].lazy;
				seg[p + p + 1].lazy += seg[p].lazy;
			}
			seg[p].lazy = 0;
		}
	}

	template<typename T>
	void build(int p, int i, int j, vector<T> const& v) {
		if (i == j) {
			seg[p].apply(i, j, v[i]);
			prop(p, i, j);
		} else {
			int m = (i + j) / 2;
			build(p + p, i, m, v);
			build(p + p + 1, m + 1, j, v);
			seg[p] = merge(seg[p + p], seg[p + p + 1]);
		}
	}

	template<typename T>
	inline void build(vector<T> const& v) {
		build(1, 0, n - 1, v);
	}

	Node query(int p, int i, int j, int l, int r) {
		prop(p, i, j);
		assert(i <= r && j >= l);
		if (i >= l && j <= r) return seg[p];
		int m = (i + j) / 2;
		if (m >= r) {
			prop(p + p + 1, m + 1, j);
			return query(p + p, i, m, l, r);
		} else if (m < l) {
			prop(p + p, i, m);
			return query(p + p + 1, m + 1, j, l, r);
		}
		Node L = query(p + p, i, m, l, r);
		Node R = query(p + p + 1, m + 1, j, l, r);
		return merge(L, R);
	}

	inline Node query(int l, int r) {
		return query(1, 0, n-1, l, r);
	}

	template<typename... T>
	void update(int p, int i, int j, int l, int r, T... x) {
		prop(p, i, j);
		if (i > r || j < l) return;
		if (i >= l && j <= r) {
			seg[p].apply(i, j, x...);
			prop(p, i, j);
			return;
		}
		int m = (i + j) / 2;
		update(p + p, i, m, l, r, x...);
		update(p + p + 1, m + 1, j, l, r, x...);
		seg[p] = merge(seg[p + p], seg[p + p + 1]);
	}

	template<typename... T>
	inline void update(int l, int r, T... x) {
		update(1, 0, n-1, l, r, x...);
	}
};