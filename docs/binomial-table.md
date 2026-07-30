---
title: Binomial Table (二項係数テーブル)
documentation_of: //math/combinatorics/binomial-table.hpp
---

二項係数テーブルをパスカルの三角形より求める。

# binomial_table

```cpp
vector<vector<T> > binomial_table(int N)
```

`n` 以下の二項係数テーブルを返す。

## 計算量

- $O(n^2)$
