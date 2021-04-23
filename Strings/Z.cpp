/** Generate Z function. O(N) */
template<typename T> std::vector<int> buildZ(T const& v) {
	int n = v.size();
	std::vector<int> z(n);
	for (int i = 1, l = 0, r = 0; i < n; i++) {
		if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);
		while(i + z[i] < n && v[z[i]+i] == v[z[i]]) z[i]++;
		if (z[i] + i - 1 > r) l = i, r = i + z[i] - 1;
	}
	return z;
}
