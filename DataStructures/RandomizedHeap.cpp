#include <bits/stdc++.h>
using namespace std;

mt19937 rd(10);
uniform_int_distribution<int> toss(0, 1);

// randomized heap https://cp-algorithms.com/data_structures/randomized_heap.html
// capable of O(log n) insertion, pop_min, melding (combining two heaps)
// and O(1) get_min
template<typename T>
struct RandomizedHeap {
    using ptr = unique_ptr<RandomizedHeap<T>>;

    T val;
    ptr l, r;

    RandomizedHeap() = default;
    RandomizedHeap(T x) : val(x), l(nullptr), r(nullptr) {};

    // combines two heaps a and b
    // consumes heap a and b, and procudes a new heap
    friend auto meld(ptr a, ptr b) -> ptr {
        if (!a) return b;
        if (!b) return a;

        // a is the root 
        if (a->val > b->val) swap(a, b);

        // 50/50 chance to combine b with each child of a 
        if (toss(rd)) a->l = meld(move(a->l), move(b));
        else a->r = meld(move(a->r), move(b));

        return a;
    }

    friend auto insert(ptr& a, T x) -> void {
        a = meld(move(a), make_unique<RandomizedHeap>(x));
    }

    friend auto pop(ptr& a) -> void {
        a = meld(move(a->l), move(a->r));
    }

    auto min() -> T {
        return val;
    }
};


int main() {
    RandomizedHeap<int>::ptr a, b;

    for (int i = 0; i < 10; i += 2) {
        insert(a, i);
        insert(b, i+1);
    }

    cout << a->min() << '\n';
    cout << b->min() << '\n';

    pop(a), pop(a);
    pop(b);

    auto c = meld(move(a), move(b));

    while (c) {
        cout << c->min() << ' ';
        pop(c);
    }
    cout << '\n';
}