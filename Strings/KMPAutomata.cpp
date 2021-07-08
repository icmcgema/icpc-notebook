#include <bits/stdc++.h>

using namespace std;


// what the string stores
template<typename T>
struct KMPAutomata {
	vector<int> phi;
	vector<unordered_map<T, int>> to;
	vector<T> str;

	KMPAutomata(){}
	KMPAutomata(const vector<T>& vec){
		build(vec);
	}

	KMPAutomata(const string& s) {
		build(vector<char>(s.begin(), s.end()));
	}	

	void build(vector<T> s) {
		phi.resize(s.size());
		to.resize(s.size() + 1);
		str = s;

		phi[0] = 0;
		for (int i = 1; i < s.size(); i++) {
			int& j = phi[i];
			j = phi[i-1];
			while(j and s[j] != s[i]) j = phi[j-1];

			if (s[i] == s[j]) j++;
		}

	}

	// next state if I add character c
	int next(int j, T c) {

		if(to[j].count(c)) return to[j][c];
		int & memo = to[j][c];

		while(j and (j == str.size() or c != str[j])) j = phi[j - 1];

		if(c == str[j]) j++;

		return memo = j;
	} 
};