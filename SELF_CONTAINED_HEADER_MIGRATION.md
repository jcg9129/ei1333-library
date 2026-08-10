# Self-contained header migration

## 目的

ライブラリの各ヘッダーを、それより前に別のヘッダーや
`using namespace std;` がなくても利用できる状態へ段階的に移行する。

最終的に次の状態を目指す。

- 各 `.hpp` が使用する標準ヘッダーとプロジェクトヘッダーを直接
  include する
- ヘッダー内の標準ライブラリ名を `std::` で修飾する
- ヘッダー内で `using namespace std;` を宣言しない
- 各ヘッダーを空の翻訳単位の先頭で include してコンパイルできる
- `test/verify/*.test.cpp` が `template/template.hpp` に依存しない
- verify に通常の clang-format include sorting を適用できる

## 現在の進捗

2026-08-04 時点の進捗は次のとおり。

| 項目                                      | 状態     | 件数 |
| ----------------------------------------- | -------- | ---- |
| リポジトリ内の `.hpp`                     | 調査済み | 320  |
| 自己完結化して継続検査しているヘッダー    | 移行済み | 120  |
| `template/template.hpp` に依存する verify | 移行待ち | 243  |

移行済みヘッダーの正本は
[`scripts/self-contained-headers.txt`](scripts/self-contained-headers.txt)、
未移行 verify の正本は
[`scripts/verify-template-include-allowlist.txt`](scripts/verify-template-include-allowlist.txt)
とする。この文書の件数と差がある場合は、これらの一覧を優先する。

## 段階

### 1. 新規コードの品質を固定する

状態: 完了

- 新規ヘッダーに自己完結性を要求する
- 新規 verify の `template/template.hpp` 依存を禁止する
- CI で許可リストの増加を禁止する

### 2. 既存ヘッダーを自己完結化する

状態: 進行中

依存するプロジェクトヘッダーが少ないものから、小さなまとまりで移行する。
移行したヘッダーは `scripts/self-contained-headers.txt` に追加し、CI で毎回
単体コンパイルする。

### 3. 対応する verify を移行する

状態: 未着手

依存先ヘッダーが自己完結した後、対応する verify から
`template/template.hpp` を削除する。必要な標準ヘッダー、型別名、入出力処理、
補助関数は verify 側に明示する。移行後は
`scripts/verify-template-include-allowlist.txt` から対象を削除する。

### 4. 移行済みコードの逆戻りを防ぐ

状態: 一部完了

- 自己完結化済みヘッダーは CI で継続的に単体コンパイルしている
- verify の例外追加は禁止している
- 全 verify の移行後に例外リストを削除する

### 5. 一律の検査へ切り替える

状態: 未着手

全ヘッダーと verify の移行後、全 `.hpp` の単体コンパイルと全 verify の
`template/template.hpp` 禁止を一律に適用する。verify の
`--sort-includes=0` 例外も撤廃する。

## ヘッダー移行手順

1. 依存の少ないヘッダーまたは密接に関連する小さなヘッダー群を選ぶ
2. 必要な標準ヘッダーとプロジェクトヘッダーを直接 include する
3. 標準ライブラリ名を `std::` で修飾する
4. 必要に応じて `#pragma once` を追加する
5. `scripts/self-contained-headers.txt` にパスを辞書順で追加する
6. 正常系、境界値、重要な前提を検査する単体テストを追加または更新する
7. 関連ドキュメントのシグネチャや制約を更新する
8. clang-format、ヘッダー単体コンパイル、単体テスト、docs check を実行する
9. この文書の進捗件数と移行履歴を更新する

ヘッダー単体コンパイルには、CI と同じ次の形式を使用できる。

```console
g++ -std=c++17 -fsyntax-only -x c++ -include ./path/to/header.hpp /dev/null
```

## 移行履歴

| 日付       | 対象                                                                                                                                                                                                                                                                       | 備考                              |
| ---------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------- |
| 2026-08-04 | `structure/others/sparse-table.hpp`                                                                                                                                                                                                                                        | 標準 include と `std::` 修飾      |
| 2026-08-04 | `structure/others/disjoint-sparse-table.hpp`                                                                                                                                                                                                                               | 標準 include と `std::` 修飾      |
| 2026-08-04 | `structure/others/plus-minus-one-rmq.hpp`                                                                                                                                                                                                                                  | Sparse Table 依存を明示           |
| 2026-08-04 | `structure/others/queue-operate-aggregation.hpp`                                                                                                                                                                                                                           | 標準依存を明示                    |
| 2026-08-04 | `structure/others/deque-operate-aggregation.hpp`                                                                                                                                                                                                                           | 標準依存を明示                    |
| 2026-08-04 | `structure/others/abstract-binary-indexed-tree.hpp`                                                                                                                                                                                                                        | 標準依存を明示                    |
| 2026-08-04 | `structure/others/binary-indexed-tree.hpp`                                                                                                                                                                                                                                 | 標準依存を明示                    |
| 2026-08-04 | `structure/others/persistent-array.hpp`                                                                                                                                                                                                                                    | 標準依存を明示                    |
| 2026-08-04 | `structure/others/priority-sum-structure.hpp`                                                                                                                                                                                                                              | 標準依存を明示                    |
| 2026-08-04 | `structure/others/linear-rmq.hpp`                                                                                                                                                                                                                                          | 標準依存を明示                    |
| 2026-08-04 | `structure/union-find/union-find.hpp`                                                                                                                                                                                                                                      | 標準依存を明示                    |
| 2026-08-04 | `structure/union-find/weighted-union-find.hpp`                                                                                                                                                                                                                             | 標準依存を明示                    |
| 2026-08-04 | `structure/union-find/union-find-undo.hpp`                                                                                                                                                                                                                                 | 標準依存を明示                    |
| 2026-08-04 | `structure/union-find/partially-persistent-union-find.hpp`                                                                                                                                                                                                                 | 標準依存を明示                    |
| 2026-08-04 | `structure/union-find/persistent-union-find.hpp`                                                                                                                                                                                                                           | Persistent Array 依存を明示       |
| 2026-08-04 | `structure/union-find/bipartite-graph.hpp`                                                                                                                                                                                                                                 | Union Find 依存を明示             |
| 2026-08-04 | `structure/heap/erasable-heap.hpp`                                                                                                                                                                                                                                         | 標準依存を補完                    |
| 2026-08-04 | `structure/heap/leftist-heap.hpp`                                                                                                                                                                                                                                          | 標準依存を明示                    |
| 2026-08-04 | `structure/heap/persistent-leftist-heap.hpp`                                                                                                                                                                                                                               | Leftist Heap 依存を明示           |
| 2026-08-04 | `structure/heap/skew-heap.hpp`                                                                                                                                                                                                                                             | 標準依存を明示                    |
| 2026-08-10 | `dp/cumulative-sum-2d.hpp`、`dp/cumulative-sum.hpp`、`dp/edit-distance.hpp`、`dp/knapsack-01-2.hpp`、`dp/knapsack-01.hpp`、`dp/knapsack-limitations.hpp`、`dp/knapsack.hpp`、`dp/largest-rectangle.hpp`、`dp/longest-increasing-subsequence.hpp`、`dp/monotone-minima.hpp` | 標準 include と `std::` 修飾      |
| 2026-08-10 | `structure/class/act.hpp`、`structure/class/acted-monoid.hpp`、`structure/class/affine.hpp`、`structure/class/beats-monoid.hpp`、`structure/class/monoid.hpp`、`structure/class/range-add-range-min.hpp`、`structure/class/range-chmin-chmax-add-range-sum.hpp`            | 標準 include と `std::` 修飾      |
| 2026-08-10 | `structure/others/slope-trick.hpp`、`structure/others/sqrt-decomposition.hpp`、`structure/others/union-rectangle.hpp`                                                                                                                                                      | 標準 include と `std::` 修飾      |
| 2026-08-10 | `dp/divide-and-conquer-optimization.hpp`、`dp/knapsack-limitations-2.hpp`、`dp/online-offline-dp.hpp`                                                                                                                                                                      | 移行済みヘッダーへの依存を明示    |
| 2026-08-10 | `graph/graph-template.hpp`、`graph/shortest-path/bellman-ford.hpp`、`graph/shortest-path/bfs.hpp`、`graph/shortest-path/dijkstra.hpp`、`graph/shortest-path/grid-bfs.hpp`、`graph/shortest-path/warshall-floyd.hpp`                                                        | グラフ共通型と標準 include を明示 |
| 2026-08-10 | `math/combinatorics/` の6ヘッダー                                                                                                                                                                                                                                          | 標準 include と `std::` 修飾      |
| 2026-08-10 | `math/matrix/matrix.hpp`、`math/matrix/square-matrix.hpp`、`math/rational/rational.hpp`                                                                                                                                                                                    | 標準 include と `std::` 修飾      |
| 2026-08-10 | `math/number-theory/` の11ヘッダー                                                                                                                                                                                                                                         | 標準 include と `std::` 修飾      |
| 2026-08-10 | `other/` の9ヘッダー                                                                                                                                                                                                                                                       | 標準 include と `std::` 修飾      |
| 2026-08-10 | `string/manacher.hpp`、`string/z-algorithm.hpp`                                                                                                                                                                                                                            | 標準 include と `std::` 修飾      |
| 2026-08-10 | geometry の基礎・距離・交差判定・多角形関連38ヘッダー                                                                                                                                                                                                                      | 標準 include と `std::` 修飾      |
| 2026-08-10 | `geometry/integer/point.hpp`、`structure/others/decremental-upper-hull.hpp`                                                                                                                                                                                                | 標準 include と `std::` 修飾      |

## 次の候補

次の候補として、プロジェクト内ヘッダーへの依存がない
`structure/others/generalized-slope-trick.hpp`、`structure/others/permutation-tree.hpp`、
および graph・math の基礎ヘッダー群を検討する。その後も依存関係の葉に近い
ヘッダーから進め、1コミットの変更範囲を小さく保つ。
