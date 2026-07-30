---
title: Binomial (二項係数)
documentation_of: //math/combinatorics/binomial.hpp
---

二項係数 ${}_n \mathrm{C} _k$ を $\displaystyle \frac {k(k-1)\dots (n-k+1)} {k(k-1)\dots 1}$ を利用して求める。

$k$ が小さい時に有効。

# binomial

```cpp
T binomial(int64_t N, int64_t K)
```

${}_n \mathrm{C} _k$ を返す。

## 計算量

- $O(K \log K)$

ただし逆元が $O(1)$ で求まる場合 $O(K)$
