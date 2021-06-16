/** return the minimum distance**2 between 2 points in the plane. O(N logn) */
template<typename T> T closest_pair_distance2(vector<Point<T>> p) {
	sort(p.begin(), p.end());

	vector<Point<T>> strip(p.size());
	auto find_closest = [&](auto&& find_closest, vector<Point<T>>& p, int l, int r)->T {
		if (r - l <= 0) return numeric_limits<T>::max();

		int m = (l + r) / 2;
		T distL = find_closest(find_closest, p, l, m);
		T distR = find_closest(find_closest, p, m + 1, r);
		T dist = min(distL, distR);

		int strip_index = 0;
		for (int i = l, j = m + 1; i <= m || j <= r; ) {
			if (j > r || (i <= m && p[i].y < p[j].y)) strip[strip_index++] = p[i++];
			else strip[strip_index++] = p[j++];
		}
		for (int i = l; i <= r; i++) p[i] = strip[i - l];

		strip_index = 0;
		for (int i = l; i <= r; i++) if ((p[i].x - p[m].x) * (p[i].x - p[m].x) < dist)
			strip[strip_index++] = p[i];

		for (int i = 0; i < strip_index; i++) {
			for (int j = i + 1; j < strip_index && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < dist; j++) {
				dist = min(dist, strip[i].dist2(strip[j]));
			}
		}

		return dist;
	};

	return find_closest(find_closest, p, 0, (int) p.size() - 1);
}
