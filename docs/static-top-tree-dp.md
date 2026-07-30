---
title: Static Top Tree DP (Static Top Tree 上のDP)
documentation_of: //graph/tree/static-top-tree-dp.hpp
---

Static Top Tree の各クラスターに対するDPを管理します。頂点または辺の情報を変更した後、影響を受けるクラスターだけを再計算できます。

# コンストラクタ

```cpp
StaticTopTreeDP(const StaticTopTree<G> &g, const TreeDPInfo &info)
```

Static Top Tree `g` とDPの演算を定義する `info` からDPを構築します。

## 制約

- `g` と `info` は、このオブジェクトより長く存在する
- `TreeDPInfo` の各演算は $O(1)$

## 計算量

- $O(n)$

# update_vertex

```cpp
Path update_vertex(int u)
```

頂点 $u$ の情報を変更した後に呼び出し、影響を受けるクラスターを再計算します。更新後の木全体に対応する path cluster を返します。

## 制約

- $0 \leq u \lt n$
- `TreeDPInfo` の各演算は $O(1)$

## 計算量

- $O(\log n)$

# update_edge

```cpp
Path update_edge(int e)
```

辺 $e$ の情報を変更した後に呼び出し、影響を受けるクラスターを再計算します。更新後の木全体に対応する path cluster を返します。

## 制約

- $0 \leq e \lt n - 1$
- `TreeDPInfo` の各演算は $O(1)$

## 計算量

- $O(\log n)$

# TreeDPInfo

`TreeDPInfo` は `Point` と `Path` の型、および以下の演算を定義する必要があります。

## vertex

```cpp
Path vertex(int u) const
```

頂点 $u$ のみからなる path cluster を生成します。

## add_vertex

```cpp
Path add_vertex(Point d, int u) const
```

point cluster `d` の根に頂点 $u$ を追加し、path cluster にします。

## add_edge

```cpp
Point add_edge(Path d, int e) const
```

path cluster `d` に辺 $e$ を追加して仮想的な根を作り、point cluster にします。

## rake

```cpp
Point rake(Point l, Point r) const
```

point cluster `l` と `r` をマージします。

## compress

```cpp
Path compress(Path p, Path c, int e) const
```

根に近い側の path cluster `p` と、その子側の path cluster `c` を辺 $e$ でマージします。
