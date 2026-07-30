---
title: Coeff of Rational Function
documentation_of: //math/fps/coeff-of-rational-function.hpp
---

$K$ 次多項式 $P(x), Q(x)$ に対して $\displaystyle [x^N] \frac{P(x)}{Q(x)}$ を Bostan-Mori algorithm によって計算する。

# coeff_of_rational_function

```cpp
Mint coeff_of_rational_function(FPS<Mint> P, FPS<Mint> Q, int64_t k)
```

## 計算量

$O(K \log K \log N)$
