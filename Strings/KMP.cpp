/** Generate prefix function of KMP. O(N) */
template<typename T> std::vector<int> prefixKMP(T const& v) {
	int n = v.size();
	std::vector<int> pi(n);
	for (int i = 1; i < n; i++) {
		pi[i] = pi[i-1];
		while(pi[i] > 0 && v[pi[i]] != v[i])
			pi[i] = pi[pi[i]-1];
		if (v[i] == v[pi[i]]) pi[i]++;
	}
	return pi;
}
