---
title: Mod Log (離散対数問題)
documentation_of: //math/combinatorics/mod-log.hpp
---

$a^x \equiv b \pmod p$ を満たす非負整数 $k$ の最小値を求める。

# mod_log

```cpp
int64_t mod_log(int64_t a, int64_t b, int64_t p)
```

$a^x \equiv b \pmod p$ を満たす非負整数 $x$ の最小値を返す。ただし、存在しない場合 $-1$ を返す。

## 計算量

- $O(\sqrt p)$
