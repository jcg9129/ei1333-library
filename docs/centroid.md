---
title: Centroid (木の重心)
documentation_of: //graph/tree/centroid.hpp
---

木の重心を求める。その頂点を取り除いたときにできる部分木たちの頂点数がすべて半分以下になる頂点を木の重心と呼び、重心は $1$ 個か $2$ 個存在する。

# centroid

```cpp
vector<int> centroid(const Graph<T>& g)
```

木 `g` の重心となる頂点をすべて返す。

## 計算量

- $O(V)$
