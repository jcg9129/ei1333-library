---
title: Knapsack (個数制限なしナップサック問題)
documentation_of: //dp/knapsack.hpp
---

個数制限なしナップサック問題を次に示す。

重さ $w_i$、価値 $v_i$ であるような $N$ 種類の品物がある。重さの和が $W$ 以下となるように選ぶとき、価値の最大値を求めよ。

# knapsack

```cpp
vector<T> knapsack(const vector<int>& w, const vector<T>& v, const int& W, const T& NG, const Compare& comp = Compare())
```

`W` 以下の範囲で、各重さについて価値の最大値を求める。`NG` は到達ができない場合の値で、`comp` は比較演算子。

## 計算量

- $O(NW)$
