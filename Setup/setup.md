# Setup pré-contest

Esse setup serve para otimizar o tempo do time durante o contest, dando comandos e scripts para facilitar a criação de arquivos C++ a partir de um template, organizar em pastas, visualizar diferenças entre saídas esperadas e obtidas, etc.

## Como usar

Para usar rode `icpc <X>`, onde `<X>` é a letra do último problema do contest. Exemplo, `icpc K` se os problemas do contest vão de A a K. Este comando irá criar no diretório atual as pastas e arquivos:

```
|-- output/
|-- tasks/
	|-- A/
	...
	|-- K/
		|-- sol.cpp
		|-- test.sh
```
`./tasks` possui as pastas para cada problema, e `./output` irá ser preenchido sempre com o source do último problema testado, para que ele possa ser encontrado mais facilmente na hora da submissão.

`./tasks/<X>/` possui o `sol.cpp` (uma cópia do seu template) e `test.sh`. Ao rodar `./test.sh` dentro dessa pasta, o seu código é compilado e executado com o input dos `.in` dentro dessa pasta, e comparada com os `.out` correspondentes.


## Como configurar

Para configurar:

1. Copie o conteúdo deste diretório (exceto este arquivo) para uma pasta chamada `~/icpc-templates/`. 

	> Se você escolher outro nome, terá que mudar toda ocorrência de "~/icpc-templates" nos shell scripts.

2. Crie o seu template da maratona em `~/icpc-templates/template.cpp`, algo do tipo:
	```c++
	#include <bits/stdc++.h>

	#define fi first
	#define se second
	#define eb emplace_back

	using namespace std;
	typedef long long ll;

	int main() {
		ios::sync_with_stdio(0); cin.tie(0);
	}
	```
3. Customize com as suas flags de compilação as primeiras linhas de `~/icpc-templates/prep.sh` e `~/icpc-templates/test.sh`: 
	```bash
	CXXFLAGS="-std=c++17 -DLOCAL_PC -fsanitize=address,undefined -ggdb3 -Wall -Wextra -Wno-unused-result -Wshadow"
	```
4. Crie um alias no seu `~/.bashrc` para criar o comando `icpc`:
	```bash
	alias icpc="~/icpc-templates/prep.sh"
	```
5. Se você quiser usar headers de bits pré-compilados, inclua também no seu `~/.bashrc` o caminho para o include do seu `bits/stdc++.h`, como a seguir:
	```bash
	export BITS_PATH=/usr/include/x86_64-linux-gnu/c++/7/bits/stdc++.h
	```
	Você pode achar esse caminho compilando qualquer arquivo cpp que inclua bits/stdc++ com a flag `-H`, que diz ao g++ para imprimir os caminhos encontrados para os includes.
6. Opcional: também inclua a seguinte função no seu `~/.bashrc`:
	```bash
	tk() {
		if [ -z $1 ]; then
			test_case=1
		else
			test_case=$1
		fi

		while true; do 
			read -d $'\04' -p "Reading $test_case.in:
	" X
			echo "$X" > "$test_case.in"
			read -d $'\04' -p "Reading $test_case.out:
	" X
			echo "$X" > "$test_case.out"
			test_case=$(($test_case + 1))
		done
	}
	```

	Essa função serve para criar os casos de teste `1.in`, `1.out`, `2.in`, `2.out`, ..., etc. mais facilmente. Use rodando `tk [<caso de teste>]`, e o comando te dará um prompt dos conteúdos das entradas e saídas e gerará os arquivos .in e .out.
