---
title: Directed MST (最小有向全域木)
documentation_of: //graph/mst/directed-mst.hpp
---

有向グラフが与えられたとき、ある頂点を根とする最小有向全域木を求める。頂点が指定されない場合は、超頂点を追加して各頂点に重み $0$ の辺を張れば同じ問題に帰着される。

基本的には、各頂点について、その頂点に入ってくる辺のうち最小の重みのものを選べば良い。このときに、サイクルが生えると困るので、賢いことをしている。

# directed_mst

```cpp
MinimumSpanningTree<T> directed_mst(int V, int root, Edges<T> edges)
```

`V` 頂点のグラフ `edges` の `root` を頂点とする最小有向全域木を返す。`cost` はそのときの辺のコストの和、`edges` は用いた辺集合が格納される。頂点 `root` から全ての頂点へ到達可能であることを仮定している。

## 計算量

- $O(E \log V)$

$V$: 頂点数、$E$: 辺の本数
