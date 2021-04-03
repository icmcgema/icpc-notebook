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

// creation + 1 mult has higher time as 1 int128 mulmod
// becomes faster afer around 4 multiplications + inits
// up to 6 times faster when doing lots of multiplications
// modulo de same number
// -----------------------------------------------------------
//                    benchmark results
// -----------------------------------------------------------
// int64modmul/1          19.0 ns         19.0 ns     36185356
// int64modmul/2          53.6 ns         53.6 ns     12638112
// int64modmul/4           117 ns          117 ns      6188974
// int64modmul/8           231 ns          231 ns      3026745
// int64modmul/16          465 ns          465 ns      1499313
// int64modmul/32          954 ns          954 ns       718907
// int64modmul/64         1900 ns         1899 ns       369682
// int64modmul/128        3782 ns         3780 ns       183062
// int64modmul/256        7663 ns         7659 ns        90720
// int64modmul/512       15193 ns        15185 ns        45400
// int64modmul/1024      30072 ns        30051 ns        23488
// int64modmul/2048      59431 ns        59398 ns        10000
// int64modmul/4096     112081 ns       112020 ns         7679
// -----------------------------------------------------------
// int64mont/1            56.8 ns         56.7 ns     12108520
// int64mont/2            58.7 ns         58.6 ns     11591214
// int64mont/4            63.9 ns         63.8 ns     10452542
// int64mont/8            80.0 ns         80.0 ns      8625561
// int64mont/16            116 ns          116 ns      5997047
// int64mont/32            188 ns          188 ns      3744182
// int64mont/64            334 ns          334 ns      2051937
// int64mont/128           620 ns          619 ns      1113791
// int64mont/256          1200 ns         1199 ns       587902
// int64mont/512          2321 ns         2320 ns       298828
// int64mont/1024         4631 ns         4628 ns       152314
// int64mont/2048         9186 ns         9182 ns        75944
// int64mont/4096        18280 ns        18272 ns        38717