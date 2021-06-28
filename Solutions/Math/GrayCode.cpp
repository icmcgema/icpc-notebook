#include <bits/stdc++.h>

using namespace std;

/**
 * Funções para a sequência de strings binárias 0000, 0001, 0011, 0010, 0110, 0111, 0101, 0100, 1100, ...
 * A sequencia é uma travessia por todos as strings binárias de certo tamanho, tal que a distância de Hamming
 * (número de bits diferentes) de cada string adjacente é 1.
 * Exemplo, [gray(0) = 000, ..., gray(7) = 100] é a sequencia de gray de strings binárias de tamanho 3
 * Essa sequencia também é um ciclo hamiltoniano de custo mínimo.
 * Algo parecido também pode ser encontrado para permutações que diferem por um swap de numeros adjacentes
 */
namespace GrayCode {
	
	int gray(int k) {
		return k^(k >> 1);
	}

	int order(int n) {
		int ans = 0;
		for(; n; n >>= 1)
			ans ^= n;
		return ans;
	}
};