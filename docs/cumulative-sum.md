---
title: Cumulative Sum (一次元累積和)
documentation_of: //dp/cumulative-sum.hpp
---

$1$ 次元の累積和です。事前に累積和を構築することで、区間和を $O(1)$ で求められます。

# コンストラクタ

```cpp
(1) CumulativeSum()
(2) explicit CumulativeSum(size_t sz)
```

1. 空の数列で初期化します。
2. 長さ `sz` の数列で初期化します。各要素は $0$ です。

## 計算量

- (1) $O(1)$
- (2) $O(N)$

# add

```cpp
void add(int k, const T& x)
```

要素 `k` に値 `x` を加えます。

## 制約

- $0 \leq k \lt N$
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

- $O(N)$

# fold

```cpp
T fold(int r) const
```

区間 $[0, r)$ の和を返します。

## 制約

- $0 \leq r \leq N$
- `build` を呼び出した後

## 計算量

- $O(1)$

# fold

```cpp
T fold(int l, int r) const
```

区間 $[l, r)$ の和を返します。

## 制約

- $0 \leq l \leq r \leq N$
- `build` を呼び出した後

## 計算量

- $O(1)$
