---
title: Tree Diameter (木の直径)
documentation_of: //graph/tree/tree-diameter.hpp
---

木の直径を求める。

適当な頂点から DFS して最も遠い点 $u$ を求める、$u$ から DFS して最も遠い点 $v$ を見つけると、そのペア $(u, v)$ が直径の端点。

# コンストラクタ

```cpp
explicit TreeDiameter(const Graph<T> &g)
```

木 `g` で初期化します。

## 計算量

- $O(V + E)$

# build

```cpp
T build()
```

木の直径を返す。`path` には直径を構成する辺が格納される。

## 計算量

$O(V)$
