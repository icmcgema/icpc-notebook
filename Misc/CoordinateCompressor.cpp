/* 
	Easy-to-use util DS for coordinate compression of any tyoe
	Just initialize it with a vector, or call 'add()', and you can access
	compressed values with [] operator.
*/

template<typename T>
struct CoordCompressor {
	vector<T> vec;

	CoordCompressor(): sorted(false) {}
	CoordCompressor(const vector<T>& v): sorted(false) {
		add(v);
	}
	template <typename ...Ts>
	void add(const Ts&... args) {
		if(sorted_) throw runtime_error("Can't add elements after accessing them");
		(vec.push_back(args), ...);
	}
	void add(const vector<T>& v) {
		if(sorted_) throw runtime_error("Can't add elements after accessing them");
		for(auto x : v) 
			vec.push_back(x);
	}

	// Returns order of x in O(logN)
	int operator[](const T& x) {
		if(!sorted_) {
			sorted_ = true;
			sort(vec.begin(), vec.end());
		}
		return lower_bound(vec.begin(), vec.end(), x) - vec.begin();
	}

private:
	bool sorted_;
};

// usage:
// CoordCompressor<ll> comp;
// comp.add({10, 1344, 56});
// comp.add(123, 42);
// int idx = comp[123] // returns 3