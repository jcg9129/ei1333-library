---
title: Mod Tetration (テトレーション)
documentation_of: //math/combinatorics/mod-tetration.hpp
---

${a \uparrow \uparrow b} \bmod m$ を求める。$\uparrow \uparrow$ はテトレーション演算で $a^{a^{a^{a^{\ldots}}}}$ ($a$ が $b$ 個続く) を指す。

# mod_tetration

```cpp
T mod_tetration(const T& a, const T& b, const T& m)
```

${a \uparrow \uparrow b} \bmod m$ を返す。

## 計算量

- $O(\sqrt m)$
