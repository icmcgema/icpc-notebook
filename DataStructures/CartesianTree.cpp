#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct Cartesian {
	vector<int> L, R;
	vector<T> vec;
	stack<int> st;

	// root in data structure is always 0. Actual root is R[0]
	Cartesian() {
		// sentinel
		st.emplace();
		L.eb(), R.eb();
		vec.eb();
	}

	// O(n) amortized after n invocations, but O(tree height) in worst case. 
	void add(int x) {
		vec.eb(x);
		int u = vec.size()-1;
		L.eb(), R.eb();

		while(st.size() > 1 and vec[st.top()] > vec.back()) {
			st.pop();
		}

		int v = st.top();
		L.back() = R[v];
		R[v] = u;
		st.emplace(u);
	}

	// returns index of the root of the tree
	int root() const {
		return R[0];
	}

	// get value of node i
	T& operator[](int i) const {
		return vec[i];
	}
	
	int left(int i) const {
		return L[i];
	}
	
	int right(int i) const {
		return R[i];
	}

	// in order traversal
	void traverse(int u, ostream& os) const {
		if(u == 0) return;
		traverse(L[u], os);
		traverse(R[u], os);
		os << pre[vec[u]] << ' ';
	}
	
	// in order traversal
	void traverse(ostream& os) const {
		traverse(root(), os);
	}

	friend ostream& operator<<(ostream& os, const Cartesian& tree) {
		tree.traverse(os);
		return os;
	}

};
