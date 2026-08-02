---
title: Count Bounded Increasing Sequences
documentation_of: //math/combinatorics/count-bounded-increasing-sequences.hpp
---

広義単調増加な整数列に上限が与えられたとき、条件を満たす列の個数を求めます。

# count_bounded_increasing_sequences

```cpp
template <typename Mint>
Mint count_bounded_increasing_sequences(
    const vector<int> &lower_bounds,
    const vector<int> &upper_bounds)
```

長さ $N$ の広義単調増加な整数列 $B$ であって、すべての $i$ について

$$
\mathrm{lower\_bounds}_i \leq B_i \lt \mathrm{upper\_bounds}_i
$$

を満たすものの個数を返します。空列の個数は $1$ とします。上下限は単調でなくても構いません。上限のみを指定したい場合は、`lower_bounds` のすべての要素を $0$ にします。

## 制約

- $0 \leq \mathrm{upper\_bounds}_i$
- `lower_bounds.size() == upper_bounds.size()`
- $0 \leq \mathrm{lower\_bounds}_i$
- `Mint` は NTT-friendly modint
- $N + U_{N-1} - L_0 + 6 \lt$ `Mint::mod()`

ここで、$L$ は下限の prefix max、$U$ は上限の suffix min とします。

## 計算量

$H=U_{N-1}-L_0$ とします。

- $O((N+H)\log^2(N+H))$

## 参考

- [上限付き単調増加列の数え上げ](https://noshi91.hatenablog.com/entry/2023/07/21/235339)
