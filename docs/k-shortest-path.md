---
title: K Shortest Path
documentation_of: //graph/shortest-path/k-shortest-path.hpp
---

頂点 $s$ から $t$ へのパス(Path) のうち、昇順 $k$ 個のパスの長さを Yen's Algorithm により求める。

パス(Path、道) は同じ頂点を通らない経路である。

verify が甘いため合っているかかなり不安です

# k_shortest_path

```cpp
vector<pair<T, vector<int> > > k_shortest_path(const Graph<T>& g, int s, int t, int k)
```

重み付き有向グラフ `g` の頂点 `s` から `t` へのパスのうち、昇順 `k` 個のパスの長さとそのパスの辺番号の列を返す(パスの個数が `k` 個に満たないとき全てを返す)。

## 計算量

- $O(KV(E + V) \log V)$
