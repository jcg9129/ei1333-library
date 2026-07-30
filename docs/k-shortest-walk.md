---
title: K Shortest Walk
documentation_of: //graph/shortest-path/k-shortest-walk.hpp
---

頂点 $s$ から $t$ へのウォーク(Walk) のうち、昇順 $k$ 個のウォークの長さを Eppstein's Algorithm により求める。

ウォーク(Walk、歩道、経路) とは重複して頂点や辺が現れることを許容した頂点 $s$ から $t$ への経路を指す。

ちなみにトレイル(Trail) は同じ辺を通らない経路、道(Path) は同じ頂点を通らない経路である。

# k_shortest_walk

```cpp
vector<T> k_shortest_walk(const Graph<T>& g, int s, int t, int k)
```

重み付き有向グラフ `g` の頂点 `s` から `t` へのウォークのうち、昇順 `k` 個のウォークの長さを返す(ウォークの個数が `k` 個に満たないとき全てを返す)。

## 計算量

- $O((V + E) \log V + K \log K)$
