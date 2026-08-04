---
title: Sparse Table (スパーステーブル)
documentation_of: //structure/others/sparse-table.hpp
---

冪等半群に対する区間クエリを、前計算 $\Theta (n \log n)$、クエリ $\Theta (1)$ で処理する。

# コンストラクタ

```cpp
explicit SparseTable(const std::vector<T>& v, const F& f)
```

配列 `v`、演算 $f$ で初期化する。

## 計算量

- $\Theta(N \log N)$

# fold

```cpp
inline T fold(int l, int r) const
```

区間 $[l, r)$ の演算結果を返す。

## 計算量

- $\Theta(1)$
