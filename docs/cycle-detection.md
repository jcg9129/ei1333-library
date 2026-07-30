---
title: Cycle Detection (閉路検出)
documentation_of: //graph/others/cycle-detection.hpp
---

有向グラフが与えられたとき、辺素なサイクルを $1$ つみつける。

適当な頂点から DFS すると見つけられる。

# コンストラクタ

```cpp
explicit CycleDetection(int n)
```

頂点数 `n` のグラフで初期化します。

## 計算量

- $O(n)$

# build

```cpp
Edges<T> build()
```

辺素なサイクルを $1$ つ見つけて返す。ただし、見つからなかったとき空列を返す。

## 計算量

$O(E + V)$
