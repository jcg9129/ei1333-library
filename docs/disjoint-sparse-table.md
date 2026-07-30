---
title: Disjoint Sparse Table
documentation_of: //structure/others/disjoint-sparse-table.hpp
---

更新がない場合の半群に対する区間クエリを、前計算 $O(n \log n)$、クエリ $O(1)$ で処理する。

# コンストラクタ

```cpp
DisjointSparseTable(const vector<Semigroup>& v, const F& f)
```

配列 `v` で初期化する。`f` は半群をマージする二項演算である。

## 計算量

- $O(N \log N)$

# fold

```cpp
Semigroup fold(int l, int r)
```

区間 $[l, r)$ を演算した結果を返す。

## 計算量

- $O(1)$
