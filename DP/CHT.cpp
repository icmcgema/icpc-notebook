#include <bits/stdc++.h>
using namespace std;

// Dynamic Hull. Usa só inteiros, mas se der overflow, tem comentarios pra transformar pra double
namespace CHT {
	using ll = long long;
	const ll isQuery=-(1LL<<62);
	struct Line {
	    ll m, b;int id;
	    Line(ll m_, ll b_, int id_) : m(m_), b(b_), id(id_) {}
	    mutable multiset<Line>::iterator it,e;
	    const Line* succ() const {
	        return next(it)==e ? 0 : &*next(it);
	    }
	    bool operator<(const Line& rhs) const {
	        if (rhs.b!=isQuery) return m<rhs.m;
	        const Line* s=succ();
	        if (!s) return 0;
	        ll x = rhs.m;
	        return b - s->b < (s->m - m)*x;
	        // se der overflow, substitua a linha de cima por
	        // return b - s->b < double(s->m - m) * double(x);
	    }
	};
	struct DynamicHull : public multiset<Line> {
	    bool bad(iterator y) {
	        auto z=next(y);
	        if (y==begin()) {
	            if (z==end()) return 0;
	            return y->m == z->m && y->b <= z->b;
	        }
	        auto x=prev(y);
	        if (z==end()) return y->m==x->m&&y->b<=x->b;
	        return (x->b - y->b)*(z->m - y->m)>=(y->b - z->b)*(y->m - x->m);
	        // se der overflow, substitua a linha de cima por
	        // return double(x->b - y->b)*double(z->m - y->m) >= double(y->b - z->b)*double(y->m - x->m);
	    }

	    // O(logN), N = numero de linhas
	    void insertLine(ll m, ll b, int id) {
	        auto y = insert({m, b, id});
	        y->it=y; y->e=end();
	        if (bad(y)) {erase(y);return;}
	        while (next(y)!=end() && bad(next(y))) erase(next(y));
	        while (y!=begin() && bad(prev(y))) erase(prev(y));
	    }

	    // O(logN), N = numero de linhas
	    pair<ll, int> getMax(ll x) {
	        auto l=*lower_bound({x, isQuery, 0});
	        return {l.m*x+l.b, l.id};
	    }
	};
}