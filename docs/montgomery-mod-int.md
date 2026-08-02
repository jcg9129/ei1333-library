---
title: Montgomery Mod Int
documentation_of: //math/combinatorics/montgomery-mod-int.hpp
---

Montgomery Reduction を用いて、コンパイル時に固定した mod 上の整数を扱います。

# MontgomeryModInt

```cpp
template <uint32_t mod, bool fast = false>
struct MontgomeryModInt
```

`mod` を法とする整数型です。値は内部で Montgomery 表現として保持されます。

`fast == false` の場合、整数からの構築時に値を $[0,\mathrm{mod})$ へ正規化します。`fast == true` の場合は剰余計算を省略するため、構築時に $0 \leq x < \mathrm{mod}$ を満たす整数だけを渡してください。

次の型エイリアスが定義されています。

```cpp
template <uint32_t mod>
using modint = MontgomeryModInt<mod>;

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;
```

## 制約

- $3 \leq \mathrm{mod} < 2^{30}$
- `mod` は奇数
- `inv` または除算を使用する場合、`mod` は素数

# コンストラクタ

```cpp
MontgomeryModInt()
MontgomeryModInt(const int64_t &x)
```

デフォルトコンストラクタは $0$ で初期化します。整数 `x` を渡した場合は、`fast == false` なら `x` が負の場合を含めて mod 上の値へ正規化します。

## 計算量

- $O(1)$

# 四則演算

```cpp
mint &operator+=(const mint &rhs)
mint &operator-=(const mint &rhs)
mint &operator*=(const mint &rhs)
mint &operator/=(const mint &rhs)

mint operator+(const mint &rhs) const
mint operator-(const mint &rhs) const
mint operator*(const mint &rhs) const
mint operator/(const mint &rhs) const
mint operator-() const
```

mod 上の加算、減算、乗算、除算、単項マイナスを行います。

## 制約

除算する場合は次を満たす必要があります。

- `rhs != 0`
- `mod` は素数

## 計算量

- 加算、減算、乗算、単項マイナス: $O(1)$
- 除算: $O(\log \mathrm{mod})$

# 比較演算

```cpp
bool operator==(const mint &rhs) const
bool operator!=(const mint &rhs) const
```

mod 上の値が等しいか比較します。

## 計算量

- $O(1)$

# val

```cpp
uint32_t val() const
```

保持する値を通常表現へ戻し、$[0,\mathrm{mod})$ の整数として返します。

## 計算量

- $O(1)$

# pow

```cpp
mint pow(uint64_t n) const
```

自身の $n$ 乗を返します。

## 計算量

- $O(\log n)$

# inv

```cpp
mint inv() const
```

Fermat の小定理を用いて、自身の乗法逆元を返します。

## 制約

- 自身が $0$ ではない
- `mod` は素数

## 計算量

- $O(\log \mathrm{mod})$

# mod

```cpp
static constexpr uint32_t mod()
```

法 `mod` を返します。

## 計算量

- $O(1)$

# 入出力

```cpp
friend ostream &operator<<(ostream &os, const mint &x)
friend istream &operator>>(istream &is, mint &x)
```

出力時は $[0,\mathrm{mod})$ の通常表現を出力します。入力時は符号付き $64$ bit 整数を読み込み、`fast == false` なら mod 上の値へ正規化します。
