---
title: Cumulative Sum 2D (二次元累積和)
documentation_of: //dp/cumulative-sum-2d.hpp
---

$2$ 次元の累積和です。事前に累積和を構築することで、矩形和を $O(1)$ で求められます。

# コンストラクタ

```cpp
CumulativeSum2D(int W, int H)
```

幅 `W`、高さ `H` の二次元配列で初期化します。各要素は $0$ です。

## 制約

- $0 \leq W$
- $0 \leq H$

## 計算量

- $O(WH)$

# add

```cpp
void add(int x, int y, T z)
```

要素 $(x, y)$ に値 `z` を加えます。

## 制約

- $0 \leq x \lt W$
- $0 \leq y \lt H$
- `build` より前に呼び出す

## 計算量

- $O(1)$

# build

```cpp
void build()
```

累積和を構築します。

## 制約

- `add` をすべて処理した後に1回だけ呼び出す

## 計算量

- $O(WH)$

# query

```cpp
T query(int sx, int sy, int gx, int gy) const
```

半開矩形 $[sx, gx) \times [sy, gy)$ の要素の総和を返します。

## 制約

- $0 \leq sx \leq gx \leq W$
- $0 \leq sy \leq gy \leq H$
- `build` を呼び出した後

## 計算量

- $O(1)$
