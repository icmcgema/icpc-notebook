#include <bits/stdc++.h>

using namespace std;

using ll = long long;

template<typename T, int n, int m, int mod = -1>
struct Matrix {
	static constexpr bool has_mod = (mod == -1);

	array<T, n*m> mat = {};

	// matrix indexing is done via operator()
	// ie for a matrix m, m(1, 0), accesses the first element of the second row
	constexpr inline T const& operator()(int i, int j) const {
		return mat[i*m + j];
	}

	constexpr inline T& operator()(int i, int j) {
		return mat[i*m + j];
	}

	// static constructors
	static Matrix from_vecs(vector<vector<T>> const& v) {
		Matrix r;
        for (int i = 0; i < n; i++) {
            copy(v[i].begin(), v[i].end(), r.mat.begin() + i*m);
        }
		return r;
    }

	constexpr static Matrix identity() {
		Matrix r{};
		for(int i = 0; i < n; ++i) r(i, i) = 1;
		return r;
	}

	constexpr static Matrix zeros() {
		return Matrix{};
	}

	// operators
	constexpr Matrix& operator+=(Matrix const& rhs) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				(*this)(i, j) += rhs(i, j);
				if constexpr (has_mod) {
					if ((*this)(i, j) >= mod) (*this)(i, j) -= mod;
				}
			}
		}
		return *this;
	}

	constexpr Matrix operator+(Matrix const& rhs) const {
		auto ans = *this;
		return ans += rhs;
	}

	constexpr Matrix& operator-=(Matrix const& rhs) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				(*this)(i, j) -= - rhs(i, j);
				if constexpr (has_mod) {
					if ((*this)(i, j) < 0) (*this)(i, j) += mod;
				}
			}
		}
		return *this;
	}

	constexpr Matrix operator-(Matrix const& rhs) const {
		auto ans = *this;
		return ans -= rhs;
	}

	template<int p>
	constexpr Matrix<T, n, p, mod> operator*(Matrix<T, m, p, mod> const& rhs) const {
		Matrix<T, n, p, mod> res{};
		for (int i = 0; i < n; i++) {
			// for large matrices swap the next two lines for better cache locality
			for (int j = 0; j < p; j++) {
				for (int k = 0; k < m; k++) {
					if constexpr (has_mod) res(i, j) = ((ll)res(i, j) + (ll)(*this)(i, k) * rhs(k, j)) % mod;
					else res(i, j) += (*this)(i, k) * rhs(k, j);
				}
			}
		}
		return res;
	}

	constexpr Matrix<T, n, n, mod> operator^(int k) const {
		// garantees matrix is square
		static_assert(n == m, "n != m");

		auto a = *this;
		auto ans = Matrix<T, n, n, mod>::identity();
		while(k) {
			if(k&1) ans = ans * a;
			a = a * a;
			k >>= 1;
		}
		return ans;
	}

	constexpr Matrix& operator*=(T x) {
		for (auto& i : mat) {
			if constexpr (has_mod) i = 1ll * i * x % mod;
			else i *= x;
		}
		return *this;
	}

	constexpr Matrix operator*(T x) const {
		auto ans = *this;
		return ans *= x;
	}

	constexpr bool operator==(Matrix<T, n, m, mod> const& rhs) const {
		return equal(mat.begin(), mat.end(), rhs.mat.begin());
	}

	constexpr Matrix<T, m, n, mod> transposed() const {
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