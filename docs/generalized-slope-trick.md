---
title: Generalized Slope Trick
documentation_of: //structure/others/generalized-slope-trick.hpp
---

区分線形凸関数 $f(x)$ を効率的に扱うためのデータ構造。

$f(x)$ の傾きが変化する点を平衡二分探索木に持つことで、特定の操作を簡潔に行うことが可能となる。傾きを $1$ ずつ変化する場合は優先度付きキューを用いていたが、平衡二分探索木を用いることで一般の傾きの操作ができるようになる(未実装)。

平衡二分探索木には Splay Tree を用いている。

主にDPの高速化に用いられることが多い。

# コンストラクタ

```cpp
GeneralizedSlopeTrick()
```

$f(x)=0$ で初期化します。

## 計算量

- $O(1)$

# query

```cpp
Query query()
```

$f(x)$ の最小値とそれを満たす $x$ の最小値および最大値を返す。

## 計算量

- $O(1)$

# add_all

```cpp
void add_all(const T& a)
```

$f(x)$ に $a$ を加算する。

## 計算量

- $O(1)$

# add_a_minus_x

```cpp
void add_a_minus_x(const T& a)
```

$f(x)$ に $\max(a - x, 0)$ を加算する。

## 計算量

- $O(\log Q)$

# add_x_minus_a

```cpp
void add_x_minus_a(const T& a)
```

$f(x)$ に $\max(x - a, 0)$ を加算する。

## 計算量

- $O(\log Q)$

# add_abs

```cpp
void add_abs(const T& a)
```

$f(x)$ に$abs(x-a)$ を加算する。

## 計算量

- $O(\log Q)$

# clear_right

```cpp
void clear_right()
```

$f(x) = \min_{y \le x} f(y)$ に置き換える。

## 計算量

- $O(1)$

# clear_left

```cpp
void clear_left()
```

$f(x) = \min_{y \ge x} f(y)$ に置き換える。

## 計算量

- $O(1)$

# shift

```cpp
void shift(const T& a, const T& b)
```

$f(x) = \min_{x-b \le y \le x-a} f(y)$ に置き換える。$a \leq b$ を満たす必要がある。

## 計算量

- $O(1)$

# shift

```cpp
void shift(const T& a)
```

$f(x) = f(x - a)$ に置き換える。

## 計算量

- $O(1)$

# get

```cpp
T get(const T& x)
```

$f(x)$ を返す。ただし $f$ を破壊する。

## 計算量

- $O(\log Q)$

# merge

```cpp
void merge(GeneralizedSlopeTrick &g)
```

$f(x)$ に $g(x)$ を加算する。ただし $g$ を破壊する。

## 計算量

- $f, g$ の大きさをそれぞれ $N, M$ として $O(\min(N, M) \log \max(N, M))$
