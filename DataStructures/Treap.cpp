#include <bits/stdc++.h>
using namespace std;

mt19937 rd(10);
namespace Treap {

template<typename T>
struct Node {
    T val;
    int sz, h;
    Node *l, *r;
    bool flip = false;
    T sum = 0;

    Node(T const& v) : val(v), sz(1), h(rd()), l(nullptr), r(nullptr), sum(v) {};
};

using T = int;
using ptr = Node<T>*;

static void flush(ptr t) {
    if (!t) return;
    if (t->flip) {
        if (t->l) t->l->flip ^= true;
        if (t->r) t->r->flip ^= true;
        swap(t->l, t->r);
        t->flip = false;
    }
}

static void op(ptr t) {
    if (!t) return;

    t->sz = 1;
    t->sum = t->val;

    if (t->l) {
        t->sz += t->l->sz;
        t->sum += t->l->sum;
    }
    if (t->r) {
        t->sz += t->r->sz;
        t->sum += t->r->sum;
    }
}

static ptr merge(ptr l, ptr r) {
    if (!l) return r;
    if (!r) return l;
    flush(l), flush(r);

    if (l->h > r->h) {
        l->r = merge(l->r, r);
        op(l);
        return l;
    }
    else {
        r->l = merge(l, r->l);
        op(r);
        return r;
    }
}

static pair<ptr, ptr> split(ptr t, T const& v) {
    if (!t) return {};
    flush(t);

    ptr x;
    if (t->val < v) {
        tie(t->r, x) = split(t->r, v);
        op(t);
        return {t, x};
    }
    else {
        tie(x, t->l) = split(t->l, v);
        op(t);
        return {x, t};
    }
}

static pair<ptr, ptr> split_pos(ptr t, int pos) {
    if (!t) return {};
    flush(t);

    int p = (t->l ? t->l->sz : 0) + 1;

    ptr x;
    if (pos >= p) {
        tie(t->r, x) = split_pos(t->r, pos-p);
        op(t);
        return {t, x};
    }
    else {
        tie(x, t->l) = split_pos(t->l, pos);
        op(t);
        return {x, t};
    }
}

static void insert(ptr& root, T const& v) {
    auto [l, r] = split(root, v);
    l = merge(l, new Node(v));
    root = merge(l, r);
}

static void insert_pos(ptr& root, T const& v, int pos) {
    auto [l, r] = split_pos(root, pos);
    l = merge(l, new Node(v));
    root = merge(l, r);
}

static void erase(ptr& root, T const& v) {
    auto [l, aux] = split(root, v);
    ptr r;
    tie(aux, r) = split_pos(aux, 1);
    root = merge(l, r);
}

static void print(ptr root) {
    if (!root) return;
    flush(root);
    print(root->l);
    cout << root->val;
    print(root->r);
}

}; // end namespace Treap
