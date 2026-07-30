---
title: Z Algorithm
documentation_of: //string/z-algorithm.hpp
---

文字列 $S$ が与えられたとき、それぞれの $i$ について $S$ と $S[i, \|S\|]$ の最長共通接頭辞の長さを記録した配列を線形時間で構築する。

具体例を以下に示す。例えば $i = 5$ のときの最長共通接頭辞は "aaa"、つまり $3$ 文字である。

<pre>
aaabaaaab
921034210
</pre>

# コンストラクタ

```cpp
ZAlgorithm()
```

空文字列で初期化する。

# コンストラクタ

```cpp
ZAlgorithm(const S& s)
```

文字列 `s` で初期化する。

## 計算量

- $O(\|S\|)$

# add

```cpp
void add(const T& c)
```

文字列の末尾に `c` を追加する。

## 計算量

- 全体で $O(\|S\|)$

# get

```cpp
int get(int k) const
```

現時点の文字列の $S$ と $S[i, \|S\|]$ の最長共通接頭辞の長さを返す。

## 計算量

- $O(1)$

# operator[]

```cpp
int operator[](int k) const
```

`get(k)` と同じ値を返す。

## 計算量

- $O(1)$

# get

```cpp
vector<int> get()
```

現時点の文字列の $S$ とすべての $i$ についての$S[i, \|S\|]$ の最長共通接頭辞の長さを返す。

## 計算量

- $O(\|S\|)$
