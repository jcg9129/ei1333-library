---
title: Topological Sort (トポロジカルソート)
documentation_of: //graph/others/topological-sort.hpp
---

DAG(閉路のない有向グラフ) が与えられたとき、トポロジカルソートする。

入次数 $0$ の頂点から消すことを繰り返す。

# topological_sort

```cpp
vector<int> topological_sort(const Graph<T>& g)
```

DAG `g` をトポロジカルソートして、その頂点の順序を返す。

## 計算量

$O(E + V)$
