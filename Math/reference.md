# Math Reference

## Table of Contents

1. [Harmonic Progression](###harmonic-Progression)


### Harmonic Progression

Aproximação pra soma parcial de progressão harmônica (**funciona muito bem pra `n` grande**):
```cpp
  // a = first value, d = difference between consecutive denominators, n = number of terms
  double partial_sum(double a, double d, double n) {
    return log( (2 * a + (2 * n - 1) * d)/(2 * a - d) )/d;
  }
```
