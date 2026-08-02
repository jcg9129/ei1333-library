---
title: Enumerate Coefficients of Powers of Formal Power Series
documentation_of: //math/fps/enumerate-coefficients-of-powers.hpp
---

形式的冪級数の冪の特定次数の係数を Power Projection を用いて列挙する。

# enumerate_coefficients_of_powers

```cpp
template <typename Mint>
FormalPowerSeriesFriendlyNTT<Mint> enumerate_coefficients_of_powers(
    FormalPowerSeriesFriendlyNTT<Mint> f,
    FormalPowerSeriesFriendlyNTT<Mint> g = {Mint(1)}, int m = -1)
```

$n=\mathrm{f.size()}-1$ とする。次の値を $k=0,1,\ldots,m$ について列挙する。

$$
[x^n]f(x)^k g(x).
$$

`m` を省略した場合は $m=n$ とする。合成逆関数の計算で用いる Power Projection の特殊形である。

## 制約

- `f` は空でない
- `Mint` は NTT-friendly な素数 mod 上の ModInt
- `2 * bit_ceil(f.size())` 点の NTT を実行できる

## 計算量

- 時間計算量: $O(n\log^2 n + m\log m)$
- 空間計算量: $O(n+m)$
