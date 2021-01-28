#include <bits/stdc++.h>
using namespace std;

template<typename T, typename Cmp = less<T>>
struct MinQueue {
    constexpr static auto cmp = Cmp{};

    deque<pair<T, int>> q;
    int l = 0, r = 0;

    auto push(T const& val) -> void {
        while (!q.empty() and !cmp(q.back().first,val)) {
            q.pop_back();
        }
        q.emplace_back(val, r++);
    }

    auto pop() -> void {
        if (!q.empty() and q.front().second == l) {
            q.pop_front();
        }
        l++;
    }

    auto get() -> T {
        return q.front().first;
    }

    auto empty() -> bool {
        return q.empty();
    }

    auto size() -> int {
        return r-l;
    }
};