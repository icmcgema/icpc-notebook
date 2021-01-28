#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct MergeSortTree {
    int n;
    vector<vector<T>> tree;

    MergeSortTree(vector<T> const& v) :
        n(v.size()), tree(n * 4)
    {
        build(v, 0, 0, n-1);
    }

    auto build(vector<T> const& v, int no, int l, int r) -> void {
        if (l == r) {
            tree[no] = {v[l]};
        }
        else {
            int m = (l+r)/2;

            build(v, no*2+1, l, m);
            build(v, no*2+2, m+1, r);

            tree[no].resize(r-l+1);
            
            merge(
                tree[no*2+1].begin(), tree[no*2+1].end(),
                tree[no*2+2].begin(), tree[no*2+2].end(),
                tree[no].begin()
            );
        }
    }

    // returns number of elements in sorted vector v in [x, y)
    auto count_range(vector<T> const& v, int x, int y) -> int {
        return lower_bound(v.begin(), v.end(), y) - lower_bound(v.begin(), v.end(), x);
    }

    // return numbe
    auto count_query(int a, int b, int x, int y) -> int {
        return count_query(0, 0, n-1, a, b, x, y);
    }

    auto count_query(int no, int l, int r, int a, int b, int x, int y) -> int {
        if (a <= l and r <= b) {
            return count_range(tree[no], x, y);
        }
        else {
            int m = (l+r)/2;

            if (b <= m) {
                return count_query(no*2+1, l, m, a, b, x, y);
            }
            else if (a > m) {
                return count_query(no*2+2, m+1, r, a, b, x, y);
            }
            else {
                return count_query(no*2+1, l, m, a, b, x, y) + 
                       count_query(no*2+2, m+1, r, a, b, x, y); 
            }
        }
    }
};