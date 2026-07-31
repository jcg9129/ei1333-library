---
title: Partially Retroactive Priority Queue
documentation_of: //structure/heap/partially-retroactive-priority-queue.hpp
---

長さ $N$ の操作列を持つ優先度付きキューです。各時刻の操作を過去にさかのぼって `push`、`pop`、何もしない操作のいずれかへ変更し、操作列を空の優先度付きキューへ適用したあとの状態を管理します。

空の優先度付きキューに対する `pop` は無視されます。`Compare` のデフォルトは `std::less<T>` で、最小値が先に取り除かれます。

`Compare` によって同順位となる要素が複数ある場合は、より早い時刻に `push` された要素が先に取り除かれます。

各 `push` を最終状態に残る要素と途中で取り除かれる要素に分類し、操作列の接頭辞和が $0$ となる境界と、境界の前後で入れ替わる候補をセグメント木で管理します。空のキューに対する `pop` は、操作列の先頭に、すべての実要素より優先度が低い仮想要素を $N$ 個追加することで通常の `pop` と同様に扱います。

# コンストラクタ

```cpp
PartiallyRetroactivePriorityQueue<T, Compare>(int n, Compare compare = Compare())
```

長さ `n` の操作列を、すべて何もしない操作として初期化します。

## 制約

- $0 \leq n$
- `Compare` は狭義弱順序を定める
- `T{}` は加法単位元を表す
- `T` は `+=`、`-=`、コピー構築、ムーブ構築が可能

## 計算量

- 時間 $O(n)$
- 空間 $O(n)$

# set_push

```cpp
void set_push(int t, T value)
```

時刻 `t` の操作を `value` の `push` に変更します。以前の操作は上書きされます。

## 制約

- $0 \leq t < n$

## 計算量

- $O(\log n)$

# set_pop

```cpp
void set_pop(int t)
```

時刻 `t` の操作を優先要素の `pop` に変更します。以前の操作は上書きされます。その時点でキューが空なら何も行いません。

## 制約

- $0 \leq t < n$

## 計算量

- $O(\log n)$

# set_noop

```cpp
void set_noop(int t)
```

時刻 `t` の操作を何もしない操作に変更します。以前の操作は上書きされます。

## 制約

- $0 \leq t < n$

## 計算量

- $O(\log n)$

# empty

```cpp
bool empty() const
```

すべての操作を適用したあとの優先度付きキューが空かを返します。

## 計算量

- $O(1)$

# size

```cpp
int size() const
```

すべての操作を適用したあとに残る要素数を返します。

## 計算量

- $O(1)$

# top

```cpp
const T& top() const
```

すべての操作を適用したあとに残る優先要素を返します。

## 制約

- `empty()` が `false`

## 計算量

- $O(1)$

# sum

```cpp
T sum() const
```

すべての操作を適用したあとに残る全要素の総和を返します。

## 計算量

- $O(1)$
