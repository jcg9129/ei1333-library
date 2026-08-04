---
title: Union Find
documentation_of: //structure/union-find/union-find.hpp
---

集合を高速に扱うためのデータ構造です。集合を合併する操作(unite)と、ある要素がどの集合に属しているか(find)を問い合わせる操作を行うことができます。

# コンストラクタ

```cpp
UnionFind(std::size_t n)
```

`n` 個の集合を作成します。集合 $i(0 \leq i \lt n)$ には要素 $i$ のみが属します。

## 制約

- $0 \leq n$

## 計算量

- $O(n)$

# unite

```cpp
bool unite(int x, int y)
```

集合 `x` と `y` を併合します。併合済のとき `false`、未併合のとき `true` を返します。

## 制約

- $0 \leq x, y \lt n$

## 計算量

- amortized $O(\alpha(n))$

# find

```cpp
int find(int k)
```

要素 `k` が属する集合の代表元を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- amortized $O(\alpha(n))$

# size

```cpp
int size(int k)
```

要素 `k` が属する集合の要素数を返します。

## 制約

- $0 \leq k \lt n$

## 計算量

- amortized $O(\alpha(n))$

# same

```cpp
bool same(int x, int y)
```

要素 `x` と `y` が同じ集合に属する場合 `true`、異なる集合に属する場合は `false` を返します。

## 制約

- $0 \leq x, y \lt n$

## 計算量

- amortized $O(\alpha(n))$

# groups

```cpp
std::vector<std::vector<int>> groups()
```

それぞれの集合に含まれる要素を列挙し、それを返します。それぞれの集合内の要素は昇順に格納されますが、集合の順番は未定義です。

## 計算量

- $O(n)$
