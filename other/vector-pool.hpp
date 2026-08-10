#pragma once

#include <vector>

template <class T>
struct VectorPool {
  std::vector<T> pool;
  std::vector<T*> stock;
  int ptr;

  VectorPool() = default;

  VectorPool(int sz) : pool(sz), stock(sz) {}

  inline T* alloc() { return stock[--ptr]; }

  inline void free(T* t) { stock[ptr++] = t; }

  void clear() {
    ptr = (int)pool.size();
    for (int i = 0; i < (int)pool.size(); i++) stock[i] = &pool[i];
  }
};
