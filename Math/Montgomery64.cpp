#include <bits/stdc++.h>
using namespace std;

using u128 = __uint128_t;
using i128 = __int128_t;
using u64 = uint64_t;
using i64 = int64_t;

namespace {
    inline u64 hi(u128 x) {
        return u64(x >> 64);
    }

    inline u64 lo(u128 x) {
        return u64(x);
    }
}

struct Montgomery64 {
    Montgomery64(u64 n) : mod(n), inv(1), r2(-n % n) {
        for (int i = 0; i < 6; i++) {
            inv *= 2 - n * inv;
        }

        one = r2;

        r2 = u128(r2) * r2 % n;
    }

    u64 mod, inv, r2, one;

    u64 init(u64 x) {
        return mult(x, r2);
    }

    u64 reduce(u128 x) {
        u64 q = lo(x) * inv;
        i64 a = hi(x) - hi(u128(q) * mod);
        if (a < 0)
            a += mod;
        return a;
    }

    u64 mult(u64 a, u64 b) {
        return reduce(u128(a) * b);
    }
};

// creation + 1 mult has equal execution time as 1 int128 mulmod
// up to 2.5 times faster when doing lots of multiplications
// modulo de same number
// -----------------------------------------------------------
//                    benchmark results
// -----------------------------------------------------------
// int64modmul/1          10.1 ns         10.1 ns     65643538
// int64modmul/2          21.6 ns         21.5 ns     30587116
// int64modmul/4          40.3 ns         40.2 ns     17132524
// int64modmul/8          83.2 ns         83.1 ns      8281352
// int64modmul/16          184 ns          184 ns      3879638
// int64modmul/32          391 ns          390 ns      1805350
// int64modmul/64          761 ns          760 ns       856000
// int64modmul/128        1518 ns         1516 ns       463365
// int64modmul/256        3095 ns         3090 ns       228800
// int64modmul/512        6380 ns         6371 ns       113619
// int64modmul/1024      12464 ns        12449 ns        57368
// int64modmul/2048      24474 ns        24452 ns        28183
// int64modmul/4096      48872 ns        48813 ns        13930
// -----------------------------------------------------------
// int64mont/1            8.95 ns         8.93 ns     75784040
// int64mont/2            12.9 ns         12.9 ns     54609868
// int64mont/4            20.4 ns         20.4 ns     34621673
// int64mont/8            34.9 ns         34.9 ns     19985642
// int64mont/16           66.7 ns         66.7 ns     10422145
// int64mont/32            137 ns          136 ns      5122867
// int64mont/64            279 ns          279 ns      2516347
// int64mont/128           572 ns          572 ns      1190575
// int64mont/256          1133 ns         1132 ns       604272
// int64mont/512          2319 ns         2315 ns       302561
// int64mont/1024         4519 ns         4515 ns       153520
// int64mont/2048         9794 ns         9732 ns        74967
// int64mont/4096        20945 ns        20655 ns        32777