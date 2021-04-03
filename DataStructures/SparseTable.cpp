template<typename T>
struct SparseTable {
	int n;
	std::vector<std::vector<T>> mat;

	// Function to apply range query
	inline static T f(T x, T y) {
		return min(x, y);
	}

	// initialize everything
	SparseTable(std::vector<T> const& a) {
		n = a.size();
		const int max_log = 32 - __builtin_clz(n);
		mat.resize(max_log);
		mat[0] = a;
		for (int j = 1; j < max_log; j++) {
			mat[j].resize(n - (1 << j) + 1);
			for (int i = 0; i <= n - (1 << j); i++) {
				mat[j][i] = f(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
			}
		}
	}

	// Query [from, to]. O(1)
	inline T query(int from, int to) const {
		assert(0 <= from && from <= to && to <= n - 1);
		int lg = 32 - __builtin_clz(to - from + 1) - 1;
		return f(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
	}
};
