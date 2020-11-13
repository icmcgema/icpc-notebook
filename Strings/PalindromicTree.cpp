/*
	A palindromic tree stores all distinct palindromes that appear as substrings of a string S. 
	There are at most |S| of them, believe me. Proof is by induction. If S = T + c, when adding character
	c, take the biggest palindrome created ending at c, let's call it P. If there would exist smaller palindromes 
	created at this moment, they would have already appeared as a prefix of P. That means the only new palindrome
	is the biggest one.
	Tree has two roots: -1 and 0. All nodes in subtree of -1 have odd length, and all nodes in subtree of 0 have even
	length. An edge of this tree with character c (U -- c --> V) means that V = cUc. Edge (-1 -- c --> V) means that V = c.
	A suffix link U --> V means that V is the greatest suffix of U that is also a palindrome.
	Construction:
	
	Create roots 0 and -1 and suffix link of 0 goes to -1 and suffix link of -1 goes to itself.
	Invariant: keep "last" pointer as the pointer to the last node added. "last" starts at -1
	Add character c:
	Lets find greatest palindrome ending at c. To do that, let's find biggest suffix link (S) of last that has character c
	to it's left, and then do S -- c --> U if U is not already there.
	To find suffix link, find second largest suffix link of last that has c to it's left. If it doesn't exist, suffix link is 0
	Properties:
	- Level of a node tells it's length
	- Suffix links of a node tells all nodes that end in a position
	- Suffix links forms a tree
	Applications:
	- Count number of distinct substrings that are palindromes
	- Count number of times a palindrome appears as substring
	- Find sum of lengths of all substring palindromes
	- Count triples i <= j < k such that Si,j is pal. and Sj+1,k it pal.
	- Find largest common palindrome substring between K strings.
	- Find kth smaller palindrome: precompute all palindromes and their frequencies and sort them using hash lcp
*/

#include <bits/stdc++.h>

using namespace std;

struct node {
	map<int, int> ch; // children
	int link, cnt; // how many times it appears as subtring
	int start; // first time this palindrome appears as subtring. If you want the last, just reverse the string
	int sz; // size of the palindrome
};

const int N = 100007;
node _tree[N + 2];
node * tree = _tree + 1;

void build(string & s, bool frequency_of_appearence = false) {
	tree[-1].link = -2;
	tree[-1].sz = -1;
	tree[0].link = -1;
	tree[0].sz = 0;

	int tt = 0;
	int last = -1;

	for(int i = 0; i < s.size(); ++i) {
		char c = s[i];
		// Add a new character
		while(i - tree[last].sz == 0 or s[i - tree[last].sz - 1] != c) last = tree[last].link;

		if(tree[last].ch.count(c) == 0) {
			++tt;
			tree[tt].sz = tree[last].sz + 2;
			tree[tt].cnt = 0;
			tree[tt].start = i - tree[tt].sz + 1;

			tree[last].ch[c] = tt;

			// Finds suffix link
			int u = tree[last].link;
			while(u != -2 and s[i - tree[u].sz - 1] != c) u = tree[u].link;
			tree[tt].link = u == -2? 0 : tree[u].ch[c];
		}
		last = tree[last].ch[c];
		tree[last].cnt++;
		// cout << "Found palindrome " <<  last << " as " << s.substr(tree[last].start, tree[last].sz) << endl;
	}

	// If you want to calculate frequencies for each palindrome
	if(frequency_of_appearence) {
		for(int i = tt; i > 0; --i) {
			tree[tree[i].link].cnt += tree[i].cnt;
		}
	}
}

deque<char> d;
void dfs(int u) {
	cout << string(d.begin(), d.end()) << " appears " << tree[u].cnt << " times, and starts at " << tree[u].start << endl;
	for(auto & [c, v] : tree[u].ch) {
		d.push_front(c);
		if(u == -1) d.pop_front();
		d.push_back(c);
		dfs(v);
		if(u != -1) d.pop_front();
		d.pop_back();
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	string s = "abacaba";
	build(s, true);

	dfs(-1);
	dfs(0);
}