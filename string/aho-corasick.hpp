#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../structure/trie/trie.hpp"

template <int char_size, int margin>
struct AhoCorasick : Trie<char_size + 1, margin> {
  using Trie<char_size + 1, margin>::Trie;

  const int FAIL = char_size;
  std::vector<int> correct;

  void build(bool heavy = true) {
    correct.resize(this->size());
    for (int i = 0; i < this->size(); i++) {
      correct[i] = (int)this->nodes[i].accept.size();
    }
    std::queue<int> que;
    for (int i = 0; i <= char_size; i++) {
      if (~this->nodes[0].nxt[i]) {
        this->nodes[this->nodes[0].nxt[i]].nxt[FAIL] = 0;
        que.emplace(this->nodes[0].nxt[i]);
      } else {
        this->nodes[0].nxt[i] = 0;
      }
    }
    while (!que.empty()) {
      auto& now = this->nodes[que.front()];
      int fail = now.nxt[FAIL];
      correct[que.front()] += correct[fail];
      que.pop();
      for (int i = 0; i < char_size; i++) {
        if (~now.nxt[i]) {
          this->nodes[now.nxt[i]].nxt[FAIL] = this->nodes[fail].nxt[i];
          if (heavy) {
            auto& u = this->nodes[now.nxt[i]].accept;
            auto& v = this->nodes[this->nodes[fail].nxt[i]].accept;
            std::vector<int> accept;
            set_union(std::begin(u), std::end(u), std::begin(v), std::end(v),
                      std::back_inserter(accept));
            u = accept;
          }
          que.emplace(now.nxt[i]);
        } else {
          now.nxt[i] = this->nodes[fail].nxt[i];
        }
      }
    }
  }

  std::unordered_map<int, int> match(const std::string& str, int now = 0) {
    std::unordered_map<int, int> result, visit_cnt;
    for (auto& c : str) {
      now = this->nodes[now].nxt[c - margin];
      visit_cnt[now]++;
    }
    for (auto& [now, cnt] : visit_cnt) {
      for (auto& v : this->nodes[now].accept) result[v] += cnt;
    }
    return result;
  }

  std::pair<std::int64_t, int> move(const char& c, int now = 0) {
    now = this->nodes[now].nxt[c - margin];
    return {correct[now], now};
  }

  std::pair<std::int64_t, int> move(const std::string& str, int now = 0) {
    std::int64_t sum = 0;
    for (auto& c : str) {
      auto nxt = move(c, now);
      sum += nxt.first;
      now = nxt.second;
    }
    return {sum, now};
  }
};
