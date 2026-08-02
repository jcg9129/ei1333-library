---
title: Count Bounded Increasing Sequences
documentation_of: //math/combinatorics/count-bounded-increasing-sequences.hpp
---

広義単調増加な整数列に上限が与えられたとき、条件を満たす列の個数を求めます。

# count_bounded_increasing_sequences

```cpp
template <template <typename> class FPS, typename Mint>
Mint count_bounded_increasing_sequences(
    const vector<int> &lower_bounds,
    const vector<int> &upper_bounds)
```

長さ $N$ の広義単調増加な整数列 $B$ であって、すべての $i$ について

$$
\mathrm{lower\_bounds}_i \leq B_i \leq \mathrm{upper\_bounds}_i
$$

を満たすものの個数を返します。空列の個数は $1$ とします。上下限は単調でなくても構いません。上限のみを指定したい場合は、`lower_bounds` のすべての要素を $0$ にします。

## 制約

- $0 \leq \mathrm{upper\_bounds}_i$
- `lower_bounds.size() == upper_bounds.size()`
- $0 \leq \mathrm{lower\_bounds}_i$
- $N + \max_i \mathrm{upper\_bounds}_i + 1 \lt$ `Mint::mod()`

## 計算量

$M = 1 + \max_i \mathrm{upper\_bounds}_i$ とします。下限を prefix max、上限を suffix min で置き換えたものをそれぞれ $L, U$ とします。$L$ の極大な定値区間を $[l_k,r_k)$ とし、

$$
S=N+\sum_k (U_{r_k-1}-L_{l_k}+1)
$$

とおくと、計算量は次のとおりです。

- $O(S\log^2(N+M))$

## 参考

- [上限付き単調増加列の数え上げ](https://noshi91.hatenablog.com/entry/2023/07/21/235339)
- [上限付き単調増加列の数え上げを実装する](https://nononmath.hatenablog.com/entry/2024/06/11/193707)
