---
title: Doubling Lowest Common Ancestor (最小共通祖先)
documentation_of: //graph/tree/doubling-lowest-common-ancestor.hpp
---

ダブリングによって最小共通祖先を求める。

頂点 $u$、$v$ の最小共通祖先を求めたいとする。$dep[i]$ をある頂点を根とする根付き木としてみたときの深さとし、$dep[u] \leq dep[v]$ を仮定する。まず $dep[v] - dep[u]$ 個だけ頂点 $v$ を親に遡らせて、頂点 $u, v$ の深さを揃える。このとき深さが一致したらそれが最小共通祖先。それ以外のとき、上位 bit から頂点 $u, v$ 双方の $2^k$ 個先の親を見て、異なれば遡ることを繰り返し、双方の親ではない直前の頂点を求める。するとその親が最小共通祖先であることがわかる。

# コンストラクタ

```cpp
(1) explicit DoublingLowestCommonAncestor(int n)
(2) explicit DoublingLowestCommonAncestor(const Graph<T> &g)
```

1. 頂点数 `n` の木で初期化します。
2. 木 `g` で初期化します。

## 計算量

- (1) $O(n)$
- (2) $O(V + E)$

# build

```cpp
void build(int root = 0)
```

構築する。

## 計算量

- $O(V)$

# lca

```cpp
int lca(int u, int v)
```

頂点 `u`、`v` の最小共通祖先(LCA)を返す。

## 計算量

- $O(\log V)$

# climb

```cpp
int climb(int u, int k)
```

頂点 `u` から `k` 個親に遡った頂点を返す。

## 計算量

- $O(\log V)$

# dist

```cpp
T dist(int u, int v)
```

頂点 `u`、`v` 間のパスの辺の本数を返す。

## 計算量

- $O(\log V)$
