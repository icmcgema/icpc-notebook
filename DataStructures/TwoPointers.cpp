/*
	General structure to solve two pointers problems. Inspired by Codeforces EDU lesson
	https://codeforces.com/edu/course/2/lesson/9
*/

struct twopointer {

	struct state {

		state() {} // init state for empty interval

		void add(int x) { 
			// include code for adding x into current window
		}

		void rem(ll x) {
			// include code for removing x from current window
		}

		// if the state is considered good
		bool good() { 
			// include code to say if the state is good
		}
	};

	vector<int> vec;

	twopointer(vector<int> vec = {}) {
		this->vec = vec;
	}

	// solve the two pointers problem where subinterval is good if interval is good (here, empty intervals should always be good)
	// at each step, finds biggest interval for fixed r
	int solve_sub() {
		int l = 0;

		state st;
		for(int r = 0; r < vec.size(); ++r) {
			st.add(vec[r]);

			while(!st.good()) {
				st.rem(vec[l++]);
			}

			// calculation step 
			// [l, r] contains the biggest good interval ending at r
			ans += r - l + 1;
		}
		return ans;
	}

	// solve the two pointers problem where super interval is good if interval is good (here, empty intervals should always be BAD!, otherwise, by definition, all intervals should be good)
	// at each step, finds smallest interval for fixed r
	int solve_sup(ll k) {
		int l = 0;

		ll ans = 0;

		state st;
		for(int r = 0; r < vec.size(); ++r) {
			st.add(vec[r]);

			while(st.good()) {
				st.rem(vec[l++]);
			}

			// do calculation step

			// here, [l, r] is the first not good interval. [l-1, r] should have the smallest good interval
			// assume that if l == 0, there was no good interval yet
			ans += l;
		}
		return ans;
	}
}; 