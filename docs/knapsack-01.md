---
title: Knapsack 01 (0-1ナップサック問題) $O(NW)$
documentation_of: //dp/knapsack-01.hpp
---

0-1 ナップサック問題を次に示す。

重さ $w_i$、価値 $v_i$ であるような $N$ 個の品物がある。重さの和が $W$ 以下となるように選ぶとき、価値の最大値を求めよ。

# knapsack_01

```cpp
vector<T> knapsack_01(const vector<int>& w, const vector<T>& v, const int& W, const T& NG, const Compare& comp = Compare())
```

`W` 以下の範囲で、各重さについて価値の最大値を求める。`NG` は到達ができない場合の値で、`comp` は比較演算子。

## 計算量

- $O(NW)$
