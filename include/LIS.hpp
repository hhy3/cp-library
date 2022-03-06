#pragma once

#include <vector>

/**
 * @brief 最长递增子序列 (Longest increasing subsequence) 问题 
 *        简介: https://en.wikipedia.org/wiki/Longest_increasing_subsequence
 *        模板题: https://leetcode-cn.com/problems/longest-increasing-subsequence/
 * 
 * @param a 
 * @param lis 
 * @return int 
 */
template <typename T>
int LIS(const std::vector<T> &a, std::vector<T> lis) {
  lis.clear();
  for (auto x : a) {
    auto it = lower_bound(lis.begin(), lis.end(), x);
    if (it == lis.end()) lis.push_back(x);
    else *it = x;
  }
  return lis.size(); 
}