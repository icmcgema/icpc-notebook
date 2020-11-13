// https://csacademy.com/contest/archive/task/and-closure/statement/

#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second
#define mset(a, b) memset(a, b, sizeof(a))
#define DBG(x) cout << "[" << #x << "]: " << x << endl
using ll = long long;
using pii = pair<int, int>;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#endif

template<class Ty> Ty randint(Ty a, Ty b) { return uniform_int_distribution<Ty>(a, b)(rng); }
template<class num> inline void rd(num& x) {
	char c, neg = 0; while(isspace(c = getchar_unlocked()));
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar_unlocked())) x = (x << 3) + (x << 1) + c - '0';
	x = neg ? -x : x; }
template <class Ty, class... Args> inline void rd(Ty& x, Args&... args) { rd(x); rd(args...); }

const int MAXN = 1 << 20, INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

void fwht(vector<ll>& v, bool invert) {
	int n = v.size();
	for (int mlen = 1; mlen + mlen <= n; mlen <<= 1) {
		for (int i = 0; i < n; i += mlen + mlen) {
			for (int j = 0; j < mlen; j++) {
				ll a = v[i + j], b = v[i + j + mlen]; // solving (a + bx) for x = {1, -1}. if `or convolution`, use roots x=1, x=0
				v[i + j] = b;
				v[i + j + mlen] = a + b;
				if (invert) v[i + j] = b - a, v[i + j + mlen] = a;

				if (v[i+j] < 0) v[i+j] += MOD;
				if (v[i+j+mlen] >= MOD) v[i+j+mlen] -= MOD;
			}
		}
	}
}

inline void mul(vector<ll>& f1, vector<ll> const& f2) {
	for (int i = 0; i < MAXN; i++) f1[i] = f1[i] * f2[i] % MOD;
}

inline vector<ll> getFreq(vector<ll> const& a) {
	vector<ll> f(MAXN);
	for (ll x : a) f[x]++;
	for (ll& x : f) x %= MOD;
	return f;
}

inline int solve(vector<ll>& v, int y) {
	v = getFreq(v);
	fwht(v, false);
	vector<ll> r = v;
	for (y--; y > 0; y /= 2, mul(v, v)) if (y&1) mul(r, v);
	fwht(r, true);
	int ans = 0;
	for (int i = 0; i < MAXN; i++) ans += r[i] != 0;
	return ans;
}

int main() {
	int n; rd(n);
	vector<ll> a(n+1);
	for (int i = 0; i < n; i++) rd(a[i]);
	printf("%d\n", solve(a, n));
}