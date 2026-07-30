---
title: Dinic Capacity Scaling (最大流)
documentation_of: //graph/flow/dinic-capacity-scaling.hpp
---

最大流を求めるアルゴリズム。

すべての辺の容量が整数の場合、スケーリングを用いて Dinic の計算量を $O(EV \log U)$ に落とすことが出来る($U$ は辺の容量の最大値)。

具体的には、フローを残余グラフ上で $k$ が大きい方から $2^k$ 単位で流すようにする。

# コンストラクタ

```cpp
explicit DinicCapacityScaling(int V)
```

頂点数 `V` で初期化する。

# add_edge

```cpp
void add_edge(int from, int to, flow_t cap, int idx = -1)
```

頂点 `from` から `to` に容量 `cap` の辺を追加する。

# max_flow

```cpp
flow_t max_flow(int s, int t)
```

頂点 `s` から `t` に最大流を流し、その流量を返す。

## 計算量

$O(EV \log U)$

$U$ は辺の容量の最大値
