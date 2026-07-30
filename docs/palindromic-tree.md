---
title: Palindromic Tree (回文木)
documentation_of: //string/palindromic-tree.hpp
---

文字列 $S$ が与えられる。Palindromic Tree は $S$ に含まれるすべての回文を頂点とした木である。

長さが $-1$ と $0$ の超頂点を用意する。各頂点からは、その頂点に対応する回文の両端に同じ文字を $1$ 文字加えてできる回文の頂点に辺を張ることで木を構成する。特に長さ $1$ の回文は $-1$ の超頂点から、長さ $2$ の回文は $0$ の超頂点から辺を張ることになる。

さらに Suffix Link として、頂点の回文に含まれる最大の回文接尾辞に対応する頂点に辺を張る。例えば eertree からは ee、reer からは r に Suffix Link が張られることになる。Suffix Link からなる木を Suffix Link Tree と呼ぶことにする。

Palindromic Tree は、長さ $-1$ の超頂点、長さ $0$ の超頂点を根とした木および Suffix Link Tree の $3$ つの木構造を同時に管理するデータ構造とみなせる。

文字列に含まれる全てのユニークな回文の個数は超頂点 $-1, 0$ を除いた頂点数、$i$ 番目の文字が最後尾となるような回文の個数は対応する頂点の Suffix Link Tree の深さと一致する。

# コンストラクタ

```cpp
(1) PalindromicTree()
(2) PalindromicTree(const string &S)
```

(1) 空の Palindromic Tree を構築する。

(2) 文字列 $S$ に対応する Palindromic Tree を構築する。

## 計算量

- (1) $O(1)$
- (2) $O(\|S\|)$

# add

```cpp
int add(const T &x)
```

末尾に文字 `x` を追加する。追加した文字を末尾とする最長回文接尾辞の頂点番号を返す。

# add

```cpp
void add(const string &s)
```

末尾に文字列 `s` を追加する。

# diff

```cpp
int diff(int t) const
```

頂点 $t$ が表す回文の長さと、その Suffix Link が指す回文の長さとの差を返す。

## 計算量

- $O(1)$

# update_dp

```cpp
template <typename I, typename U>
vector<int> update_dp(const I &init, const U &apply)
```

直前の `add` で追加した文字を末尾に持つ回文接尾辞を列挙し、`init` と `apply` を用いて系列 DP を更新する。

# build_frequency

```cpp
vector<int> build_frequency() const
```

各頂点に対応する回文の出現回数を返す。

# output

```cpp
vector<T> output(int idx) const
```

頂点 `idx` に対応する回文を返す。

# size

```cpp
int size() const
```

頂点数を返す。

# operator[]

```cpp
Node &operator[](int idx)
```

頂点 `idx` に対応するノードを返す。
