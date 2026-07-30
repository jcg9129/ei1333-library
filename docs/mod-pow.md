---
title: Mod Pow (べき乗)
documentation_of: //math/combinatorics/mod-pow.hpp
---

ある値のべき乗を求める。

# mod_pow

```cpp
T mod_pow(T x, int64_t n, const T& p)
```

$x^n \bmod p$ を返す。

## 計算量

- $O(\log n)$
