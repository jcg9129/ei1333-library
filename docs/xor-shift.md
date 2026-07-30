---
title: Xor Shift
documentation_of: //other/xor-shift.hpp
---

Xorshift は擬似乱数生成法の一つである。

周期が $2^{64}-1$ となる実装を示した。

# コンストラクタ

```cpp
explicit XorShift(uint64_t seed = 88172645463325252ull)
```

シード値 `seed` で初期化する。

# get

```cpp
inline T get()
```

$[0, 2^{64})$ で生成した乱数を返す。

# get

```cpp
inline uint32_t get(uint32_t r)
```

$[0, r)$ で生成した乱数を返す。`r` は32bit整数に限る。64bitで生成したい場合は例えば `get()` を `r` で割った余りを求めるとよい。

# get

```cpp
inline uint32_t get(uint32_t l, uint32_t r)
```

$[l, r)$ で生成した乱数を返す。

# probability

```cpp
inline double probability()
```

$[0.0, 1.0)$ で生成した乱数(実数)を返す。
