// https://cses.fi/problemset/task/1110/

#include <bits/stdc++.h>
using namespace std;

#define hash UISHDUIAHSDU
struct Hash {
	static constexpr int MOD[2] = {(int) 1e9+7, (int) 1e9+9};
	int val[2];

	Hash() { val[0] = val[1] = 0; }
	Hash(string const& s) { *this = calculateHash(s); }
	Hash(int x) { val[0] = x % MOD[0]; val[1] = x % MOD[1]; }
	Hash(int x, int y) { val[0] = x % MOD[0]; val[1] = y % MOD[1]; }

	static int add(int x, int y, int k) { x += y; if (x >= MOD[k]) x -= MOD[k]; return x; }
	static int sub(int x, int y, int k) { x -= y; if (x < 0) x += MOD[k]; return x; }
	static int mul(int x, int y, int k) { return 1ll * x * y % MOD[k]; }
	static int fpow(int x, int y, int k) {
		int r = 1;
		for (; y > 0; y /= 2, x = mul(x, x, k))
			if (y % 2 == 1) r = mul(r, x, k);
		return r;
	}
	static int divi(int x, int y, int k) { return mul(x, fpow(y, MOD[k] - 2, k), k); }
	static Hash pow(Hash x, int y) {
		Hash r = 1;
		for (; y >= 0; y /= 2, x *= x)
			if (y%2 == 1) r *= x;
		return r;
	}

	Hash operator+(Hash const& h) const { return Hash(add(val[0], h.val[0], 0), add(val[1], h.val[1], 1)); }
	Hash operator-(Hash const& h) const { return Hash(sub(val[0], h.val[0], 0), sub(val[1], h.val[1], 1)); }
	Hash operator*(Hash const& h) const { return Hash(mul(val[0], h.val[0], 0), mul(val[1], h.val[1], 1)); }
	Hash operator/(Hash const& h) const { return Hash(divi(val[0], h.val[0], 0), divi(val[1], h.val[1], 1)); }
	Hash& operator+=(Hash const& h) { return *this = *this + h; }
	Hash& operator-=(Hash const& h) { return *this = *this - h; }
	Hash& operator*=(Hash const& h) { return *this = *this * h; }
	Hash& operator/=(Hash const& h) { return *this = *this / h; }

	bool operator==(Hash const& h) const { return val[0] == h.val[0] && val[1] == h.val[1]; }
	bool operator!=(Hash const& h) const { return val[0] != h.val[0] || val[1] != h.val[1]; }

	static Hash calculateHash(string const& s, Hash const primes = Hash(31, 37)) {
		Hash cur = 0;
		Hash p = 1;
		for (char c : s) {
			cur += p * (c - 'a' + 1); // assuming that is a lowercase string
			p *= primes;
		}
		return cur;
	}
	static vector<Hash> calculateHashVector(string const& s, Hash const primes = Hash(31, 37)) {
		int n = s.size();
		Hash p = 1;
		vector<Hash> cur(n);
		for (int i = 0; i < n; i++) {
			if (i) cur[i] = cur[i-1];
			cur[i] += p * (s[i] - 'a' + 1);
			p *= primes;
		}
		return cur;
	}
	static vector<Hash> calculatePowerVector(Hash p, const int n) {
		vector<Hash> ans(n);
		ans[0] = 1;
		for (int i = 1; i < n; i++)
			ans[i] = ans[i-1] * p;
		return ans;
	}
};

ostream& operator<<(ostream& out, Hash const& h) {
	return out << "[" << h.val[0] << "," << h.val[1] << "]";
}

inline void minimalRotation(string s) {
	int n = s.size();
	s += s;

	Hash primes(31, 29);
	vector<Hash> hash = Hash::calculateHashVector(s, primes);
	vector<Hash> power = Hash::calculatePowerVector(primes, n);

	// lexicographically compares two substrings: s[A..A+n] and s[B..B+n]
	auto cmp = [&](int const A, int const B) {
		if (s[A] != s[B]) return s[A] < s[B];
		Hash h1, h2;
		int lo = 2, hi = n, mi;

		while(lo < hi) {
			mi = (lo + hi) / 2;
			h1 = hash[A + mi - 1] - (A ? hash[A - 1] : 0);
			h2 = hash[B + mi - 1] - (B ? hash[B - 1] : 0);
			if (A < B) h1 *= power[B - A];
			else h2 *= power[A - B];

			if (h1 != h2) hi = mi;
			else lo = mi + 1;
		}
		return s[A+hi-1] < s[B+hi-1];
	};

	vector<int> a(n);
	iota(a.begin(), a.end(), 0);
	nth_element(a.begin(), a.begin(), a.end(), cmp);
	cout << s.substr(a[0], n) << "\n";
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	string s; cin >> s;
	minimalRotation(s);
}