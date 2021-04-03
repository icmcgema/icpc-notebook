#include <bits/stdc++.h>
using namespace std;

vector<int> sieve(int n) {
    vector<char> s(n/2 + 1);
    for (int i = 1; i <= (sqrt(n) + 1) / 2; i++) {
        if (s[i] == 0) {
            for (int j = 2*(i*i + i); j <= (n-1)/2; j += 2*i + 1) {
                s[j] = 1;
            }
        }
    }

    vector<int> primes;
    if (n >= 2) primes.push_back(2);

    for (int i = 1; i <= (n-1) / 2; i ++) {
        if (s[i] == 0) {
            primes.push_back(2*i+1);
        }
    }

    return primes;
}