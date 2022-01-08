#pragma once

#include <vector>
#include <string>

/**
 * @brief kmp (Knuth–Morris–Pratt) 算法
 * 简介: https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 * 模板题: https://www.luogu.com.cn/problem/P3375
 * 
 * @param s 待匹配字符串
 * @param p 模式串
 * @return std::pair<std::vector<int>, std::vector<int>> 
 *         返回值为 {匹配到的位置, 前缀函数}
 */
std::pair<std::vector<int>, std::vector<int>> kmp(const std::string &s, const std::string &p) {
  int n = s.size(), m = p.size();
  vector<int> pi(m + 1), ans;
  for (int i = 1, j = 0; i < m; ++i) {
    while (j > 0 && p[i] != p[j]) {
      j = pi[j];
    }
    if (p[i] == p[j]) {
      j++;
    } 
    pi[i + 1] = j;
  }
  for (int i = 0, j = 0; i < n; ++i) {
    while (j > 0 && s[i] != p[j]) {
      j = pi[j];
    }
    if (s[i] == p[j]) {
      j++;
    }
    if (j == m) {
      ans.push_back(i - m + 1);
      j = pi[j];
    }
  }
  return {ans, pi};
}
