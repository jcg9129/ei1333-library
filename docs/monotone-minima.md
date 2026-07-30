---
title: Monotone Minima
documentation_of: //dp/monotone-minima.hpp
---

$2$ 変数関数 $f(i, j) (0 \leq i \lt H, 0 \leq j \lt W)$ が Monotone であるとは、すべての $k$ に対して $\mathrm{argmin} f(k, *) \leq \mathrm{argmin} f(k + 1, *)$ を満たすことをいう。つまり各行の最小値をとる位置が右下に単調に下がっていることを意味する。

Monge $\Rightarrow$ Totally Monotone(TM) $\Rightarrow$ Monotone なので、Monotone は弱い条件である。

# monotone_minima

```cpp
vector<pair<int, T> > monotone_minima(int H, int W, const function<T(int, int)>& f, const Compare& comp = Compare())
```

各行について、最小値をとる位置と最小値をペアで返す。`f` は $2$ 変数関数、`comp` は比較関数。

## 計算量

- $O(N \log N)$
