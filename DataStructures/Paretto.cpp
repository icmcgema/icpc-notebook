#include <bits/stdc++.h>
using namespace std;

// a paretto is a structure that has the property that
// for no point X there is no another point Y such that
// X[0] < Y[0] and X[1] < Y[1] 
template<typename K, typename V>
struct Paretto {
    using ii = pair<K, V>;

    set<ii> s;

    // adds a point {x, y} to the set
    void add_point(K const& x, V const& y) {
        auto p = ii{x, y};
        auto it = s.lower_bound(p);

        if (it->second >= y) return;

        auto p_it = s.insert(p).first;

        while (p_it != s.begin() and prev(p_it)->second <= y) {
            s.erase(prev(p_it));
        }
    }

    // return the maximum y of a point A such that A[0] >= x
    V get_best(K x) {
        auto it = s.lower_bound(ii{x, numeric_limits<V>::min()});

        if (it == s.end()) return numeric_limits<V>::min();
        return it->second;
    }
};