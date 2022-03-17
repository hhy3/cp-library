#pragma once

#include <vector>
#include <string>
#include <string_view>


namespace hy {
namespace string {

/**
 * @brief kmp (Knuth–Morris–Pratt) 算法
 *        
 *        简介: https://cp-algorithms.com/string/prefix-function.html
 *        模板题: https://www.luogu.com.cn/problem/P3375
 * 
 *        Time Complexity: O(n + m)
 * 
 * @param s 待匹配字符串
 * @param p 模式串
 * @return std::pair<std::vector<int>, std::vector<int>> 
 *         返回值为 {匹配到的位置, 前缀函数}
 */
std::pair<std::vector<int>, std::vector<int>> kmp(const std::string &s, const std::string &p) {
  int n = s.size(), m = p.size();
  std::vector<int> pi(m + 1), ans;
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


/**
 * @brief 字符串哈希
 * 
 *        简介: https://oi-wiki.org/string/hash/
 *        模板题: luogu.com.cn/problem/P3370
 * 
 * @tparam K 
 */
template <uint64_t K=13331>
struct string_hash {

  int n;
  std::vector<uint64_t> h, power;


  /**
   * @brief Construct a new string hash object
   *
   *        Time Complexity: O(n)
   *  
   */
  string_hash(std::string_view s)
    : n((int)s.size()), h(n+1), power(n+1) {
    power[0] = 1;
    for (int i = 1; i <= n; ++i) {
      h[i] = h[i-1] * K + s[i-1];
      power[i] = power[i-1] * K;
    }  
  }

  /**
   * @brief get hash value of substring s[l:r] 
   *        
   *        Time Complexity: O(1)
   * 
   */
  uint64_t get(int l, int r) {
    return h[r+1] - h[l] * power[r - l + 1];
  }

  /**
   * @brief get hash value of the whole string s
   *        
   *        Time Complexity: O(1)
   * 
   */
  uint64_t get() {
    return get(0, n-1);
  }

};

} // namespace string
} // namespace hy