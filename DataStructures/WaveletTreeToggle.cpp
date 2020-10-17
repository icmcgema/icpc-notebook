#include <bits/stdc++.h>
using namespace std;

/** Wavelet Tree data structure. Input array is 0 based */
struct waveletTree {
	int lo, hi, mi; // minimum, maximum and (lo+hi)/2 element on array
	waveletTree *L, *R; // children

	vector<int> mp; // map how many elements went left
	struct Bit { // count how many indices are active
		vector<int> bt;
		Bit() {}

		inline void init(int n) {
			bt.assign(n, 0);
			for (int i = 1; i < n; i++) update(i, 1);
		}

		inline void update(int i, int x) {
			for (; i < (int) bt.size(); i += i&-i)
				bt[i] += x;
		}

		inline int query(int i) {
			int r = 0;
			for (; i > 0; i -= i&-i)
				r += bt[i];
			return r;
		}
		inline int query(int i, int j) {
			return query(j) - query(i - 1);
		}
	} bt;

#define mapLeft(i) (mp[i]) /* original mapLeft */
#define mapRight(i) (i - mapLeft(i)) /* original mapRight */

	/** *beg points to the first element, *end points to after the last element (just like stl default functions).
	 * Elements are in range [lo..hi], inclusive */
	waveletTree(int *beg, int *end, int lo, int hi) { // O(nlogA)
		L = R = NULL;
		this->lo = lo;
		this->hi = hi;
		this->mi = (lo + hi) / 2;

		bt.init(end - beg + 1);

		mp.reserve(end - beg + 1);
		mp.push_back(0);
		for (auto it = beg; it != end; it++)
			mp.push_back(mp.back() + ((*it) <= mi));

		if (lo != hi) {
			auto pivot = stable_partition(beg, end, [&](int x) {
				return x <= mi;
			}); // split the vector
			L = new waveletTree(beg, pivot, lo, mi);
			R = new waveletTree(pivot, end, mi + 1, hi);
		}
	}

	/** K-th smallest element on range[l..r] */
	int kthSmallest(int k, int l, int r) {
		if (l > r) return -1; // out of bounds
		if (lo == hi) return lo; // leaf node

		int inLeft = mapLeft(r) - mapLeft(l-1);
		if (k <= inLeft) return L->kthSmallest(k, mapLeft(l-1)+1, mapLeft(r));
		else return R->kthSmallest(k-inLeft, mapRight(l-1)+1, mapRight(r));
	}

	/** Frequency of elements between [x..y] in array[l..r] */
	int rangeCount(int x, int y, int l, int r) {
		if (l > r || lo > y || hi < x) return 0; // out of bounds
		if (lo >= x && hi <= y) return bt.query(l, r);
		if (mi >= y) return L->rangeCount(x, y, mapLeft(l-1)+1, mapLeft(r));
		else if (mi <= x) return R->rangeCount(x, y, mapRight(l-1)+1, mapRight(r));
		else return L->rangeCount(x, mi, mapLeft(l-1)+1, mapLeft(r)) +
					R->rangeCount(mi+1, y, mapRight(l-1)+1, mapRight(r));
	}

	/** Toggle i-th active state (switch ON/OFF) */
	void toggle(int i) {
		if (bt.query(i, i)) bt.update(i, -1);
		else bt.update(i, 1);
		if (lo != hi) {
			if (mapLeft(i) == mapLeft(i-1) + 1) L->toggle(mapLeft(i));
			else R->toggle(mapRight(i));
		}
	}

	~waveletTree() {
		if (L) delete L;
		if (R) delete R;
	}

#undef mapLeft
#undef mapRight
};

const int MAXN = 1e5 + 5;
int a[MAXN];

// https://www.spoj.com/problems/ILKQUERY2/
int main() {
	int n, q; scanf("%d%d", &n, &q);

	vector<int> all;
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		all.push_back(a[i]);
	}
	sort(all.begin(), all.end());
	all.erase(unique(all.begin(), all.end()), all.end());
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(all.begin(), all.end(), a[i]) - all.begin();

	waveletTree T(a+1, a+n+1, 0, all.size());
	while(q--) {
		int op; scanf("%d", &op);
		if (op == 0) {
			int i, l, k; scanf("%d%d%d", &i, &l, &k);
			if (binary_search(all.begin(), all.end(), k)) {
				k = lower_bound(all.begin(), all.end(), k) - all.begin();
				printf("%d\n", T.rangeCount(k, k, i + 1, l + 1));
			}
			else puts("0");
		} else {
			int i; scanf("%d", &i);
			T.toggle(i + 1);
		}
	}

	return 0;
}