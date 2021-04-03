/** Convex hull excluding collinear points. O(n)
 * To include collinear points, change the <= operators of orientation to < */
template<typename T> vector<Point<T>> convex_hull(vector<Point<T>> v) {
	int n = v.size();
	if (n <= 2) return v;

	sort(v.begin(), v.end());

	vector<Point<T>> ch(2 * n);
	int sz = 0;

	for (int i = 0; i < n; i++) {
		while(sz > 1 && v[i].orientation(ch[sz - 2], ch[sz - 1]) < 0) sz--;
		ch[sz++] = v[i];
	}
	for (int i = n-2, up_sz = sz; i >= 0; i--) {
		while(sz > up_sz && v[i].orientation(ch[sz - 2], ch[sz - 1]) < 0) sz--;
		ch[sz++] = v[i];
	}

	ch.resize(sz - 1);
	return ch;
}
