#include <bits/stdc++.h>
using namespace std;

/** Wavelet Tree data structure. Input array is 0 based */
struct waveletTree {
	int lo, hi, mi; // minimum, maximum and (lo+hi)/2 element on array
	waveletTree *L, *R; // children
	vector<int> mp; // map how many elements went left

#define mapLeft(i) (mp[i]) /* original mapLeft */
#define mapRight(i) (i - mapLeft(i)) /* original mapRight */

	/** *beg points to the first element, *end points to after the last element (just like stl default functions).
	 * Elements are in range [lo..hi], inclusive */
	waveletTree(int *beg, int *end, int lo, int hi) { // O(nlogA)
		L = R = NULL;
		this->lo = lo;
		this->hi = hi;
		this->mi = (lo + hi) / 2;

		mp.reserve(end - beg + 1);
		mp.push_back(0);
		for (auto it = beg; it != end; it++) {
			mp.push_back(mp.back() + ((*it) <= mi));
		}

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
		if (lo >= x && hi <= y) return r - l + 1; // total fit

		if (mi >= y) return L->rangeCount(x, y, mapLeft(l-1)+1, mapLeft(r));
		else if (mi <= x) return R->rangeCount(x, y, mapRight(l-1)+1, mapRight(r));
		else return L->rangeCount(x, mi, mapLeft(l-1)+1, mapLeft(r)) +
			   R->rangeCount(mi+1, y, mapRight(l-1)+1, mapRight(r));
	}

	/** Swap elements a[i] and a[i+1] */
	void swapContiguous(int i) {
		if (lo == hi) return; // leaf node, no need to swap

		bool iLeft = mapLeft(i) == mapLeft(i-1) + 1; // if a[i] <= mi
		bool i1Left = (mapLeft(i+1)) == (mapLeft(i) + 1); // if a[i+1] <= mi

		if (iLeft && !i1Left) mapLeft(i)--;
		else if (!iLeft && i1Left) mapLeft(i)++;
		else if (iLeft && i1Left) L->swapContiguous(mapLeft(i));
		else R->swapContiguous(mapRight(i));
	}

	/** Push element k to end of array */
	void push_back(int k) {
		mp.push_back(mp.back() + (k <= mi));
		if (lo != hi) {
			if (k <= mi) L->push_back(k);
			else R->push_back(k);
		}
	}

	/** Pop element k from the end of array */
	void pop_back(int k) {
		mp.pop_back();
		if (lo != hi) {
			if (k <= mi) L->pop_back(k);
			else R->pop_back(k);
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

// https://www.spoj.com/problems/ILKQUERY/
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

	int N = all.size();
	vector<vector<int>> pos(N);
	for (int i = 1; i <= n; i++) pos[a[i]].push_back(i - 1);

	waveletTree T(a+1, a+n+1, 0, all.size());
	while(q--) {
		int k, i, l; scanf("%d%d%d", &k, &i, &l);
		int ans = T.kthSmallest(k, 1, i + 1);
		printf("%d\n", l <= (int) pos[ans].size() ? pos[ans][l - 1] : -1);
	}

	return 0;
}