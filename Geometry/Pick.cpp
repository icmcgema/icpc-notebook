/** Count integer (lattice) points inside and on boundary of polygon (can be concave)
 * BE CAREFUL: T must be INTEGER!!! */
template<typename T> pair<T, T> count_lattice_points(vector<Point<T>> const& v) {
	/** Pick's theorem: A = i + b/2 - 1 (area = inner_lattice + boundary_lattice/2 - 1) */
	pair<T, T> ans = {0, 0}; // <inside, boundary>
	T area2 = 0;
	int n = v.size();
	for (int i = 0, j = n-1; i < n; j = i, i++) {
		Point<T> dif = v[i] - v[j];
		dif.x = abs(dif.x), dif.y = abs(dif.y);
		ans.se += gcd(dif.x, dif.y);
		area2 += v[i].cross(v[j]);
	}
	area2 = abs(area2);
	ans.fi = (area2 - ans.se + 2) / 2;
	return ans;
}