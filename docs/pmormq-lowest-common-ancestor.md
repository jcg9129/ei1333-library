---
title: PMORMQ Lowest Common Ancestor (最小共通祖先)
documentation_of: //graph/tree/pmormq-lowest-common-ancestor.hpp
---

オイラーツアーと±1RMQ によって最小共通祖先を求める。

辺属性のオイラーツアーをする。すべての頂点について、その頂点 $k$ に最初に到達した時刻 $in[k]$ と深さ $dep[k]$ を求めておく。頂点 $u, v$ の最小共通祖先は区間 $[in[u], in[v]]$ の要素のうち深さが最小となる頂点である。

スパーステーブルを用いると前計算 $O(V \log V)$、クエリ $O(1)$ となるが、$dep[k]$ 隣接する要素の差がちょうど $1$ であることを利用した ±1RMQ を用いると前計算 $O(V)$、クエリ $O(1)$ となる。

# コンストラクタ

```cpp
explicit PMORMQLowestCommonAncestor(int n)
```

頂点数 `n` の木で初期化します。

## 計算量

- $O(n)$

# build

```cpp
void build(int root = 0)
```

構築する。

## 計算量

- $O(V)$

# lca

```cpp
int lca(int x, int y) const
```

頂点 `u`、`v` の最小共通祖先(LCA)を返す。

## 計算量

- $O(1)$
