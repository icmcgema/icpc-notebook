// https://codeforces.com/blog/entry/96344

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

/*
	- O3: Auto-vectorize the code if the mentioned architectures allow it. This can make your code much faster by using SIMD 
		(single instruction, multiple data) which kinda parallelizes your code on an instruction level. More info below.
		Function inlining — inlines functions aggressively if possible (and no, marking functions as inline doesn't inline functions, 
		nor does it give hints to the compiler)
		Unrolls loops more aggressively than O2 (this might lead to instruction cache misses if generated code size is too large)

	- unroll-loops: Enables aggressive loop unrolling, which reduces the number of branches and optimizes parallel computation, 
		but might increase code size too much and lead to instruction cache misses.	

	- avx2: Instruction set that provide 8, 16 and 32 byte vector instructions 
	(i.e., you can do some kinds of operations on pairs of 8 aligned integers at the same time).

	- lzcont: constant time __builtin_clz

	- popcnt: constant time __builtin_popcount
	
	- bmi, bmi2: These are bit manipulation instruction sets. 
	They provide even more bitwise operations like ctz, blsi, and pdep
*/