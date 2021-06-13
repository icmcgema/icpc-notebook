#include <bits/stdc++.h>

using namespace std;

namespace SuffixArray {

	// returns lcp array, with size a.size()-1, in which lcp[i] represents 
	// the longest common prefix between suffix in position i and the one in i+1
	// Complexidade: O(n)
	vector<int> build_lcp(vector<int> & a, string & s) {
		int n = a.size();
		vector<int> pos(n), lcp(n-1);
		for(int i = 0; i < n; ++i) {
			pos[a[i]] = i;
		}

		int sz = 0;
		for(int i = 0; i < n; ++i) {
			if(pos[i] == n-1) continue;
			int j = a[pos[i] + 1];
			while(i + sz < n and j + sz < n and s[i + sz] == s[j + sz]) sz++;
			lcp[pos[i]] = sz;
			if(sz) sz--;
		}
		return lcp;
	}


	// Retorna um vetor com os indices de inicio de prefixo.
	// Cuidado, essa funcao adiciona um caractere $ no final da string
	// Complexidade: O(n logn )
	vector<int> build_sufix_array(string & s) {
		s += '$';
		int n = s.size();
		vector<int> head(n), a(n), a1(n), c(n), c1(n);

		iota(a.begin(), a.end(), 0);
		sort(a.begin(), a.end(), [&](int i, int j) {
			return s[i] < s[j];
		});

		int cc = 0;
		for(int i = 0; i < n; ++i) {
			if(i == 0 or s[a[i]] != s[a[i-1]]) {
				c[a[i]] = cc; 
				head[cc++] = i;
			} else c[a[i]] = c[a[i-1]];
		}

		int l = 1;
		while(l < n) {
			for(int i = 0; i < n; ++i) {
				j = (a[i] - l + n)%n;
				a1[head[c[j]]++] = j;
			}
			cc = 0;

			head.assign(head.size(), 0);
			for(int i = 0; i < n; ++i) {
				if(i == 0 or c[a1[i]] != c[a1[i-1]] or c[(a1[i] + l)%n] != c[(a1[i-1] + l)%n]) {
					head[cc] = i;
					c1[a1[i]] = cc++;
				} else c1[a1[i]] = c1[a1[i-1]];
			}

			a = a1;
			c = c1;
			l <<= 1;
		}

		return a;
	}

};