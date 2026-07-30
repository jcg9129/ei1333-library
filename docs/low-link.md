---
title: Low Link (橋/関節点)
documentation_of: //graph/others/low-link.hpp
---

橋や関節点などを効率的に求める際に有効なアルゴリズム。

グラフをDFSして各頂点 `idx` について、`ord[idx]` := DFS で頂点に訪れた順番、`low[idx]` := 頂点 $idx$ からDFS木の葉方向の辺を $0$ 回以上、後退辺を $1$ 回以下通って到達可能な頂点の `ord` の最小値 を求める。

ある頂点 $u$ が関節点であるとき、DFS木の根については子が $2$ つ以上、それ以外の頂点については 頂点 $u$ のある子 $v$ について `ord[u]` $\le$ `low[v]` を満たす。

ある辺 $(u, v)$ が橋であるとき、`ord[u]` $\lt$ `low[v]` を満たす。

# コンストラクタ

```cpp
explicit LowLink(const Graph<T> &g)
```

グラフ `g` で初期化します。

## 計算量

- $O(V + E)$

# build

```cpp
virtual void build()
```

LowLink を構築する。構築後、`articulation` には関節点、`bridge` には橋が格納される。非連結でも多重辺を含んでいてもOK。

## 計算量

$O(V + E)$
