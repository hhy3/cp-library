#pragma once

#include <vector>
#include <functional>

namespace hy {
namespace dp {

/**
 * @brief 最长递增子序列 (Longest increasing subsequence) 问题 
 *        简介: https://en.wikipedia.org/wiki/Longest_increasing_subsequence
 *        模板题: https://leetcode-cn.com/problems/longest-increasing-subsequence/
 * 
 * @param a 
 * @param lis 
 * @return int 
 */
template <typename T, typename Compare>
int LIS(const std::vector<T> &a, 
        std::vector<T> &lis, 
        Compare cmp) {
  lis.clear();
  int n = a.size();
  std::vector<int> dp(n);
  for (int i = 0; i < n; ++i) {
    auto it = lower_bound(lis.begin(), lis.end(), a[i], cmp);
    dp[i] = it - lis.begin();
    if (it == lis.end()) lis.push_back(a[i]);
    else *it = a[i];
  }
  int len_lis = lis.size();
  lis.clear();
  for (int i = n-1, j = len_lis - 1; i >= 0; --i) {
    if (dp[i] == j) {
      lis.push_back(a[i]);
      j--;
    }
  }
  reverse(lis.begin(), lis.end());
  return len_lis;
}


} // namespace dp
} // namespace hy