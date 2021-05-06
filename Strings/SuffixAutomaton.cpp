/** Suffix automaton structure. O(N) to build */
struct SuffixAutomaton {
	struct State {
		int len, link;
		map<char, int> next;
	};

	vector<State> st;
	int last;

	SuffixAutomaton(string const& s) {
		int n = s.size();
		st.reserve(2 * n);

		st.push_back(State{0, -1});
		last = 0;

		for (int i = 0; i < n; i++) { // extend current char
			st.push_back(State{i + 1, 0});
			int r = (int) st.size() - 1;

			int p = last;
			while(p >= 0 && st[p].next.find(s[i]) == st[p].next.end()) {
				st[p].next[s[i]] = r;
				p = st[p].link;
			}

			if (p != -1) {
				int q = st[p].next[s[i]];
				if (st[p].len + 1 == st[q].len) {
					st[r].link = q;
				} else { // split and add q'
					st.push_back(State{st[p].len + 1, st[q].link, st[q].next});
					int qq = (int) st.size() - 1;

					st[q].link = st[r].link = qq;
					while(p >= 0 && st[p].next[s[i]] == q) {
						st[p].next[s[i]] = qq;
						p = st[p].link;
					}
				}
			}

			last = r;
		}
	}
};
