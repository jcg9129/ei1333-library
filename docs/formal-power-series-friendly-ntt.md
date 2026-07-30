---
title: Formal Power Series Friendly NTT (NTTmod用形式的冪級数)
documentation_of: //math/fps/formal-power-series-friendly-ntt.hpp
---

NTT を利用可能な mod のもとで、形式的べき級数の各演算を効率的に行う。

TODO 解説

通常はテンプレートの型として Modint 構造体を渡す。また static な関数として `ntt` と `intt` が実装された構造体が必要である。この構造体は `NumberTheoreticTransformFriendlyModInt< T >` に対応しているが、他のライブラリを使いたい場合は必要に応じてこの部分を書き換えること。

計算量が書かれていない演算は $O(n \log n)$ で動作する。引数で `deg` を渡すことで、`deg` 項まで計算して返すものもある(デフォルトでは基本的に $\mathrm{deg}(f)$ 項で打ち切る)。

# +

```cpp
P operator+(const P &r) const
```

$f(x) + g(x)$ を返す。

## 計算量

- $O(n)$

# -

```cpp
P operator-(const P &r) const
```

$f(x) - g(x)$ を返す。

## 計算量

- $O(n)$

# *

```cpp
P operator*(const P &r) const
```

$f(x) \times g(x)$ を返す。

## 計算量

- $O(n \log n)$

# /

```cpp
P operator/(const P &r) const
```

$f(x) = q(x) \times g(x) + r(x)$ かつ $\mathrm{deg}(r) \lt \mathrm{deg}(g)$ を満たす $q(x)$ を返す。

## 計算量

- $O(n \log n)$

# %

```cpp
P operator%(const P &r) const
```

$f(x) = q(x) \times g(x) + r(x)$ かつ $\mathrm{deg}(r) \lt \mathrm{deg}(g)$ を満たす $r(x)$ を返す。

## 計算量

- $O(n \log n)$

# div_mod

```cpp
pair<P, P> div_mod(const P &r)
```

剰余を返す。`/` と `%` をそれぞれ呼び出すよりも効率的。

## 計算量

- $O(n \log n)$

# operator()

```cpp
T operator()(T x) const
```

$f(x)$ の値を評価して返す。

## 計算量

- $O(n)$

# diff

```cpp
P diff() const
```

$f(x)'$ を返す。

## 計算量

- $O(n)$

# integral

```cpp
P integral() const
```

$\int f(x) dx$ を返す。

## 計算量

- $O(n)$

# inv

```cpp
P inv(int deg = -1) const
```

$\frac {1} {f(x)}$ を返す。$f(0) \neq 0$ を要求する。

## 計算量

- $O(n \log n)$

# log

```cpp
P log(int deg = -1) const
```

$\log f(x)$ を返す。$f(0) = 1$ を要求する。

## 計算量

- $O(n \log n)$

# sqrt

```cpp
P sqrt(const function<T(T)> &get_sqrt, int deg = -1) const
```

$\sqrt {f(x)}$、つまり $f(x) = g(x)^2$ を満たす $g(x)$ を返す。存在しない場合空配列を返す。`get_sqrt` はあるmodint $y$ が与えられたときに $y = x^2$ を満たす modint $x$ を返すラムダ式で、これを渡さない場合は非 $0$ な最初の項が $1$ であることを要求する。存在しない場合は適当な値を返すように実装すると、空配列が返される。

## 計算量

- $O(n \log n)$

# exp

```cpp
P exp(int deg = -1) const
```

$e^{f} (x)$ を返す。$f(0) = 0$ を要求する。

## 計算量

- $O(n \log n)$

# pow

```cpp
P pow(int64_t k, int deg = -1) const
```

$f^{k} (x)$ を返す。

## 計算量

- $O(n \log n)$

# mod_pow

```cpp
P mod_pow(int64_t k, P g) const
```

$f^{k} (x) \pmod {g(x)}$ を返す。

## 計算量

- $O(n \log k \log \mathrm{deg}(f))$

# taylor_shift

```cpp
P taylor_shift(T c) const
```

$g(x) = f(x + c)$ を満たす $g(x)$ を返す。

## 計算量

- $O(n \log n)$
