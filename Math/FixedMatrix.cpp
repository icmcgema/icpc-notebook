#include <bits/stdc++.h>

using namespace std;

using ll = long long;

template<typename T, int n, int m, int mod = -1>
struct Matrix {
	array<T, n*m> mat = {};

	// matrix indexing is done via operator()
	// ie for a matrix m, m(1, 0), accesses the first element of the second row
	inline T const& operator()(int i, int j) const {
		return mat[i*m + j];
	}

	inline T& operator()(int i, int j) {
		return mat[i*m + j];
	}

	// constructors
	Matrix(vector<vector<T>> const& v) {
        for (int i = 0; i < n; i++) {
            copy(v[i].begin(), v[i].end(), mat.begin()+m*i);
        }
    }

	static Matrix identity() {
		Matrix r{};
		for(int i = 0; i < n; ++i) r(i, i) = 1;
		return r;
	}

	static Matrix zeros() {
		return Matrix{};
	}

	// operators
	Matrix& operator+=(Matrix const& rhs) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				(*this)(i, j) += rhs(i, j);
				if constexpr (mod != -1) {
					if ((*this)(i, j) >= mod) (*this)(i, j) -= mod;
				}
			}
		}
		return *this;
	}

	Matrix operator+(Matrix const& rhs) const {
		auto ans = *this;
		return ans += rhs;
	}

	Matrix& operator-=(Matrix const& rhs) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				(*this)(i, j) -= - rhs(i, j);
				if constexpr (mod != -1) {
					if ((*this)(i, j) < 0) (*this)(i, j) += mod;
				}
			}
		}
		return *this;
	}

	Matrix operator-(Matrix const& rhs) const {
		auto ans = *this;
		return ans -= rhs;
	}

	template<int p>
	Matrix<T, n, p, mod> operator*(Matrix<T, m, p, mod> const& rhs) const {
		Matrix<T, n, p, mod> res{};
		for (int i = 0; i < n; i++) {
			// for large matrices swap the next two lines for better cache locality
			for (int j = 0; j < p; j++) {
				for (int k = 0; k < m; k++) {
					if constexpr (mod != -1) res(i, j) = ((ll)res(i, j) + (ll)(*this)(i, k) * rhs(k, j)) % mod;
					else res(i, j) += (*this)(i, k) * rhs(k, j);
				}
			}
		}
		return res;
	}

	Matrix& operator*=(T x) {
		for (auto& i : mat) {
			if constexpr (mod != -1) i = 1ll * i * x % mod;
			else i *= x;
		}
		return *this;
	}

	Matrix operator*(T x) const {
		auto ans = *this;
		return ans *= x;
	}

	bool operator==(Matrix<T, n, m, mod> const& rhs) const {
		return equal(mat.begin(), mat.end(), rhs.mat.begin());
	}

	Matrix<T, m, n, mod> transposed() {
		auto ans = Matrix<T, m, n, mod>{};
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				ans(j, i) = (*this)(i, j);
			}
		}
		return ans;
	}

	friend ostream& operator<<(ostream& os, const Matrix& mat) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; ++j) {
				os << mat(i, j) << ' ';
			}
			os << '\n';
		}
		return os;
	}

};

// garantees matrix is square
template<typename T, int n, int mod = -1>
Matrix<T, n, n, mod> operator^(Matrix<T, n, n, mod> a, ll k) {
	auto ans = Matrix<T, n, n, mod>::identity();
	while(k) {
		if(k&1) ans = ans * a;
		a = a * a;
		k >>= 1;
	}
	return ans;
}