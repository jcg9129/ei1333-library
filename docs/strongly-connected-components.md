---
title: Strongly Connected Components (強連結成分分解)
documentation_of: //graph/connected-components/strongly-connected-components.hpp
---

与えられた有向グラフを強連結成分分解する。

グラフの任意の $2$ 頂点間に有向路が存在するとき、有向グラフが強連結であるとよぶ。強連結成分は、極大で強連結な部分グラフである。

適当な頂点から DFS をして、帰りがけ順に頂点を列挙することを、未訪問の頂点がある間繰り返す。次に辺をすべて逆向きにしたグラフについて、列挙した頂点の逆順に DFS する。$1$ 回の DFS で到達できた頂点が $1$ つの強連結成分となる。DFS は明示的なスタックを用いて非再帰で実行するため、グラフが深い場合もコールスタックを消費しない。

強連結成分を縮約後の頂点とそれらを結ぶ辺からなるグラフは DAG になっている。

# コンストラクタ

```cpp
explicit StronglyConnectedComponents(int n)
```

頂点数 `n` のグラフで初期化します。

## 計算量

- $O(n)$

# build

```cpp
void build()
```

強連結成分分解する。`dag` には縮約後の頂点と辺からなる DAG が格納される。`comp` には各頂点が属する強連結成分の頂点番号がトポロジカル順で格納される。`group` には各強連結成分について、それに属する頂点が格納される。辺を追加した後に再度呼び出すこともできる。

## 計算量

- $O(E + V)$
- 空間計算量: $O(E + V)$

# operator[]

```cpp
int operator[](int k) const
```

頂点 $k$ が属する強連結成分の番号を返す。

## 計算量

- $O(1)$
