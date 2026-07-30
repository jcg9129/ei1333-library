---
title: Gabow Edmonds (一般グラフの最大マッチング)
documentation_of: //graph/flow/gabow-edmonds.hpp
---

一般グラフの最大マッチングを、GabowのEdmonds' Algorithmによって求める。

グラフ $G=(V, E)$ において、$M$ が $E$ の部分集合でかつ $M$ のどの $2$ 辺も共通の端点をもたないとき、$M$ を $G$ のマッチングといい、辺の本数が最大であるマッチングを最大マッチングという。

# コンストラクタ

```cpp
GabowEdmonds(int n)
```

頂点数 `n` で初期化する

# add_edge

```cpp
void add_edge(int u, int v)
```

頂点 `u`、`v` 間に無向辺を張る

# max_matching

```cpp
vector<pair<int, int> > max_matching()
```

最大マッチングを求め、その辺集合を返す。

## 計算量

- $O(VE \log V)$
