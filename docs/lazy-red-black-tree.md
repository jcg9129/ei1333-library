---
title: Lazy Red Black Tree (遅延伝搬赤黒木)
documentation_of: //structure/bbst/lazy-red-black-tree.hpp
---

Lazy-Red-Black-Tree は Red-Black-Tree に遅延伝搬を実装したものである。

# コンストラクタ

```cpp
LazyRedBlackTree(int sz, const F& f, const G& g, const H& h, const Monoid& M1, const OperatorMonoid& OM0)
```

サイズ `n` で初期化する。ここで `f` は2つの区間の要素をマージする二項演算、`g` は要素と作用素をマージする二項演算、`h` は作用素同士をマージする二項演算、`M1` はモノイドの単位元、`OM0` は作用素の単位元である。

# split

```cpp
pair<Node*, Node*> split(Node* t, int k)
```

木 `t` を $[0, k)[k, n)$ で分割する。

## 計算量

- $O(\log n)$

# split3

```cpp
tuple<Node*, Node*, Node*> split3(Node* t, int a, int b)
```

木 `t` を $[0, a)[a, b)[b, n)$ で分割する。

## 計算量

- $O(\log n)$

# merge

```cpp
Node* merge(Node* l, Args... rest)
```

木 `l` と木 `r` を併合する。

## 計算量

- $O(\log n)$

# build

```cpp
Node* build(const vector<Monoid>& v)
```

配列 `v` をもとに木を構築する。

## 計算量

- $O(n)$

# dump

```cpp
vector<Monoid> dump(Node* r)
```

木 `r` の葉を通りがけ順に格納したものを返す。

## 計算量

- $O(n)$

# to_string

```cpp
string to_string(Node* r)
```

`dump(r)` をスペース区切りで文字列として連結したものを返す。

## 計算量

- $O(n)$

# insert

```cpp
void insert(Node*& t, int k, const Monoid& v)
```

木 `t` の位置 `k` (0-indexed) にノード `v` を挿入する。

## 計算量

- $O(\log n)$

# erase

```cpp
Monoid erase(Node*& t, int k)
```

木 `t` の位置 `k` (0-indexed) のノードを削除する。

## 計算量

- $O(\log n)$

# query

```cpp
Monoid query(Node*& t, int a, int b)
```

区間 $[l, r)$ の要素を二項演算した結果を返す。

## 計算量

- $O(\log n)$

# set_element

```cpp
void set_element(Node*& t, int k, const Monoid& x)
```

木 `t` の位置 `k` (0-indexed) のノードを `x` に変更する。

## 計算量

- $O(\log n)$

# set_propagate

```cpp
void set_propagate(Node*& t, int a, int b, const OperatorMonoid& pp)
```

木 `t` の区間 $[a, b)$ の要素に作用素 `pp` を適用する。

## 計算量

- $O(\log n)$

# push_front

```cpp
void push_front(Node*& t, const Monoid& v)
```

木 `t` の先頭にノード `v` を挿入する。

## 計算量

- $O(\log n)$

# push_back

```cpp
void push_back(Node*& t, const Monoid& v)
```

木 `t` の末尾にノード `v` を挿入する。

## 計算量

- $O(\log n)$

# pop_front

```cpp
Monoid pop_front(Node*& t)
```

木 `t` の先頭要素を削除する。

## 計算量

- $O(\log n)$

# pop_back

```cpp
Monoid pop_back(Node*& t)
```

木 `t` の末尾要素を削除する。

## 計算量

- $O(\log n)$
