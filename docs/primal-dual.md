---
title: Primal Dual (最小費用流)
documentation_of: //graph/flow/primal-dual.hpp
---

最小費用流を最短路反復で解くアルゴリズム。始点から終点までの重みの最短路を求め、そこに流せる限り流す。これを流したい分だけ流しきるまで繰り返す。最短路の計算は、ポテンシャル $h$ を用いて負辺がないように変換して Dijkstra法 で求める。

# コンストラクタ

```cpp
PrimalDual(int V)
```

頂点数 $v$ で初期化する。

# add_edge

```cpp
void add_edge(int from, int to, flow_t cap, cost_t cost)
```

頂点 `from` から `to` に容量 `cap`、コスト `cost` の有向辺を張る。

# min_cost_flow

```cpp
cost_t min_cost_flow(int s, int t, flow_t f)
```

頂点 `s` から `t` に流量 `f` の最小費用流を流し、そのコストを返す。流せないとき $-1$ を返す。

## 計算量

- $O(FE \log V)$

$F$: 流量、$V$: 頂点数、$E$: 辺の本数

# output

```cpp
void output()
```

最小費用流を復元して出力する。
