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

// ------------------- Another implementation, using two stacks (bigger code, but more powerful) --------------------- //

template<class T, T F(T, T) = std::min<T>>
struct minstack {
	stack<pair<T, T> > s;
 
	void push(T x) {
		if (!s.size()) s.push({x, x});
		else s.push({x, F(s.top().second, x)});
	}
	T top() { return s.top().first;	}
	T pop() {
		T ans = s.top().first;
		s.pop();
		return ans;
	}
	int size() { return s.size(); }
	T min() { return s.top().second; }
};
 
template<class T, T F(T, T) = std::min<T>>
struct minqueue {
	minstack<T, F> s1, s2;
 
	void push(T x) { s1.push(x); }
	void move() {
		if (s2.size()) return;
		while (s1.size()) {
			T x = s1.pop();
			s2.push(x);
		}
	}
	T front() { return move(), s2.top(); }
	T pop() { return move(), s2.pop(); }
	int size() { return s1.size()+s2.size(); }
	T min() {
		if (!s1.size()) return s2.min();
		else if (!s2.size()) return s1.min();
		return F(s1.min(), s2.min());
	}
};
