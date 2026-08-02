---
title: Composition of Formal Power Series
documentation_of: //math/fps/composition-of-formal-power-series.hpp
---

2 つの形式的冪級数の合成を計算する。

# composition_of_formal_power_series

```cpp
template <typename Mint>
FormalPowerSeriesFriendlyNTT<Mint> composition_of_formal_power_series(
    const FormalPowerSeriesFriendlyNTT<Mint>& outer,
    const FormalPowerSeriesFriendlyNTT<Mint>& inner, int deg = -1)
```

形式的冪級数 $f(x)=\mathrm{outer}(x)$ と $g(x)=\mathrm{inner}(x)$ に対して、

$$
f(g(x)) \bmod x^{\mathrm{deg}}
$$

を返す。返り値の要素数は常に `deg` であり、`outer` と `inner` の不足する係数は $0$ とみなす。

`deg` を省略した場合は `outer.size()` 項を返す。

## 制約

- $g(0)=0$（`inner` が空の場合も含む）
- `deg >= 0`
- `Mint` は NTT-friendly な素数 mod 上の ModInt
- `deg >= 2` のとき、`2 * bit_ceil(deg)` 点の NTT を実行できる

## 計算量

`deg` を $N$ とすると、

- 時間計算量: $O(N\log^2 N)$
- 空間計算量: $O(N)$
