#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

/**
 * If T is floating point, remove all of the occurences of the exact string "% mod" and you are safe
 * If T is int and you require negative values, do the same as above. 
 * Otherwise, don't forget to set a mod, cause probably the problem asks you to.
 */
template<typename T, int mod = 1234567890>
struct Matrix {
	vector<vector<T>> mat;
	int n, m;

	Matrix(int n_, int m_): n(n_), m(m_), mat(n_, vector<T>(m_)) {}
	Matrix(vector<vector<T>> v): n(v.size()), m(v[0].size()), mat(v) {}
	Matrix(initializer_list<vector<T>> l): mat(l), n(l.size()), m(l.begin()->size()) {}

	vector<T>& operator[](int i) const {
		return const_cast<vector<T>&>(mat[i]);
	}

	// Sum two matrices
	Matrix operator+(const Matrix& b) const {
		if(n != b.n or m != b.m) throw runtime_error("Matrixes have different dimensions");

		Matrix ans(n, m);
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				ans[i][j] = (mat[i][j] + b[i][j]) % mod; 
			}
		}
		return ans;
	}

	// Sum two matrices
	Matrix operator-(const Matrix& b) const {
		if(n != b.n or m != b.m) throw runtime_error("Matrixes have different dimensions");

		Matrix ans(n, m);
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				ans[i][j] = mat[i][j] - b[i][j]; 
				if(mod != 1234567890 and ans[i][j] < 0) ans[i][j] = ans[i][j] + mod; 
			}
		}
		return ans;
	}

	// Multiply two matrices
	Matrix operator*(const Matrix& b) const {
		if(m != b.n) throw runtime_error("Can't multiply: matrixes' dimensions are not compatible");

		Matrix ans(n, b.m);
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < b.m; ++j) {
				for(int k = 0; k < m; ++k) {
					ans[i][j] = (ans[i][j] + 1ll * mat[i][k] * b[k][j] % mod) % mod;
				}
			}
		}
		return ans;
	}

	// multiply by column vector
	vector<T> operator*(const vector<T>& col) const {
		if(m != col.size()) throw runtime_error("Can't multiply: matrixes' dimensions are not compatible");
		vector<T> ans(m);
		for(int i = 0; i < n; ++i) {
			ans[i] = T(0);
			for(int j = 0; j < m; ++j) {
				ans[i] = (ans[i] + 1ll * mat[i][j] * col[j] % mod) % mod;
			}
		}
		return ans;
	}

	// multiply by scalar
	Matrix operator*(const T& x) const {
		Matrix ans(n, m);
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				ans[i][j] = 1ll * mat[i][j] * x % mod;
			}
		}
		return ans;
	}

	// return k-th power
	Matrix operator^(ll k) {
		if(n != m) throw runtime_error("Cant exponentiate a non-square matrix");

		Matrix ans = identity(n);
		Matrix aux(mat);
		while(k) {
			if(k&1) ans = ans * aux;
			aux = aux * aux;
			k >>= 1;
		}
		return ans;
	}

	bool operator== (const Matrix& a) const {
		if(n != a.n or m != a.m) return false;
		bool ans = true;
		for(int i = 0; i < n && ans; ++i) ans &= mat[i] == a[i];
		return ans;
	}

	// Get transposed
	Matrix transposed() {
		Matrix ans(m, n);
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				ans[j][i] = mat[i][j];
			}
		}
		return ans;
	}

	/** For double, if you're using Z/mod you have to customize
	  * Returns the rank of the matrix (the number of column vectors that are linearly independent)
	  * O(N*M*M), I think
	  */
	int rank() {
		const double EPS = 1e-9;
		int rank = 0;
		vector<bool> row_selected(n, false);

		Matrix A = *this;

		for (int i = 0; i < m; ++i) {
			int j;
			for (j = 0; j < n; ++j) {
				if (!row_selected[j] && abs(A[j][i]) > EPS)
					break;
			}

			if (j != n) {
				++rank;
				row_selected[j] = true;
				for (int p = i + 1; p < m; ++p)
					A[j][p] = A[j][p] / A[j][i];
				for (int k = 0; k < n; ++k) {
					if (k != j && abs(A[k][i]) > EPS) {
						for (int p = i + 1; p < m; ++p)
							A[k][p] = A[k][p] - A[j][p] * A[k][i];
					}
				}
			}
		}
		return rank;
	}

	friend ostream& operator<<(ostream& os, const Matrix& mat) {
		for(int i = 0; i < mat.n; i++) {
			for(int j = 0; j < mat.m; ++j) {
				cout << mat[i][j] << ' ';
			}
			cout << '\n';
		}
		return os;
	}

	/* -------------------- Static functions ------------------- */
	static Matrix identity(int n) {
		Matrix m(n, n);
		for(int i = 0; i < n; ++i) m[i][i] = 1;
		return m;
	}

	static Matrix zeros(int n, int m) {
		return Matrix(n, m);
	}

	/** Freivalds computes if a * b = c, with probability at least (1 - (1/2)^k) of certainty
	  * a and b must be square matrices of same dimension
	  * Complexity: O(k * n^2, where k = number of steps
	  */
	static bool freivald(const Matrix& a, const Matrix& b, const Matrix& c, int k = 50) {
		if(a.n != a.m or b.n != b.m or c.n != c.m) throw runtime_error("All matrices must be square matrices");
		if(a.n != b.n or b.n != c.n) throw runtime_error("All matrices must have the same dimension");

		int n = a.n;
		bool ans = true;
		while(k-- && ans) {
			vector<T> aux(n);
			for(int i = 0; i < n; ++i) {
				aux[i] = T(rand()%2);
			}

			vector<T> ret1 = a * (b * aux);
			vector<T> ret2 = c * aux;
			ans &= ret1 == ret2;
		}
		return ans;
	}
};