---
title: Compositional Inverse of Formal Power Series
documentation_of: //math/fps/compositional-inverse-of-formal-power-series.hpp
---

形式的冪級数の合成逆関数を Power Projection と Lagrange の反転公式を用いて計算する。

# compositional_inverse_of_formal_power_series

```cpp
template <typename Mint>
FormalPowerSeriesFriendlyNTT<Mint>
compositional_inverse_of_formal_power_series(
    FormalPowerSeriesFriendlyNTT<Mint> f, int deg = -1)
```

次を満たす形式的冪級数 $g(x)$ を $x^{\mathrm{deg}}$ で打ち切って返す。

$$
f(g(x)) \equiv x \pmod{x^{\mathrm{deg}}}.
$$

`deg` を省略した場合は `f.size()` 項を返す。`deg` が `f.size()` より大きい場合、`f` の不足する係数は $0$ とみなす。

## 制約

- $f(0)=0$
- $[x^1]f(x)\ne 0$
- `Mint` は NTT-friendly な素数 mod 上の ModInt
- `deg - 1 < Mint::mod()`
- `2 * bit_ceil(deg)` 点の NTT を実行できる

## 計算量

`deg` を $N$ とすると、

- 時間計算量: $O(N\log^2 N)$
- 空間計算量: $O(N)$

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

## 計算量

- 時間計算量: $O(n\log^2 n + m\log m)$
- 空間計算量: $O(n+m)$
