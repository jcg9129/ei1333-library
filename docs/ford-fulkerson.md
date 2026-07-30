---
title: Ford Fulkerson (最大流)
documentation_of: //graph/flow/ford-fulkerson.hpp
---

最大流を求めるアルゴリズム。

DFS により増加パスがとれなくなるまでフローを流すことを繰り返し、流せなくなったら終了する。

# コンストラクタ

```cpp
explicit FordFulkerson(int V)
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

$O(FE)$

$F$ は最大流
