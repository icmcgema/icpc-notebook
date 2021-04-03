namespace Karatsuba {
	/** Karatsuba method. O(n ^ (log2_3)) ~ O(n^1.58) */
	template<typename T>
	inline void karatsuba(vector<T> const& a, vector<T> const& b, vector<T>& ans, int n) {
		if (n <= 64) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					ans[i + j] += a[i] * b[j];
			return;
		}

		int mid = n / 2;
		vector<T> _a(mid), _b(mid);
		vector<T> E(n);

		karatsuba(a, b, ans, mid);
		for (int i = 0; i < mid; i++) {
			_a[i] = a[i + mid];
			_b[i] = b[i + mid];
		}
		karatsuba(_a, _b, E, mid);

		for (int i = 0; i < n; i++) ans[i + n] = E[i];

		for (int i = 0; i < mid; i++) {
			_a[i] = a[i] + a[i + mid];
			_b[i] = b[i] + b[i + mid];
		}
		fill(E.begin(), E.end(), 0);
		karatsuba(_a, _b, E, mid);

		for (int i = 0; i < mid; i++) {
			const T tmp = ans[i + mid];
			ans[i + mid] += E[i] - ans[i] - ans[i + n];
			ans[i + mid + mid] += E[i + mid] - tmp - ans[i + n + mid];
		}
	}

	/** Multiplies two polynomials a * b = ans. O(n ^ (log2_3)) ~ O(n^1.58) */
	template<typename T>
	inline void mult(vector<T> const& a, vector<T> const& b, vector<T>& ans) {
		int n = 1;
		while(n < (int) max(a.size(), b.size())) n *= 2;
		vector<T> _a(a.begin(), a.end());
		vector<T> _b(b.begin(), b.end());
		_a.resize(n);
		_b.resize(n);
		ans.assign(n + n, 0);
		karatsuba(_a, _b, ans, n);
	}

	/** Multiplies two BigIntegers using base 10^p.
	*  T must be int128 for p=9. I guess that long long works for p < 9. */
	template<typename T, int p> inline void mult_bigint(string s1, string s2, string& ans) {
		T base = 1;
		for (int i = 0; i < p; i++) base *= 10;

		reverse(s1.begin(), s1.end());
		reverse(s2.begin(), s2.end());

		vector<T> a, b, c;
		for (int i = 0; i < (int) s1.size(); i += p) {
			T cur = 0;
			for (int j = i + p - 1; j >= i; j--)
				cur = cur * 10 + (j < (int) s1.size() ? s1[j] - '0' : 0);
			a.push_back(cur);
		}
		for (int i = 0; i < (int) s2.size(); i += p) {
			T cur = 0;
			for (int j = i + p - 1; j >= i; j--)
				cur = cur * 10 + (j < (int) s2.size() ? s2[j] - '0' : 0);
			b.push_back(cur);
		}

		mult(a, b, c);

		c.push_back(0);

		T carry = 0;
		for (int i = 0; i < (int) c.size(); i++) {
			carry += c[i];
			c[i] = carry % base;
			carry /= base;
		}
		while(!c.empty() && c.back() == 0) c.pop_back();
		reverse(c.begin(), c.end());

		ans = "";
		for (int i = 0; i < (int) c.size(); i++) {
			string cur;
			while(c[i] > 0) cur += (c[i] % 10) + '0', c[i] /= 10;
			reverse(cur.begin(), cur.end());

			if (i != 0) cur = string(p - (int) cur.size(), '0') + cur;
			ans += cur;
		}
		if (ans.empty()) ans = "0";
	}
}