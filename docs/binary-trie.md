---
title: Binary Trie
documentation_of: //structure/trie/binary-trie.hpp
---

整数をビット列とみなして、トライ木のように持つデータ構造。

# コンストラクタ

```cpp
(1) BinaryTrie()
(2) explicit BinaryTrie(Node *root)
```

1. 空のトライ木を構築します。
2. 根を `root` とするトライ木を構築します。

## 計算量

- $O(1)$

# add

```cpp
void add(const T& bit, int idx = -1, D delta = 1, T xor_val = 0)
```

トライ木の値 `bit` に `delta` を加える。`exist` には自分を含む部分木に追加された値の `delta` の総和、`idx` に対して $-1$ 以外を与えると `accept` にそのノードにマッチする全ての値のindexが格納される。

## 計算量

- $O(\log V)$

# erase

```cpp
void erase(const T& bit, T xor_val = 0)
```

値 `bit` に対応する `delta` に $-1$ を加える。

## 計算量

- $O(\log V)$

# find

```cpp
Node* find(const T& bit, T xor_val = 0)
```

値 `bit` に対応するノードを返す。存在しないとき `nullptr`。

## 計算量

- $O(\log V)$

# count

```cpp
D count(const T& bit, T xor_val = 0)
```

値 `bit` に対応するノードの `delta` を返す。存在しないとき $0$。

## 計算量

- $O(\log V)$

# min_element

```cpp
pair<T, Node*> min_element(T xor_val = 0)
```

最小値とそれに対応するノードを返す。

## 計算量

- $O(\log V)$

# max_element

```cpp
pair<T, Node*> max_element(T xor_val = 0)
```

最大値とそれに対応するノードを返す。

## 計算量

- $O(\log V)$

# kth_element

```cpp
pair<T, Node*> kth_element(D k, T xor_val = 0)
```

$k$ 番目(0-indexed) に小さい値とそれに対応するノードを返す。

## 計算量

- $O(\log V)$

# count_less

```cpp
D count_less(const T& bit, T xor_val = 0)
```

値 `bit` 未満の `delta` の総和を返す。

引数の最後の `xor_val` を指定すると、トライ木に存在する値全体に `xor_val` を xor とした場合の動作をする。

## 計算量

- $O(\log V)$
