#pragma once

#include <algorithm>
#include <cstdint>
#include <stack>
#include <vector>

template <typename T>
std::int64_t largest_rectangle(std::vector<T> height) {
  std::stack<int> st;
  height.push_back(0);
  std::vector<int> left(height.size());
  std::int64_t ret = 0;
  for (int i = 0; i < height.size(); i++) {
    while (!st.empty() && height[st.top()] >= height[i]) {
      ret = std::max(ret,
                     (std::int64_t)(i - left[st.top()] - 1) * height[st.top()]);
      st.pop();
    }
    left[i] = st.empty() ? -1 : st.top();
    st.emplace(i);
  }
  return (ret);
}
