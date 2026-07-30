---
title: Prime Table (素数テーブル)
documentation_of: //math/number-theory/prime-table.hpp
---

エラトステネスの篩により $n$ 以下の全ての値について素数かどうかを判定する。

# prime_table

```cpp
vector<bool> prime_table(int n)
```

$n$ 以下の全ての値について素数かどうか判定するための長さ $n + 1$ の配列を返す。$i$ が素数のとき $i$ 番目の要素は `true` で、非素数のとき `false` が格納される。

## 計算量

- $O(n \log \log n)$
