---
title: Bipartite Matching (二部グラフの最大マッチング)
documentation_of: //graph/flow/bipartite-matching.hpp
---

グラフ $G=(V, E)$ において、$V$ が $2$ つの部分集合 $X$ と $Y$ に分割され、$E$ のどの辺も一方の端点は $X$ に、もう一方の端点は $Y$ に属しているとき、$G$ を二部グラフという。

グラフ $G=(V, E)$ において、$M$ が $E$ の部分集合でかつ $M$ のどの $2$ 辺も共通の端点をもたないとき、$M$ を $G$ のマッチングといい、辺の本数が最大であるマッチングを最大マッチングという。

ここでは、二部グラフの最大マッチングを最大流のアルゴリズムを利用して求める。

# コンストラクタ

```cpp
explicit BipartiteMatching(int n)
```

全体のグラフの頂点数を `n` で初期化する。

# add_edge

```cpp
void add_edge(int u, int v)
```

頂点 `u`、`v` 間に辺を張る。

# bipartite_matching

```cpp
int bipartite_matching()
```

二部グラフの最大マッチングを返す。

## 計算量

- $O(V E)$

# add_vertex

```cpp
int add_vertex(int idx)
```

頂点 `idx` を追加し、フローの変化量を返す($0$ または $1$)。

# erase_vertex

```cpp
int erase_vertex(int idx)
```

頂点 `idx` を削除し、フローの変化量を返す($0$ または $-1$)。

# output

```cpp
void output() const
```

マッチングに使った辺を出力する。
