#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 200007;

struct no {
	int l, r, par, suf;
	string * s;
	map<char, int> f;
	int len() {return r - l + 1;}
	char operator[](int i) {return (*s)[l+i];}
};

no t[N + N];

int new_node(int l, int r, int par, string * str) {
	static int ptr = 0;
	ptr++;
	t[ptr].l = l;
	t[ptr].r = r;
	t[ptr].par = par;
	t[ptr].s = str;
	return ptr;
}


void print_node(int u) {
	printf("Vert = %d\t str = %s\t par = %d\n", u, (*t[u].s).substr(t[u].l, t[u].len()).c_str(), t[u].par);
}

void dfs(int u) {
	if(u) print_node(u);

	for(pair<char, int> g : t[u].f) {
		dfs(g.second);
	}
}

void build(string & s, int n) {
	int i, j, cn, cd, ns = 0;
	i = j = cn = cd = 0;

	t[0].r = -1;

	// invariante (cn, cd-1) representa a string S[i .. j-1]
	for(j = 0; j < n; ++j) {
		for(; i <= j; ++i) {
			if((cd == t[cn].len() and t[cn].f.count(s[j])) or (cd != t[cn].len() and t[cn][cd] == s[j])) { // se eh o caso 1
				// atualiza a invariante e vai pra proxima iteracao
				if(cd == t[cn].len()) {
					cn = t[cn].f[s[j]];
					cd = 0;
				} 
				cd++;
				break;
			} else if(cd == t[cn].len()) {
				t[cn].f[s[j]] = new_node(j, n-1, cn, &s); // como esse novo noh eh uma folha, seu r eh n-1 automaticamente
				if(cn) { // voce nao esta na raiz
					cn = t[cn].suf;
					cd = t[cn].len();
				}
			} else if(cd < t[cn].len()) { // caso = 3
				// Divide a aresta no meio, criando um novo noh interno e um novo noh folha
				int mid = new_node(t[cn].l, t[cn].l + cd - 1, t[cn].par, &s);
				t[t[mid].par].f[t[mid][0]] = mid;

				t[mid].f[s[j]] = new_node(j, n-1, mid, &s);
				t[mid].f[t[cn][cd]] = cn;
				t[cn].l += cd;
				t[cn].par = mid;
				if(ns) t[ns].suf = mid;
				

				// Parte 2
				cn = t[mid].par;
				int g; // g indica que o cn representa o cara s[i+1, g-1]. Quero atualizar cn ateh que g seja igual a j
				if(cn) {
					cn = t[cn].suf;
					g = j - cd;
				} else g = i+1;

				while(g < j and g + t[t[cn].f[s[g]]].len() <= j) {
					cn = t[cn].f[s[g]];
					g += t[cn].len();
				}
				if(g == j) {
					t[mid].suf = cn;
					cd = t[cn].len();
					ns = 0;
				} else {
					ns = mid;
					cn = t[cn].f[s[g]];
					cd = j - g;
				}
			}
		}
	}
}

bool find(string & s) {
	int cn, cd;
	cn = 0;
	cd = -1;

	for(int i = 0; i < s.size(); ++i) {
		char c = s[i];
		if(cd + 1 == t[cn].len()) {
			if(t[cn].f.count(c)) {
				cn = t[cn].f[c];
				cd = 0;
			} else return false;
		} else {
			if(c == t[cn][cd+1]) ++cd;
			else return false;
		}
	}

	return true;
}

int main() {
	string s;
	cin >> s;

	build(s, s.size());

	int q;
	cin >> q;

	dfs(0);

	for(int i = 0; i < q; ++i) {
		string str;
		cin >> str;

		if(find(str)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
}