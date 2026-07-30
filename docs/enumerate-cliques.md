---
title: Enumerate Cliques (クリーク全列挙)
documentation_of: //graph/others/enumerate-cliques.hpp
---

無向グラフが与えられたとき、クリークを全列挙する。

次数が $\sqrt {2E}$ 未満の頂点 $v$ を $1$ 個選んで、頂点 $v$ に隣接する頂点の部分集合を全て試し、$v$ を除去して再帰的に求める。

クリークの個数は高々 $2 ^ {\sqrt {2E}}$ 個。

# enumerate_cliques

```cpp
vector<vector<int>> enumerate_cliques(Matrix &g)
```

隣接行列 `g` の部分グラフに含まれる全てのクリークを返す。頂点数 $1$ もクリークとしてみなしている。

## 計算量

$O(2 ^ {\sqrt {2E}} V)$
