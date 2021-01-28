#include <bits/stdc++.h>
using namespace std;

mt19937 rd(10);

template<typename T>
struct Treap {
    struct Node {
        T val;
        int sz, h;
        unique_ptr<Node> l, r;

        Node(T const& v) : val(v), sz(1), h(rd()), l(nullptr), r(nullptr) {};

        auto print() -> void {
            if (l) l->print();
            cout << val << ' ';
            if (r) r->print();
        }
    };

    using ptr = unique_ptr<Node>;

    ptr root;

    auto op(Node* t) -> void {
        if (!t) return;

        t->sz = 1;
        if (t->l) t->sz += t->l->sz;
        if (t->r) t->sz += t->r->sz;
    }

    auto merge(ptr l, ptr r) -> ptr {
        if (!l) return r;
        if (!r) return l;

        if (l->h > r->h) {
            l->r = merge(move(l->r), move(r));
            op(l.get());
            return l;
        }
        else {
            r->l = merge(move(l), move(r->l));
            op(r.get());
            return r;
        }
    }

    auto split(ptr t, T const& v) -> pair<ptr, ptr> {
        if (!t) return {};

        ptr x;
        if (t->val < v) {
            tie(t->r, x) = split(move(t->r), v);
            op(t.get());
            return {move(t), move(x)};
        }
        else {
            tie(x, t->l) = split(move(t->l), v);
            op(t.get());
            return {move(x), move(t)};
        }
    }

    auto split_pos(ptr t, int pos) -> pair<ptr, ptr> {
        if (!t) return {};

        int p = (t->l ? t->l->sz : 0) + 1;

        ptr x;
        if (pos >= p) {
            tie(t->r, x) = split_pos(move(t->r), pos-p);
            op(t.get());
            return {move(t), move(x)};
        }
        else {
            tie(x, t->l) = split_pos(move(t->l), pos);
            op(t.get());
            return {move(x), move(t)};
        }
    }

    auto insert(T const& v) -> void {
        auto [l, r] = split(move(root), v);
        l = merge(move(l), make_unique<Node>(v));
        root = merge(move(l), move(r));
    }

    auto insert_pos(T const& v, int pos) -> void {
        auto [l, r] = split_pos(move(root), pos);
        l = merge(move(l), make_unique<Node>(v));
        root = merge(move(l), move(r));
    }

    auto erase(T const& v) -> void {
        auto [l, aux] = split(move(root), v);
        ptr r;
        tie(aux, r) = split_pos(move(aux), 1);
        root = merge(move(l), move(r));
    }

    auto print() -> void {
        if (root) root->print();
        cout << '\n';
    }

};

auto main() -> int {
    Treap<int> t;

    t.insert(1);
    t.insert(4);
    t.insert(-1);
    t.insert(-1);

    t.print();

    t.insert_pos(2, 0);
    t.insert_pos(3, 1);

    t.print();
}