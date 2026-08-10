#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <functional>
#include <string>
#include <vector>

template <int char_size>
struct TrieNode {
  int nxt[char_size];

  int exist;
  std::vector<int> accept;

  TrieNode() : exist(0) { std::memset(nxt, -1, sizeof(nxt)); }
};

template <int char_size, int margin>
struct Trie {
  using Node = TrieNode<char_size>;

  std::vector<Node> nodes;
  int root;

  Trie() : root(0) { nodes.push_back(Node()); }

  void update_direct(int node, int id) { nodes[node].accept.push_back(id); }

  void update_child(int node, int child, int id) { ++nodes[node].exist; }

  void add(const std::string& str, int str_index, int node_index, int id) {
    if (str_index == str.size()) {
      update_direct(node_index, id);
    } else {
      const int c = str[str_index] - margin;
      if (nodes[node_index].nxt[c] == -1) {
        nodes[node_index].nxt[c] = (int)nodes.size();
        nodes.push_back(Node());
      }
      add(str, str_index + 1, nodes[node_index].nxt[c], id);
      update_child(node_index, nodes[node_index].nxt[c], id);
    }
  }

  void add(const std::string& str, int id) { add(str, 0, 0, id); }

  void add(const std::string& str) { add(str, nodes[0].exist); }

  void query(const std::string& str, const std::function<void(int)>& f,
             int str_index, int node_index) {
    for (auto& idx : nodes[node_index].accept) f(idx);
    if (str_index == str.size()) {
      return;
    } else {
      const int c = str[str_index] - margin;
      if (nodes[node_index].nxt[c] == -1) return;
      query(str, f, str_index + 1, nodes[node_index].nxt[c]);
    }
  }

  void query(const std::string& str, const std::function<void(int)>& f) {
    query(str, f, 0, 0);
  }

  int count() const { return (nodes[0].exist); }

  int size() const { return ((int)nodes.size()); }
};
