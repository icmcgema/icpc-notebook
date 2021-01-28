#include <bits/stdc++.h>
using namespace std;

template<typename T, typename Cmp = less<T>>
struct MinQueue {
    constexpr static auto cmp = Cmp{};

    deque<pair<T, int>> q;
    int l = 0, r = 0;

    void push(T const& val) {
        while (!q.empty() and !cmp(q.back().first,val)) {
            q.pop_back();
        }
        q.emplace_back(val, r++);
    }

    void pop() {
        if (!q.empty() and q.front().second == l) {
            q.pop_front();
        }
        l++;
    }

    T get() {
        return q.front().first;
    }

    bool empty() {
        return q.empty();
    }

    int size() {
        return r-l;
    }
};