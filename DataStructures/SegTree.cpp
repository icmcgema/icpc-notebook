#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    struct Node {
        long long x;

        static auto join(Node const& lhs, Node const& rhs) -> Node {
            return {lhs.x + rhs.x};
        }

        void update(Node rhs) {
            x += rhs.x;
        }
    };

    int n;
    vector<Node> tree;

    SegTree(int n) :
        n(n), tree(n*4)
    {};

    SegTree(vector<Node> const& v) :
        n(v.size()), tree(n*4)
    {
        build(v, 0, 0, n-1);
    }

    auto build(vector<Node> const& v, int no, int l, int r) -> void {
        if (l == r) {
            tree[no] = v[l];
        }
        else {
            int m = (l+r)/2;
            build(v, no*2+1, l, m);
            build(v, no*2+2, m+1, r);
        
            tree[no] = Node::join(tree[no*2+1], tree[no*2+2]);
        }
    }

    auto get(int no, int l, int r, int a, int b) -> Node {
        if (a <= l and r <= b) {
            return tree[no];
        }

        int m = (l+r)/2;
        
        if (b <= m) return get(no*2+1, l, m, a, b);
        else if (a > m) return get(no*2+2, m+1, r, a, b);
        
        return Node::join(
            get(no*2+1, l, m, a, b),
            get(no*2+2, m+1, r, a, b)
        );
    }

    auto get(int a, int b) -> Node {
        return get(0, 0, n-1, a, b);
    }

    auto upd(int no, int l, int r, int p, Node const& val) -> void {
        if (l == r) {
            tree[no].update(val);
            return;
        }
        
        int m = (l+r)/2;

        if (p <= m) upd(no*2+1, l, m, p, val);
        else upd(no*2+2, m+1, r, p, val);

        tree[no] = Node::join(tree[no*2+1], tree[no*2+2]);
    }

    auto upd(int p, Node const& val) -> void {
        upd(0, 0, n-1, p, val);
    }
};