#pragma once

#include <cassert>
#include <utility>

/**
 * @brief Leftist-Heap
 */
template <typename T, bool isMin = true>
struct LeftistHeap {
  struct Node {
    Node *l, *r;
    int s;
    T key;
    int idx;

    explicit Node(const T& key, int idx)
        : l(nullptr), r(nullptr), s(1), key(key), idx(idx) {}
  };

  LeftistHeap() = default;

  virtual Node* clone(Node* t) { return t; }

  Node* alloc(const T& key, int idx = -1) { return new Node(key, idx); }

  Node* meld(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if ((a->key < b->key) ^ isMin) std::swap(a, b);
    a = clone(a);
    a->r = meld(a->r, b);
    if (!a->l || a->l->s < a->r->s) std::swap(a->l, a->r);
    a->s = (a->r ? a->r->s : 0) + 1;
    return a;
  }

  Node* push(Node* t, const T& key, int idx = -1) {
    return meld(t, alloc(key, idx));
  }

  Node* pop(Node* t) {
    assert(t != nullptr);
    return meld(t->l, t->r);
  }

  Node* make_root() { return nullptr; }
};
